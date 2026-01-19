#pragma once
#include <RTClib.h>

class RTCModule {
private:
    RTC_DS3231 rtc;
    unsigned long lastUpdate;
    unsigned long updateInterval;
    DateTime currentTime;

    RTCModule();

public:
    static RTCModule& getInstance();

    void begin();
    void setUpdateInterval(unsigned long intervalMs);
    void update();
    DateTime getTime();

    RTCModule(RTCModule const&) = delete;
    void operator=(RTCModule const&) = delete;
};