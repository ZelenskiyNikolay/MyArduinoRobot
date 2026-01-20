#include "MovementModule.h"
#include "Arduino.h"

MovementModule::MovementModule() : safety(SafetyModule::getInstance())
{
}
void MovementModule::MoveCalibration(float dt)
{
}

void MovementModule::MoveDance(float dt)
{
    timer -= dt;
    if (!steepReady && timer < 0)
    {
        bool temp = safety.getInstance().isBusy();
        if (temp)
            return; // выполняется шаг
        if (!temp)
            steepReady = true; // шагвыполнен
    }
    if (steepReady)
    {
        steepReady = false;
        if (steep > MAX_STEEPS)
            steep = 0;
        steep++;
        Serial.println(steep);

        if (steep == 1)
        {
            SafetyModule::getInstance().NewMov(MotionState::FORWARD, 20, 20);
            timer = 500;
        }
        else if (steep == 2)
        {
            SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 20, 20);
            timer = 500;
        }
        else if (steep == 3)
        {
            SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
            timer = 500;
        }
        else if (steep == 4)
            timer = 500;
        else if (steep == 5)
        {
            SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT90);
            timer = 500;
        }
        else if (steep == 6)
            timer = 500;
        else if (steep == 7)
            steep = 0;
    }
}