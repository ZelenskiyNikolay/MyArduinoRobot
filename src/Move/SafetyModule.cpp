#include <Arduino.h>
#include "SafetyModule.h"

SafetyModule::SafetyModule()
    : motor(), sensorLeft(7), sensorRight(6), sensorBack(14), sensorBackFlow(15),
      ultrasonic(28, 26), leftEnc(18), rightEnc(19)
{
    leftEnc.begin();
    rightEnc.begin();
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
    case MoveType::Left90:
        ResetStips();
        //Turn90Left();
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

long SafetyModule::GetTics(bool left = true)
{
    if (left)
    {
        return leftEnc.GetSensorState();
    }
    else
    {
        return rightEnc.GetSensorState();
    }
}
int SafetyModule::GetCorrections(bool left = true)
{
    if (left)
    {
        return motor.corrLeft;
    }
    else
    {
        return motor.corrRight;
    }
}
void SafetyModule::ResetStips()
{
    leftEnc.ResetTicks();
    rightEnc.ResetTicks();
}
void SafetyModule::ResetCorrections()
{
    motor.ResetCorrection();
}

int SafetyModule::update(float dt)
{
    // Здесь можно добавить проверки датчиков безопасности
    if (!active && !Ready && sensorTrigger != SafetyTriger::NONE)
    {
        corection = true;

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
    }
    if (!corection)
    {
        if (current.type == MoveType::Left90)
        {
            return Turn90Left();
        }
        timer -= dt;
        if (timer < 0)
        {
            if (current.type == MoveType::Forward || current.type == MoveType::Backward)
                CorrectMove();
            timer = 100;
        }
        if (CheckSensors())
        {
            motor.stop();
            active = false;
            // return 0; // завершено аварийно
            Ready = false;
            return -1;
        }
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
int SafetyModule::Turn90Left()
{
    if (GetTics() >= ticks90) //&& GetTics(false) >= ticks90)
    {
        motor.stop();
        active = false;
        return 1; // завершено
    }
    motor.left(); // правое вперёд, левое назад
    return -1;    // ещё крутится
}
void SafetyModule::CorrectMove()
{
    const int k = 1; // коэффициент коррекции (2–6)
    const int deadzone = 1;

    int l = GetTics(true);
    int r = GetTics(false);

    int dl = l - prevLeftTicks;
    int dr = r - prevRightTicks;

    if (dl == 0 && dr == 0)
        return;

    prevLeftTicks = l;
    prevRightTicks = r;

    int error = dl - dr;

    if (active)
    {
        int speedL;
        int speedR;
        if (abs(error) > deadzone)
        {
            if (error > 0)
            {
                speedL = SPEED - k;
                speedR = SPEED + k;
            }
            else
            {
                speedL = SPEED + k;
                speedR = SPEED - k;
            }

            speedL = constrain(speedL, 0, 255);
            speedR = constrain(speedR, 0, 255);

            if (current.type == MoveType::Forward)
                motor.forward(speedL, speedR);
            else if (current.type == MoveType::Backward)
                motor.backward(speedL, speedR);
        }
    }
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