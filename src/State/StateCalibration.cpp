#include "StateCalibration.h"

StateCalibration::StateCalibration(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12), ir(A7)
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
    SafetyModule::getInstance().update();
    ir.update();

    if (TouchButtons::getInstance().consume(0))
    {
    }
    if (TouchButtons::getInstance().consume(1))
    {
    }
    if (TouchButtons::getInstance().consume(2))
    {
    }
    if (TouchButtons::getInstance().consume(3))
    {

        SafetyModule::getInstance().TriggerUltrasonic();
    }

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
        SafetyModule::getInstance().NewMov(MotionState::FORWARD, 50, 50);
        steep_calibration++;
        return;
    }
    if (steep_calibration == 1)
    {
        if (!SafetyModule::getInstance().isBusy())
        {
            timer1 = 1000;
            steep_calibration++;
            return;
        }
    }
    if (steep_calibration == 2)
    {
        timer1 = 1000;
        steep_calibration++;
        SafetyModule::getInstance().TriggerUltrasonic();
        return;
    }
    if (steep_calibration == 3)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            if (distance < 250)
            {
                steep_calibration = 2;
                return;
            }
            else
            {
                GlobalSettings::getInstance().Point.south = distance;
                steep_calibration++;
                timer1 = 500;
                return;
            }
        }
    }
    if (steep_calibration == 4)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
        {
            SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 3, 3);
            steep_calibration++;
            timer1 = 500;
            return;
        }
    }
    if (steep_calibration == 5)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
        {
            SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
            steep_calibration++;
            timer1 = 500;
            return;
        }
    }
    if (steep_calibration == 6)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
        {
            timer1 = 1000;
            steep_calibration++;
            SafetyModule::getInstance().TriggerUltrasonic();
            return;
        }
    }
    if (steep_calibration == 7)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            if (distance < 40 || distance > 70)
            {
                steep_calibration = 6;
                return;
            }
            else
            {
                GlobalSettings::getInstance().Point.east = distance;
                steep_calibration++;
                timer1 = 500;
                return;
            }
        }
    }
    if (steep_calibration == 8)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
        {
            SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
            steep_calibration++;
            timer1 = 500;
            return;
        }
    }
    if (steep_calibration == 9)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
        {
            timer1 = 1000;
            steep_calibration++;
            SafetyModule::getInstance().TriggerUltrasonic();
            return;
        }
    }
    if (steep_calibration == 10)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            if (distance < 25 || distance > 40)
            {
                steep_calibration = 9;
                return;
            }
            else
            {
                GlobalSettings::getInstance().Point.north = distance;
                steep_calibration++;
                timer1 = 1000;
                return;
            }
        }
    }
    if (steep_calibration == 11)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
        {
            SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
            steep_calibration++;
            timer1 = 500;
            return;
        }
    }

    if (steep_calibration == 12)
    {
        timer1 -= dt;
        if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
        {
            timer1 = 1000;
            steep_calibration++;
            SafetyModule::getInstance().TriggerUltrasonic();
            return;
        }
    }
    if (steep_calibration == 13)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            if (distance < 40 || distance > 70)
            {
                steep_calibration = 12;
                return;
            }
            else
            {
                GlobalSettings::getInstance().Point.west = distance;
                steep_calibration++;
                timer1 = 1000;
                return;
            }
        }
    }
    if (steep_calibration == 14)
    {
        char buffer[32];
        sprintf(buffer, "X: %d cm Y: %d cm", GlobalSettings::getInstance().Point.south,
                GlobalSettings::getInstance().Point.east);
        Serial.println("Откалибровано:");
        Serial.println(buffer);
        sprintf(buffer, "-X: %d cm -Y: %d cm", GlobalSettings::getInstance().Point.north,
                GlobalSettings::getInstance().Point.west);
        Serial.println(buffer);
        steep_calibration++;
    }
    if (steep_calibration == 15)
    {
        timer1 -= dt;
        if (timer1 < 0)
        {
            EventBus::push({EVENT_CHANGE_STATE, STATE_SEARCH_BASE});
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
        char buffer[32];
        sprintf(buffer, "Left: %d", (int)SafetyModule::getInstance().GetTics(true));
        display->drawText(buffer, 0, 15, 1);
        sprintf(buffer, "Right: %d", (int)SafetyModule::getInstance().GetTics(false));
        display->drawText(buffer, 0, 25, 1);
        sprintf(buffer, "Dis: %d cm", (int)distance);
        display->drawText(buffer, 0, 35, 1);

        sprintf(buffer, "X: %d cm Y: %d cm", GlobalSettings::getInstance().Point.south,
                GlobalSettings::getInstance().Point.east);
        display->drawText(buffer, 0, 45, 1);
        sprintf(buffer, "-X: %d cm -Y: %d cm", GlobalSettings::getInstance().Point.north,
                GlobalSettings::getInstance().Point.west);
        display->drawText(buffer, 0, 55, 1);

        timer = 500;
    }
}