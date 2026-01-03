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

        long duration = pulseIn(echoPin, HIGH, 15000);
        if (duration == 0) return -1; // нет сигнала

        return duration * 0.0343f / 2.0f;
    }

/*
    C++

// В UltrasonicModule.h добавь волатильные переменные
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseEnd = 0;
volatile bool newDistanceReady = false;

// Обработчик прерывания (вызывается сам, когда меняется уровень на Echo)
void echoHandler() {
    if (digitalRead(ECHO_PIN) == HIGH) {
        pulseStart = micros();
    } else {
        pulseEnd = micros();
        newDistanceReady = true;
    }
}

// В update() или GetDistance()
void UltrasonicModule::trigger() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
}

float UltrasonicModule::readDistance() {
    if (newDistanceReady) {
        newDistanceReady = false;
        long duration = pulseEnd - pulseStart;
        return duration * 0.0343f / 2.0f;
    }
    return -1; // Еще не готово или нет сигнала
}
    */