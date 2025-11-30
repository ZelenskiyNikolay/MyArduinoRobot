#include "MotionSensor.h"
#include <Arduino.h>

MotionSensor::MotionSensor(int pin) : pirPin(pin)
{
    pinMode(pirPin, INPUT);
    lastState = LOW;
}

void MotionSensor::update()
{
    bool motion = digitalRead(pirPin);
    // Сработал впервые → отправляем событие
    if (motion && !lastState)
    {
        EventBus::push({EVENT_MOTION});
    }

    lastState = motion;
}