#pragma once
#include <Arduino.h>

class UltrasonicModule {
private:
    int trigPin;
    int echoPin;

public:
    UltrasonicModule(int trig, int echo)
        : trigPin(trig), echoPin(echo)
    {}
     void begin();
     float getDistance();
};