#pragma once

class LightSensor {
public:
    LightSensor(int pin);
    void update();
    bool GetSensorState();
private:
    int SensorPin;
    bool lastState = false;
};