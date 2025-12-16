#include <Arduino.h>
#include "LightSensor.h"

LightSensor::LightSensor(int pin) : SensorPin(pin)
{
    pinMode(SensorPin, INPUT);

    lastState = digitalRead(SensorPin);
}

void LightSensor::update()
{
    lastState = digitalRead(SensorPin);
}
bool LightSensor::GetSensorState()
{
    return !lastState;
}