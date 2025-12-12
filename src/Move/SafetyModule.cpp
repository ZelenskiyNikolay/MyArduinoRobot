#include <Arduino.h>
#include "SafetyModule.h"

SafetyModule::SafetyModule()
    : motor(), sensorLeft(7), sensorRight(6), sensorBack(14), sensorBackFlow(15),
      ultrasonic(16, 17)
{
    ultrasonic.begin();
}

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
    if (!active)
    {
        if (Ready)
            return 1;
        else
        {
            corection = true;
            current.time = 100;
            elapsed = 0;
            active = true;
            switch (sensorTrigger)
            {
            case SafetyTriger::SENSOR_LEFT:
                motor.backward();
                break;
            case SafetyTriger::SENSOR_RIGHT:
                motor.backward();
                break;
            case SafetyTriger::SENSOR_BACK:
                motor.forward();
                break;
            case SafetyTriger::SENSOR_BACK_FLOW:
                motor.forward();
                break;
            default:
                break;
            }
        }
    }
    // Здесь можно добавить проверки датчиков безопасности
    if (!corection)
        if (CheckSensors())
        {
            motor.stop();
            active = false;
            // return 0; // завершено аварийно
        }
    elapsed += dt;
    if (elapsed >= current.time)
    {
        if (corection)
            corection = false;
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
bool SafetyModule::CheckSensors()
{
    if (!sensorLeft.GetSensorState())
        sensorTrigger = SafetyTriger::SENSOR_LEFT;
    if (!sensorRight.GetSensorState())
        sensorTrigger = SafetyTriger::SENSOR_RIGHT;
    if (!sensorBackFlow.GetSensorState())
        sensorTrigger = SafetyTriger::SENSOR_BACK_FLOW;
    if (sensorBack.GetSensorState())
        sensorTrigger = SafetyTriger::SENSOR_BACK;

    return (!sensorLeft.GetSensorState() || !sensorRight.GetSensorState() ||
            !sensorBackFlow.GetSensorState() || sensorBack.GetSensorState());
}