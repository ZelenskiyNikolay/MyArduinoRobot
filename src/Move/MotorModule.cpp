#include <Arduino.h>
#include "MovementRequest.h"
#include "MotorModule.h"
#include "SafetyModule.h"
void MotorModule::init()
{
    pinMode(A1A, OUTPUT);
    pinMode(A1B, OUTPUT);
    pinMode(B1A, OUTPUT);
    pinMode(B1B, OUTPUT);

    // digitalWrite(A1A, LOW);
    // digitalWrite(A1B, LOW);
    // digitalWrite(B1A, LOW);
    // digitalWrite(B1B, LOW);

    SafetyModule::getInstance().reset();

    stop();
}
void MotorModule::execute(const MovementRequest &req)
{
    switch (req.type)
    {
    case MoveType::Forward:
        forward();
        break;

    case MoveType::Backward:
        backward();
        break;

    case MoveType::Left:
        left();
        break;

    case MoveType::Right:
        right();
        break;

    case MoveType::Stop:
        stop();
        break;
    }
}
void MotorModule::forward()
{
    analogWrite(A1A, SPEED);
    digitalWrite(A1B, LOW);
    analogWrite(B1A, SPEED);
    digitalWrite(B1B, LOW);
}

void MotorModule::backward()
{
    digitalWrite(A1A, LOW);
    analogWrite(A1B, SPEED);
    digitalWrite(B1A, LOW);
    analogWrite(B1B, SPEED);
}

void MotorModule::left()
{
    digitalWrite(A1A, LOW);
    analogWrite(A1B, SPEED);
    analogWrite(B1A, SPEED);
    digitalWrite(B1B, LOW);
}

void MotorModule::right()
{
    analogWrite(A1A, SPEED);
    digitalWrite(A1B, LOW);
    digitalWrite(B1A, LOW);
    analogWrite(B1B, SPEED);
}

void MotorModule::stop()
{
    // digitalWrite(A1A, LOW);
    // digitalWrite(A1B, LOW);
    // digitalWrite(B1A, LOW);
    // digitalWrite(B1B, LOW);
    analogWrite(A1A, 0);
    analogWrite(A1B, 0);
    analogWrite(B1A, 0);
    analogWrite(B1B, 0);
}
