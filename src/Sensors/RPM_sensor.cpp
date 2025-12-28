#include "RPM_sensor.h"

RPM_sensor* RPM_sensor::leftInstance = nullptr;
RPM_sensor* RPM_sensor::rightInstance = nullptr;

RPM_sensor::RPM_sensor(uint8_t pin) : SensorPin(pin) {}

void RPM_sensor::begin()
{
    pinMode(SensorPin, INPUT);

    if (SensorPin == 18) {
        leftInstance = this;
        attachInterrupt(digitalPinToInterrupt(SensorPin), isrLeft, RISING);
    }
    else if (SensorPin == 19) {
        rightInstance = this;
        attachInterrupt(digitalPinToInterrupt(SensorPin), isrRight, RISING);
    }
}

void RPM_sensor::handleInterrupt()
{
    static uint32_t lastTime = 0;
    uint32_t now = micros();

    if (now - lastTime > 800) {   // 500 мкс = защита от дребезга
        ticks++;
        lastTime = now;
    }
}

void RPM_sensor::isrLeft()
{
    if (leftInstance)
        leftInstance->handleInterrupt();
}

void RPM_sensor::isrRight()
{
    if (rightInstance)
        rightInstance->handleInterrupt();
}

long RPM_sensor::GetSensorState()
{
    return ticks;
}

void RPM_sensor::ResetTicks()
{
    ticks = 0;
}