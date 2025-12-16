#pragma once

class SoundSensor {
public:
    SoundSensor(int pin);
    void update();
    bool GetSensorState();
private:
    int SensorPin;
    bool lastState = false;
};