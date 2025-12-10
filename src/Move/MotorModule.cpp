#include <Arduino.h>
#include "MovementRequest.h"
#include "MotorModule.h"

void MotorModule::init()
{
    pinMode(A1A, OUTPUT);
    pinMode(A1B, OUTPUT);
    pinMode(B1A, OUTPUT);
    pinMode(B1B, OUTPUT);
}

void MotorModule::execute(const MovementRequest &req)
{
    switch (req.type)
    {
    case MoveType::Forward:
        digitalWrite(A1A, HIGH);
        digitalWrite(A1B, LOW);
        digitalWrite(B1A, HIGH);
        digitalWrite(B1B, LOW);
        break;

    case MoveType::Backward:
        digitalWrite(A1A, LOW);
        digitalWrite(A1B, HIGH);
        digitalWrite(B1A, LOW);
        digitalWrite(B1B, HIGH);
        break;

    case MoveType::Left:
        digitalWrite(A1A, LOW);
        digitalWrite(A1B, HIGH);
        digitalWrite(B1A, HIGH);
        digitalWrite(B1B, LOW);
        break;

    case MoveType::Right:
        digitalWrite(A1A, HIGH);
        digitalWrite(A1B, LOW);
        digitalWrite(B1A, LOW);
        digitalWrite(B1B, HIGH);
        break;

    case MoveType::Stop:
    default:
        digitalWrite(A1A, LOW);
        digitalWrite(A1B, LOW);
        digitalWrite(B1A, LOW);
        digitalWrite(B1B, LOW);
        break;
    }
}

void MotorModule::forward()
{
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);
}

void MotorModule::backward()
{
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
}

void MotorModule::left()
{
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);
}

void MotorModule::right()
{
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
}

void MotorModule::stop()
{
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, LOW);
}
