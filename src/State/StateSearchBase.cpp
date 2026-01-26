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
}
void StateSearchBase::update(float dt)
{
    SafetyModule::getInstance().update();
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

    Draw(dt);
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
            SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, 6, 0);
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
    case Button2:
        SafetyModule::getInstance().NewMov(MotionState::FORWARD, 20, 20);
        break;
    case Button3:
        SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT, 0, 0);
        break;
    case Button4:
        SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
        break;
    case Button6:
        SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT90);
        break;
    case Button5:
        SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 2, 2);
        break;
    case Button8:
        SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 20, 20);
        break;
    case Button7:
    {
        int angle = bestStep * ticks90Left / 3;
        SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, angle, 0);
        break;
    }

    case Button0:
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

void StateSearchBase::Draw(float dt)
{
    timer -= dt;
    if (timer < 0)
    {
        display->clear();
        display->drawText("LookSouth:", 0, 0, 1);
        char buffer[64];
        // sprintf(buffer, "Left: %d", (int)SafetyModule::getInstance().GetTics(true));
        // display->drawText(buffer, 0, 15, 1);
        // sprintf(buffer, "Right: %d", (int)SafetyModule::getInstance().GetTics(false));
        // display->drawText(buffer, 0, 25, 1);
        // sprintf(buffer, "Dis: %d cm", (int)distance);
        // display->drawText(buffer, 0, 35, 1);

        sprintf(buffer, "MaxDis: %d cm St:%d", maxDistance, currentStep);
        display->drawText(buffer, 0, 45, 1);
        sprintf(buffer, "BestSt: %d Corn: %d", bestStep, corner);
        display->drawText(buffer, 0, 55, 1);

        timer = 500;
    }
}