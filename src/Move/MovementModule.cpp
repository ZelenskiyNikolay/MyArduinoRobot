#include "MovementModule.h"
#include "Arduino.h"
void MovementModule::forward(int time)
{
    safety.startRequest(MovementRequest(MoveType::Forward, time));
}

void MovementModule::backward(int time)
{
    safety.process(MovementRequest(MoveType::Backward, time));
}

void MovementModule::left(int time)
{
    safety.process(MovementRequest(MoveType::Left, time));
}

void MovementModule::right(int time)
{
    safety.process(MovementRequest(MoveType::Right, time));
}

void MovementModule::stop()
{
    safety.process(MovementRequest(MoveType::Stop, 0));
}
void MovementModule::MoveDance(float dt)
{
    if (!steepReady)
    {
        int temp = safety.update(dt);
        if (temp == 0)
        { // аварийно сработка датчиков
        }
        if (temp < 0)
            return; // выполняется шаг
        if (temp > 0)
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
            safety.startRequest(MovementRequest(MoveType::Forward, steep * 1000));
        else if (steep == 2)
            safety.startRequest(MovementRequest(MoveType::Backward, 1000));
        else if (steep == 3)
            safety.startRequest(MovementRequest(MoveType::Left, 2000));
        else if (steep == 4)
            safety.startRequest(MovementRequest(MoveType::Right,  2000));
        else if (steep == 5){
            safety.startRequest(MovementRequest(MoveType::Stop, steep * 100));
            steep =0;}
        // else if (steep == 6)
        //     safety.startRequest(MovementRequest(MoveType::Forward, steep * 200));
        // else if (steep == 7)
        //     safety.startRequest(MovementRequest(MoveType::Backward, steep * 100));
        // else if (steep == 8)
        //     safety.startRequest(MovementRequest(MoveType::Left, steep * 1000));
        // else if (steep == 9)
        //     safety.startRequest(MovementRequest(MoveType::Right, steep * 1000));
        // else if (steep == 10)
        //     safety.startRequest(MovementRequest(MoveType::Stop, steep * 100));
    }
}