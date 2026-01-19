#include "RTCModule.h"
#include <Wire.h>
#include <RTClib.h>

RTCModule::RTCModule() : lastUpdate(0), updateInterval(1000) {}

RTCModule &RTCModule::getInstance()
{
    static RTCModule instance;
    return instance;
}

void RTCModule::begin()
{
    if (!rtc.begin())
    {
        Serial.println("RTC не найден!");
        return;
    }

    if (rtc.lostPower())
    {
        Serial.println("RTC потерял питание! Время будет сброшено на дату компиляции.");
    }
    else
    {
        Serial.println("RTC работает, время сохранено.");
    }

    currentTime = rtc.now();
    Serial.print("Текущее время: ");
    Serial.println(currentTime.timestamp());

    //Установка часов
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void RTCModule::setUpdateInterval(unsigned long intervalMs)
{
    updateInterval = intervalMs;
}

void RTCModule::update()
{
    unsigned long now = millis();
    if (now - lastUpdate >= updateInterval)
    {
        currentTime = rtc.now();
        lastUpdate = now;
    }
}

DateTime RTCModule::getTime()
{
    return currentTime;
}