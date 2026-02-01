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

    stop();
}

void MotorModule::forward()
{
    analogWrite(A1A, SPEED + corrLeft);
    analogWrite(A1B, 0);
    analogWrite(B1A, SPEED + corrRight);
    analogWrite(B1B, 0);
}
void MotorModule::forward(int Left, int Right)
{
    analogWrite(A1A, corrLeft + Left);
    analogWrite(A1B, 0);
    analogWrite(B1A, corrRight + Right);
    analogWrite(B1B, 0);
}
void MotorModule::forwardLeft()
{
    analogWrite(A1A, SPEED + corrLeft);
    analogWrite(A1B, 0);
}
void MotorModule::forwardRight()
{
    analogWrite(B1A, SPEED + corrRight);
    analogWrite(B1B, 0);
}
void MotorModule::backward()
{
    digitalWrite(A1A, LOW);
    analogWrite(A1B, SPEED + corrLeft);
    digitalWrite(B1A, LOW);
    analogWrite(B1B, SPEED + corrRight);
}
void MotorModule::backwardLeft()
{
    analogWrite(A1A, 0);
    analogWrite(A1B, SPEED);
}
void MotorModule::backwardRight()
{
    analogWrite(B1A, 0);
    analogWrite(B1B, SPEED);
}
void MotorModule::backward(int Left, int Right)
{
    digitalWrite(A1A, LOW);
    analogWrite(A1B, corrLeft + Left);
    digitalWrite(B1A, LOW);
    analogWrite(B1B, corrRight + Right);
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
    analogWrite(A1A, 0);
    analogWrite(A1B, 0);
    analogWrite(B1A, 0);
    analogWrite(B1B, 0);
}
void MotorModule::stopLeft()
{
    analogWrite(A1A, 0);
    analogWrite(A1B, 0);
}
void MotorModule::stopRight()
{
    analogWrite(B1A, 0);
    analogWrite(B1B, 0);
}
