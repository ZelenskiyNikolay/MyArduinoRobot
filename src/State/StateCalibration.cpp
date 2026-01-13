#include "StateCalibration.h"
#include "Sensors/TouchButtons.h"
#include "Move/SafetyModule.h"
#include "Module/SDModule.h"

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
    SafetyModule::getInstance().update(dt);
    ir.update();

    if (TouchButtons::getInstance().consume(0))
    {
        SafetyModule::getInstance().ResetStips();
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Forward, 1000));
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
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Left90, 10));
        break;
    case Button2:
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Forward, 1000));
        break;
    case Button3:
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Right90, 10));
        break;
    case Button4:
        SafetyModule::getInstance().Forward(0, 2);
        break;

    case Button6:
        SafetyModule::getInstance().Forward(2, 0);
        break;
    case Button8:
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Backward, 1000));
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

    Draw(dt);
}

void StateCalibration::Draw(float dt)
{
    timer -= dt;
    if (timer < 0)
    {
        display->clear();
        display->drawText("Calibration:", 0, 0, 1);
        char buffer[16];
        sprintf(buffer, "Left: %d", (int)SafetyModule::getInstance().GetTics(true));
        display->drawText(buffer, 0, 20, 1);
        sprintf(buffer, "Right: %d", SafetyModule::getInstance().GetTics(false));
        display->drawText(buffer, 0, 30, 1);
        char buf[5];
        dtostrf(distance, 1, 1, buf);
        sprintf(buffer, "Dis: %s cm", buf);
        display->drawText(buffer, 0, 40, 1);

        timer = 500;
    }
}