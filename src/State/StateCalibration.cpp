#include "StateCalibration.h"
#include "Sensors/TouchButtons.h"
#include "Move/SafetyModule.h"

StateCalibration::StateCalibration(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12)
{
}
StateCalibration::StateCalibration(DisplaySystem &dispOld)
    : displayOld(&dispOld), spriteOld(&dispOld), sound(12)
{
}

void StateCalibration::enter()
{
    display->clear();
    display->drawText("Calibration:", 0, 0, 1);
    timer = 0;
}
void StateCalibration::update(float dt)
{
    SafetyModule::getInstance().update(dt);

    if (TouchButtons::getInstance().consume(0))
    {
        Serial.println("!! Кнопка нажата !! ----------------------------------------------- ");
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Forward, 2000));
    }
    if (TouchButtons::getInstance().consume(1))
    {
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Backward, 1000));
    }
    if (TouchButtons::getInstance().consume(2))
    {
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Left90, 10));
    }
    if (TouchButtons::getInstance().consume(3))
    {
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Stop, 0));
        SafetyModule::getInstance().ResetStips();
    }
    // MovementModule::getInstance().MoveCalibration(dt);
    
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
        sprintf(buffer, "Left: %d", SafetyModule::getInstance().GetTics(true));
        display->drawText(buffer, 0, 20, 1);
        sprintf(buffer, "Right: %d", SafetyModule::getInstance().GetTics(false));
        display->drawText(buffer, 0, 30, 1);
        sprintf(buffer, "L Cor: %d", SafetyModule::getInstance().GetCorrections());
        display->drawText(buffer, 0, 40, 1);
        sprintf(buffer, "R Cor: %d", SafetyModule::getInstance().GetCorrections(false));
        display->drawText(buffer, 0, 50, 1);
        timer = 500;
    }
}