#pragma once
#include <Arduino.h>

class RPM_sensor {
public:
    RPM_sensor(uint8_t pin);
    void begin();
    long GetSensorState();
    void ResetTicks();

    static void isrLeft();
    static void isrRight();

private:
    uint8_t SensorPin;
    volatile long ticks = 0;

    static RPM_sensor* leftInstance;
    static RPM_sensor* rightInstance;

    void handleInterrupt();
};