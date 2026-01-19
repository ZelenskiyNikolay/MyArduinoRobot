#include "UltrasonicSensor.h"

volatile unsigned long UltrasonicModule::echoStart = 0;
volatile unsigned long UltrasonicModule::echoTime = 0;
volatile bool UltrasonicModule::newDistanceReady = false;

void UltrasonicModule::handleEcho() {
    if (digitalRead(3) == HIGH) {
        echoStart = micros();
    } else {
        echoTime = micros() - echoStart;
        newDistanceReady = true;
    }
}

void UltrasonicModule::begin()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    if (echoPin == 3)
    {
        attachInterrupt(digitalPinToInterrupt(3), handleEcho, CHANGE);
    }
}
void UltrasonicModule::Trigger() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
}
float UltrasonicModule::getDistance() {
    if (newDistanceReady) {
        newDistanceReady = false;
        // echoDuration — это уже разница во времени!
        float dist = (float)echoTime * 0.0343f / 2.0f;
        
        // Ограничение: если датчик выдает мусор (больше 4 метров)
        if (dist > 400.0f || dist < 2.0f) return -1.0f; 
        
        return dist;
    }
    return -2.0f; // Сигнал еще не вернулся
}