#include <Arduino.h>
#include "SafetyModule.h"

SafetyModule::SafetyModule()
    : motor(), sensorLeft(7), sensorRight(6), sensorBack(14), sensorBackFlow(15),
      ultrasonic(28, 26)
{
    ultrasonic.begin();
    current = MovementRequest(MoveType::Stop, 0);
    elapsed = 0;
    active = false;
    Ready = true;
    corection = false;
    sensorTrigger = SafetyTriger::NONE;
    CheckSensors();
}

void SafetyModule::process(const MovementRequest &req)
{
    motor.execute(req);
}

void SafetyModule::reset()
{
    current = MovementRequest(MoveType::Stop, 0);
    elapsed = 0;
    active = false;
    Ready = true;
    corection = false;
    sensorTrigger = SafetyTriger::NONE;
    motor.stop();
    bool b = CheckSensors();
}

void SafetyModule::startRequest(const MovementRequest &req)
{
     Serial.print("[REQUEST] type=");
    Serial.print((int)req.type);
    Serial.print(" time=");
    Serial.println(req.time);

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
    case MoveType::Stop:
        motor.stop();
        break;
    default:
        break;
    }
}
void SafetyModule::STOP_MOTORS()
{
    motor.stop();
}

int SafetyModule::update(float dt)
{
    
    Serial.print("[SAFETY] active=");
    Serial.print(active);
    Serial.print(" Ready=");
    Serial.print(Ready);
    Serial.print(" corection=");
    Serial.print(corection);
    Serial.print(" elapsed=");
    Serial.print(elapsed);
    Serial.print(" trigger=");
    Serial.println((int)sensorTrigger);

    // Здесь можно добавить проверки датчиков безопасности
    if (!active && !Ready && sensorTrigger != SafetyTriger::NONE)
    {
        // if (Ready)
        //     return 1;
        // else
        // {
            // if (sensorTrigger == SafetyTriger::NONE)
            //     return -1;
            corection = true;
            // current.time = 100;
            elapsed = 0;

            switch (sensorTrigger)
            {
            case SafetyTriger::SENSOR_LEFT:
                startRequest(MovementRequest(MoveType::Backward, 100));
                active = true;
                break;
            case SafetyTriger::SENSOR_RIGHT:
                startRequest(MovementRequest(MoveType::Backward, 100));
                active = true;
                break;
            case SafetyTriger::SENSOR_BACK:
                startRequest(MovementRequest(MoveType::Forward, 100));
                active = true;
                break;
            case SafetyTriger::SENSOR_BACK_FLOW:
                startRequest(MovementRequest(MoveType::Forward, 100));
                active = true;
                break;
            case SafetyTriger::NONE: // sensorTrigger == 0
                startRequest(MovementRequest(MoveType::Stop, 10));
                Ready = true;
                corection = false;
                return 1;
                break;
            default:
                startRequest(MovementRequest(MoveType::Stop, 10));
                break;
            }
        // }
    }
    if (!corection)
        if (CheckSensors())
        {
            motor.stop();
            active = false;
            // return 0; // завершено аварийно
            Ready = false;
            return -1;
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