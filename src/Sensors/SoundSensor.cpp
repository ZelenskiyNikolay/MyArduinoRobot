#include <Arduino.h>
#include "SoundSensor.h"

SoundSensor::SoundSensor(int pin) : SensorPin(pin)
{
    pinMode(SensorPin, INPUT);

    lastState = digitalRead(SensorPin);
}

void SoundSensor::update()
{
    lastState = digitalRead(SensorPin);
}
bool SoundSensor::GetSensorState()
{
    return !lastState;
}