#include <Arduino.h>
#include "SafetyModule.h"

SafetyModule::SafetyModule()
    : motor(), sensorLeft(36), sensorRight(38), sensorBack(14), sensorBackFlow(15),
      ultrasonic(28, 3), leftEnc(18), rightEnc(19)
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

void SafetyModule::TriggerUltrasonic() { ultrasonic.Trigger(); }
float SafetyModule::GetDistance() { return ultrasonic.getDistance(); }

void SafetyModule::reset()
{
    current = MovementRequest(MoveType::Stop, 0);
    elapsed = 0;
    active = false;
    Ready = true;
    corection = false;
    sensorTrigger = SafetyTriger::NONE;
    motor.stop();
    CheckSensors();
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
    case MoveType::ForwardSteeps:
        ResetStips();
        break;
    case MoveType::Backward:
        motor.backward();
        break;
    case MoveType::Left:
        motor.left();
        break;
    case MoveType::Left90:
        ResetStips();
        break;
    case MoveType::Right:
        motor.right();
        break;
    case MoveType::Right90:
        ResetStips();
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

long SafetyModule::GetTics(bool left)
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
int SafetyModule::GetCorrections(bool left)
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
        if (current.type == MoveType::Right90)
        {
            return Turn90Right();
        }
        if (current.type == MoveType::ForwardSteeps)
        {
            return ForwardSteeps();
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
        if (current.type == MoveType::Forward)
            StartFinalAlign();
        if (FinalAlign() == -1 && current.type == MoveType::Forward)
            return -1;
        if (corection)
            corection = false;
        motor.stop();
        active = false;
        Ready = true;
        return 1; // завершено по времени
    }
    return -1; // еще выполняется
}
void SafetyModule::StartFinalAlign()
{
    motor.stop();
    alignActive = true;

    alignLeftStart = GetTics(true);
    alignRightStart = GetTics(false);

    alignTarget = alignRightStart - alignLeftStart;

    if (abs(alignTarget) >= 2)
    {
        alignTarget = abs(alignRightStart - alignLeftStart);
        if (alignLeftStart < alignRightStart)
        {
            alignWheel = LEFT;
        }
        else
        {
            alignWheel = RIGHT;
        }
    }
    else
    {
        alignActive = false;
    }
}
int SafetyModule::FinalAlign()
{
    if (!alignActive)
    {
        motor.stop();
        return 1;
    }

    const int alignSpeed = 150;

    int delta;

    if (alignWheel == LEFT)
    {
        if (GetTics() >= alignTarget) //&& GetTics(false) >= ticks90)
        {
            motor.stop();
            active = false;
            return 1; // завершено
        }
        motor.left(); // правое вперёд, левое назад
        return -1;    // ещё крутится
    }
    else
    {
        if (GetTics(false) >= alignTarget)
        {
            motor.stop();
            active = false;
            return 1; // завершено
        }
        motor.right(); // правое вперёд, левое назад
        return -1;     // ещё крутится
    }
}

int SafetyModule::Forward(int Left, int Right)
{
    SteepsLeft = Left;
    SteepsRight = Right;
    startRequest(MovementRequest(MoveType::ForwardSteeps, 100));
}
int SafetyModule::ForwardSteeps()
{
    if (GetTics() >= SteepsLeft)
    {
        motor.stopLeft();
    }
    if (GetTics() < SteepsLeft)
    {
        motor.forwardLeft();
    }
    if (GetTics(false) >= SteepsRight)
    {
        motor.stopRight();
    }
    if (GetTics(false) < SteepsRight)
    {
        motor.forwardRight();
    }
    if (GetTics() >= SteepsLeft && GetTics(false) >= SteepsRight)
    {
        motor.stop();
        active = false;
        return 1; // завершено
    }
    return -1;
}
int SafetyModule::Turn90Left()
{
    if (GetTics() >= ticks90Left) //&& GetTics(false) >= ticks90)
    {
        motor.stop();
        active = false;
        return 1; // завершено
    }
    motor.left(); // правое вперёд, левое назад
    return -1;    // ещё крутится
}
int SafetyModule::Turn90Right()
{
    if (GetTics(false) >= ticks90Right)
    {
        motor.stop();
        active = false;
        return 1; // завершено
    }
    motor.right(); // правое вперёд, левое назад
    return -1;     // ещё крутится
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