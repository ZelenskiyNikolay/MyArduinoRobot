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
    // MovementModule::getInstance().stop();
    // SafetyModule::getInstance().reset();
    // SafetyModule::getInstance().STOP_MOTORS();
    //SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Stop, 0));
}
void StateCalibration::update(float dt)
{
    SafetyModule::getInstance().update(dt);

    if (TouchButtons::getInstance().consume(0))
    {
        Serial.println("!! Кнопка нажата !! ----------------------------------------------- ");
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Forward, 1000));
    }
    if (TouchButtons::getInstance().consume(1))
    {
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Backward, 1000));
    }
    if (TouchButtons::getInstance().consume(2))
    {
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Left, 1100));
    }
    if (TouchButtons::getInstance().consume(3))
    {
        SafetyModule::getInstance().startRequest(MovementRequest(MoveType::Stop, 0));
    }
    // MovementModule::getInstance().MoveCalibration(dt);
 
}
void StateCalibration::Draw(float dt)
{
}