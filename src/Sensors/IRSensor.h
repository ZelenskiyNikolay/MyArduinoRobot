#pragma once
#include <Arduino.h>

enum ButtonIR
{
    NOOL,
    Button0,
    Button1,
    Button2,
    Button3,
    Button4,
    Button5,
    Button6,
    Button7,
    Button8,
    Button9
};

class IRSensor
{
public:
    IRSensor(int pin);
    void update();
    ButtonIR GetSensorState();

private:
    int SensorPin;
    ButtonIR lastState = NOOL;
};