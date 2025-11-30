#pragma once
#include "Core/EventBus.h"

class MotionSensor {
public:
    MotionSensor(int pin);
    void update();

private:
    int pirPin;
    bool lastState = false;
};