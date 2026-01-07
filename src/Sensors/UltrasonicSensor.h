#pragma once
#include <Arduino.h>

class UltrasonicModule {
private:

    uint8_t trigPin;
    uint8_t echoPin;

public:
    static volatile unsigned long echoStart;
    static volatile unsigned long echoTime;
    static volatile bool newDistanceReady;

    static void handleEcho();
    void Trigger();  

    UltrasonicModule(int trig, int echo)
        : trigPin(trig), echoPin(echo)
    {}
     void begin();
     float getDistance();
};