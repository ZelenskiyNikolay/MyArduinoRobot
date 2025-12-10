#pragma once
#include <Arduino.h>

class BatteryModule {
public:
    void begin(uint8_t pin);
    void update(float dt);
    float getVoltage() const;

private:
    uint8_t pin;
    float voltage = 0.0f;
    unsigned long lastUpdate = 0;
};