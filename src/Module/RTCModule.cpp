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
        Serial.println("RTC остановлен, устанавливаю текущее время...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    else
    {
        // Можно проверить, насколько RTC отличается от компиляционного времени
        DateTime now = rtc.now();
        DateTime compileTime(F(__DATE__), F(__TIME__));

        long diff = compileTime.unixtime() - now.unixtime();
        if (abs(diff) > 60)
        { // разница более 1 минуты
            Serial.print("Корректирую RTC, разница: ");
            Serial.println(diff);
            rtc.adjust(compileTime);
        }
    }
    currentTime = rtc.now();
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