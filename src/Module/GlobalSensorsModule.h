#pragma once
#include <Arduino.h>
#include "Sensors/LightSensor.h"
#include "Sensors/SoundSensor.h"
#define UPDATETIME 100

class GlobalSensorsModule {
public:
    static GlobalSensorsModule& getInstance() {
        static GlobalSensorsModule instance;
        return instance;
    }

    void begin();
    void update(float dt);
    bool GetLightSensor();
    bool GetSoundSensor();
private:
    GlobalSensorsModule();
    uint8_t pin;
    float timer;

    LightSensor light;
    SoundSensor sound;
};