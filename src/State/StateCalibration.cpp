#include "StateCalibration.h"
#include "Sensors/TouchButtons.h"
#include "Move/SafetyModule.h"
#include "Module/SDModule.h"
#include "Move/SafetyModule2.h"

StateCalibration::StateCalibration(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12), ir(A7)
{
}
StateCalibration::StateCalibration(DisplaySystem &dispOld)
    : displayOld(&dispOld), spriteOld(&dispOld), sound(12), ir(A7)
{
}

void StateCalibration::enter()
{
    display->clear();
    display->drawText("Calibration:", 0, 0, 1);
    timer = 0;
    SDModule::getInstance().begin();
    int angle = SDModule::getInstance().getIntConfig("angle", 110);
    Serial.print(F("Угол прочитано: "));
    Serial.println(angle);
}
void StateCalibration::update(float dt)
{
    // SafetyModule::getInstance().update(dt);
    SafetyModule2::getInstance().update();
    ir.update();

    if (TouchButtons::getInstance().consume(0))
    {
        SafetyModule::getInstance().ResetStips();
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Forward, 500));
    }
    if (TouchButtons::getInstance().consume(1))
    {
        SafetyModule::getInstance().ResetStips();
        // SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Backward, 1000));
        SafetyModule::getInstance().Forward(2, 0);
    }
    if (TouchButtons::getInstance().consume(2))
    {
        SafetyModule::getInstance().ResetStips();
        SafetyModule::getInstance().Forward(0, 2);
        // SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Left90, 10));
    }
    if (TouchButtons::getInstance().consume(3))
    {
        // distnce = SafetyModule::getInstance().GetDistance();
        SafetyModule::getInstance().TriggerUltrasonic();
    }

    ButtonIR tmp = ir.GetSensorState();
    switch (tmp)
    {
    case Button1:
        SafetyModule2::getInstance().NewMov(MotionState::TURN_LEFT, 0, 0);
        break;
    case Button2:
        SafetyModule2::getInstance().NewMov(MotionState::FORWARD, 20, 20);
        break;
    case Button3:
        SafetyModule2::getInstance().NewMov(MotionState::TURN_RIGHT, 0, 0);
        break;
    case Button4:
        SafetyModule2::getInstance().NewMov(MotionState::TURN_LEFT90);
        break;
    case Button6:
        SafetyModule2::getInstance().NewMov(MotionState::TURN_RIGHT90);
        break;
    case Button5:
        SafetyModule2::getInstance().NewMov(MotionState::BACKWARD, 2, 2);
        break;
    case Button8:
        SafetyModule2::getInstance().NewMov(MotionState::BACKWARD, 20, 20);
        break;
    case Button0:
        SafetyModule::getInstance().TriggerUltrasonic();
        break;

    default:
        break;
    }

    float temp = SafetyModule::getInstance().GetDistance();
    if (temp > 0)
    {
        distance = temp;
    }

    ProcessCalibration(dt);

    Draw(dt);
}
void StateCalibration::ProcessCalibration(float dt)
{
    if (steep_calibration == 0)
    {
        SafetyModule2::getInstance().NewMov(MotionState::FORWARD, 50, 50);
        steep_calibration++;
        return;
    }
    if (steep_calibration == 1)
    {
        if (!SafetyModule2::getInstance().isBusy())
        {
            timer1 = 1000;
            steep_calibration++;
            return;
        }
    }
    if (steep_calibration == 2)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule2::getInstance().isBusy())
        {
            SafetyModule2::getInstance().NewMov(MotionState::BACKWARD, 3, 3);
            steep_calibration++;
            return;
        }
    }
    if (steep_calibration == 3)
    {
        if (timer1 < 0 && !SafetyModule2::getInstance().isBusy())
        {
            SafetyModule2::getInstance().NewMov(MotionState::TURN_LEFT90);
            steep_calibration++;
            return;
        }
    }
    if (steep_calibration == 4)
    {
        timer1 = 1000;
        steep_calibration++;
        SafetyModule::getInstance().TriggerUltrasonic();
        return;
    }
    if (steep_calibration == 5)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            if (distance < 40 || distance > 70)
            {
                steep_calibration = 4;
                return;
            }
            else
            {
                GlobalSettings::getInstance().Distance_X = distance;
                steep_calibration++;
                return;
            }
        }
    }
    if (steep_calibration == 6)
    {
        SafetyModule2::getInstance().NewMov(MotionState::TURN_LEFT90);
        steep_calibration++;
        return;
    }

    if (steep_calibration == 7)
    {
        timer1 = 1000;
        steep_calibration++;
        SafetyModule::getInstance().TriggerUltrasonic();
        return;
    }

    if (steep_calibration == 8)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            if (distance < 25 || distance > 40)
            {
                steep_calibration = 7;
                return;
            }
            else
            {
                GlobalSettings::getInstance().Distance_Y = distance;
                steep_calibration++;
                timer1 = 1000;
                return;
            }
        }
    }
    if (steep_calibration == 9)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            //EventBus::push({EVENT_CHANGE_STATE, STATE_NORMAL});
        }
    }
}
void StateCalibration::Draw(float dt)
{
    timer -= dt;
    if (timer < 0)
    {
        display->clear();
        display->drawText("Calibration:", 0, 0, 1);
        char buffer[16];
        sprintf(buffer, "Left: %d", (int)SafetyModule2::getInstance().GetTics(true));
        display->drawText(buffer, 0, 15, 1);
        sprintf(buffer, "Right: %d", (int)SafetyModule2::getInstance().GetTics(false));
        display->drawText(buffer, 0, 25, 1);
        sprintf(buffer, "Dis: %d cm", (int)distance);
        display->drawText(buffer, 0, 35, 1);

        sprintf(buffer, "X: %d cm Y: %d cm", GlobalSettings::getInstance().Distance_X,
                GlobalSettings::getInstance().Distance_Y);
        display->drawText(buffer, 0, 45, 1);

        timer = 500;
    }
}