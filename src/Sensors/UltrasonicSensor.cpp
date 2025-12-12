#include "UltrasonicSensor.h"



    void UltrasonicModule::begin() {
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }

    float UltrasonicModule::getDistance() {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        long duration = pulseIn(echoPin, HIGH, 20000);
        if (duration == 0) return -1; // нет сигнала

        return duration * 0.0343f / 2.0f;
    }
