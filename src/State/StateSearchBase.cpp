#include "StateSearchBase.h"

StateSearchBase::StateSearchBase(DisplayOled &disp)
    : display(&disp), sprite(&disp), ir(A7) //, sound(12)
{
}
void StateSearchBase::enter()
{
    display->clear();
    display->NeedUpdate = true;
    timer = 0;
    SafetyModule::getInstance().NewMov(MotionState::FORWARD, 5, 5);
    // GlobalSettings::getInstance().Point.east = 65;
}
void StateSearchBase::update(float dt)
{
    if (!edgeAlign)
        SafetyModule::getInstance().update();
    else
    {
        if (SafetyModule::getInstance().EdgeAlignment())
        {
            edgeAlign = false;
        }
    }
    ir.update();
    if (TouchButtons::getInstance().consume(3))
    {
        maxDistance = 0;
        bestStep = 0;
        corner = 0;
        currentStep = 0;
        timer = 1000;
        lookSouth = true;
        Look = Redy;
    }
    IrLogic();

    if (lookSouth)
        LookSouth(dt);
    if (RotateSouth)
        RotateToSouth(dt);
    if (moveEast)
        MoveToEastDiscrete(dt);
    if (ToSouthConfirm)
        SouthConfirm(dt);

    Draw(dt);
}
void StateSearchBase::SouthConfirm(float dt)
{
    timer -= dt;
    if (timer > 0 || SafetyModule::getInstance().isBusy())
        return;

    switch (SC)
    {
    case Redy:
    {
        if (distance <= 0)
        {
            SC = Triger;
            break;
        }
        if (itaration < 3)
        {
            measurements[itaration] = distance;
            itaration++;
            timer = 500;
            SC = Triger;
            break;
        }
        else
        {
            int successCount = 0;
            for (int i = 0; i < 3; i++)
            {
                if (measurements[i] > 250)
                {
                    successCount++;
                }
            }
            if (successCount >= 2)
            {
                Confirm = true;
            }
            else
            {
                Confirm = false;
            }
            ToSouthConfirm = false;
            distance = 0;
            SC = Redy;
            itaration = 0;
            memset(measurements, 0, sizeof(measurements));
        }
        break;
    }

    case Triger:
        SafetyModule::getInstance().TriggerUltrasonic();
        SC = Distanse;
        break;

    case Distanse:
        float temp = SafetyModule::getInstance().GetDistance();
        if (temp > 0)
        {
            distance = temp;
            SC = Redy;
        }
        else
        {
            SC = Triger;
            timer = 100;
        }
        break;
    }
}
void StateSearchBase::MoveToEastDiscrete(float dt)
{
    timer -= dt;
    if (timer > 0 || SafetyModule::getInstance().isBusy())
        return;

    switch (MoveToEast)
    {
    case Redy:
    {
        if (cur <= 0)
        {
            MoveToEast = Triger;
            return;
        }
        int delta = cur - GlobalSettings::getInstance().Point.east;
        if (delta == 0)
        {
            SafetyModule::getInstance().StopMov();
            moveEast = false;
            return;
        }
        timer = 500;
        if (abs(delta) > 5)
        {
            if (delta > 0)
                SafetyModule::getInstance().NewMov(MotionState::FORWARD, 5, 5);
            else
                SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 5, 5);
        }
        else if (abs(delta) > 0)
        {
            if (delta > 0)
                SafetyModule::getInstance().NewMov(MotionState::FORWARD, 2, 2);
            else
                SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 2, 2);
        }
        MoveToEast = Triger;
        break;
    }
    case Triger:
        SafetyModule::getInstance().TriggerUltrasonic();
        MoveToEast = Distanse;
        break;
    case Distanse:
        float temp = SafetyModule::getInstance().GetDistance();
        if (temp > 0)
        {
            if (temp < 200)
            {
                cur = temp;
                MoveToEast = Redy;
            }
            else
            {
                MoveToEast = Triger;
            }
        }
        else
            MoveToEast = Triger;
        break;
    }
}
void StateSearchBase::LookSouth(float dt)
{
    timer -= dt;
    if (timer < 0 && !SafetyModule::getInstance().isBusy())
    {
        switch (Look)
        {
        case Redy:
            if (currentStep > 11)
            {
                lookSouth = false;
                break;
            }
            timer = 1000;
            SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, ticks90Left / 3, 0);
            corner += 30;
            currentStep++;
            Look = Triger;
            break;
        case Triger:
            SafetyModule::getInstance().TriggerUltrasonic();
            Look = Distanse;
            break;
        case Distanse:
            float temp = SafetyModule::getInstance().GetDistance();
            if (temp > 0)
            {
                if (temp > maxDistance)
                {
                    maxDistance = temp;
                    bestStep = currentStep;
                    Look = Redy;
                }
                else
                {
                    Look = Redy;
                }
            }
            else
                Look = Triger;

            break;
        }
    }
}
void StateSearchBase::IrLogic()
{
    ButtonIR tmp = ir.GetSensorState();
    switch (tmp)
    {
    case Button1:
        SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, 0, 0);
        break;
    case ButtonUp:
        SafetyModule::getInstance().NewMov(MotionState::FORWARD, 20, 20);
        break;
    case Button3:
        SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT, 0, 0);
        break;
    case ButtonLeft:
        SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
        break;
    case ButtonRight:
        SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT90);
        break;
    case Button9:
        SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
        moveEast = true;
        timer = 1000;
        cur = 0;
        break;
    case ButtonDown:
        SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 3, 3);
        break;
    case Button8:
    {
        angle = bestStep * 30;
        RotateSouth = true;
        break;
    }
    case Button0:
    {
        edgeAlign = true;
        break;
    }
    case ButtonHash:
    {
        ToSouthConfirm = true;
        break;
    }
    case Button7:
        maxDistance = 0;
        bestStep = 0;
        corner = 0;
        currentStep = 0;
        timer = 1000;
        lookSouth = true;
        Look = Redy;
        break;

    default:
        break;
    }
}
void StateSearchBase::RotateToSouth(float dt)
{
    timer -= dt;
    if (timer < 0 && !SafetyModule::getInstance().isBusy())
    {
        if (angle <= 0)
        {
            RotateSouth = false;
            return;
        }
        if (angle >= 360)
        {
            RotateSouth = false;
            return;
        }
        if (angle < 180)
        {
            if (angle > 90)
            {
                timer = 1000;
                SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
                angle -= 90;
            }
            else
            {
                timer = 1000;
                SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, ticks90Left / 3, 0);
                angle -= 30;
            }
        }
        else
        {
            int temp = 360 - angle;
            if (temp > 90)
            {
                timer = 1000;
                SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT90);
                angle += 90;
            }

            else
            {
                timer = 1000;
                SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT, 0, ticks90Left / 3);
                angle += 30;
            }
        }
    }
}
void StateSearchBase::Draw(float dt)
{
    timer -= dt;
    if (timer < 0)
    {
        display->clear();
        display->drawText("LookSouth:", 0, 0, 1);
        char buffer[64];

        sprintf(buffer, "Confirm South: %d", Confirm);
        display->drawText(buffer, 0, 25, 1);

        sprintf(buffer, "MaxDis: %d cm St:%d", maxDistance, currentStep);
        display->drawText(buffer, 0, 45, 1);
        sprintf(buffer, "BestSt: %d Corn: %d", bestStep, corner);
        display->drawText(buffer, 0, 55, 1);

        timer = 500;
    }
}