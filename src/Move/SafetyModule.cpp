#include <Arduino.h>
#include "SafetyModule.h"

SafetyModule::SafetyModule(MotorModule &motor)
    : motor(motor),sensorLeft(7),sensorRight(6),sensorBack(14),sensorBackFlow(15)
{}

void SafetyModule::process(const MovementRequest &req)
{
    motor.execute(req);
}

void SafetyModule::startRequest(const MovementRequest &req)
{
    current = req;
    elapsed = 0;
    active = true;
    Ready = false;
    
    switch (req.type)
    {
    case MoveType::Forward:
        motor.forward();
        break;
    case MoveType::Backward:
        motor.backward();
        break;
    case MoveType::Left:
        motor.left();
        break;
    case MoveType::Right:
        motor.right();
        break;
    default:
        break;
    }
}

int SafetyModule::update(float dt)
{
    if (!active){
        if (Ready)
        return 1;
        else
        return 0;
    }
    // Здесь можно добавить проверки датчиков безопасности
    if (!sensorLeft.GetSensorState() || !sensorRight.GetSensorState() ||
        !sensorBackFlow.GetSensorState() || sensorBack.GetSensorState()) {
        motor.stop();
        active = false;
        return 0;  // завершено аварийно
    } 
    elapsed += dt;
    if (elapsed >= current.time)
    {
        motor.stop();
        active = false;
        Ready = true;
        return 1; // завершено по времени
    }

    return -1; // еще выполняется
}

bool SafetyModule::isBusy() const
{
    return active;
}
