#include "MovementModule.h"
#include "Arduino.h"

MovementModule::MovementModule() : safety(SafetyModule::getInstance())
{
}
/*
void MovementModule::forward(int time)
{
    safety.process(MovementRequest(MoveType::Forward, time));
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
    */
void MovementModule::MoveCalibration(float dt)
{
    // 1. если шаг выполняется — обновляем safety
    if (!steepReady)
    {
        int res = safety.update(dt);

        if (res < 0)
            return; // шаг ещё выполняется

        steepReady = true; // шаг завершён
    }

    // 2. если готовы к следующему шагу
    if (steepReady)
    {
        steepReady = false;
        steep++;
        Serial.println(steep);

        switch (steep)
        {
        case 1:
            // едем вперёд ДО КРАЯ (safety должен сам остановить)
            safety.startRequest(MovementRequest(MoveType::Forward, 5000));
            break;

        case 2:
            safety.startRequest(MovementRequest(MoveType::Stop, 300));
            break;

        case 3:
            // поворот налево 90°
            safety.startRequest(MovementRequest(MoveType::Left, 1100)); // подстрой
            break;

        case 4:
            safety.startRequest(MovementRequest(MoveType::Stop, 300));
            break;

        case 5:
        {
            // int distX = Sensors.getUltrasound(); // <-- твой метод
            // GlobalSettings::getInstance().setX(distX);
            steepReady = true; // мгновенный шаг
            break;
        }

        case 6:
            safety.startRequest(MovementRequest(MoveType::Left, 1100));
            break;

        case 7:
            safety.startRequest(MovementRequest(MoveType::Stop, 300));
            break;

        case 8:
        {
            // int distY = Sensors.getUltrasound();
            // GlobalSettings::getInstance().setY(distY);
            steepReady = true;
            break;
        }
         default:
        {
            safety.startRequest(MovementRequest(MoveType::Stop, 0));
            if (steep > 9)
                steep = 9;
            // steep = 0;
            //  тут переход в NormalState
            break;
        }
        }
    }
}

void MovementModule::MoveDance(float dt)
{
    if (!steepReady)
    {
        int temp = safety.update(dt);
        if (temp == 0)
        { // аварийно сработка датчиков
            temp = 1;
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
            safety.startRequest(MovementRequest(MoveType::Forward, 1000));
        else if (steep == 2)
            safety.startRequest(MovementRequest(MoveType::Stop, 500));
        else if (steep == 3)
            safety.startRequest(MovementRequest(MoveType::Backward, 500));
        else if (steep == 4)
            safety.startRequest(MovementRequest(MoveType::Stop, 500));
        else if (steep == 5)
            safety.startRequest(MovementRequest(MoveType::Left, 2200));
        else if (steep == 6)
            safety.startRequest(MovementRequest(MoveType::Stop, 500));
        else if (steep == 7)
            safety.startRequest(MovementRequest(MoveType::Right, 1100)); // 1100 Примерно 90"
        else if (steep == 8)
        {
            safety.startRequest(MovementRequest(MoveType::Stop, 500));
            steep = 0;
        }
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