#pragma once
#include <Arduino.h>

class BatteryModule {
public:
    static BatteryModule& getInstance() {
        static BatteryModule instance;
        return instance;
    }

    void begin(uint8_t pin);
    void update(float dt);
    float getVoltage() const;
    int getBatteryPercent();
private:
    BatteryModule(){}
    uint8_t pin;
    float voltage = 0.0f;
    unsigned long lastUpdate = 19000;
};