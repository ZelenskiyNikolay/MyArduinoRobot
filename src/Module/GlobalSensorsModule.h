#pragma once
#include <Arduino.h>
#include "Sensors/LightSensor.h"
#include "Sensors/SoundSensor.h"

class GlobalSensorsModule {
public:
    static GlobalSensorsModule& getInstance() {
        static GlobalSensorsModule instance;
        return instance;
    }

    void begin();
    void update(float dt);
    float getVoltage() const;
    int getBatteryPercent();
private:
    GlobalSensorsModule();
    uint8_t pin;

    LightSensor light;
    SoundSensor sound;
};