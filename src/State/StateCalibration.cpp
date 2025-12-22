#include "StateCalibration.h"

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
   MovementModule::getInstance().stop();
}
void StateCalibration::update(float dt)
{
    MovementModule::getInstance().MoveCalibration(dt);
}
void StateCalibration::Draw(float dt)
{
}