#include "RTCModule.h"

RTCModule::RTCModule() : lastUpdate(0), updateInterval(1000) {}

RTCModule& RTCModule::getInstance() {
    static RTCModule instance;
    return instance;
}

void RTCModule::begin() {
    rtc.begin();
    currentTime = rtc.now();
}

void RTCModule::setUpdateInterval(unsigned long intervalMs) {
    updateInterval = intervalMs;
}

void RTCModule::update() {
    unsigned long now = millis();
    if (now - lastUpdate >= updateInterval) {
        currentTime = rtc.now();
        lastUpdate = now;
    }
}

DateTime RTCModule::getTime() {
    return currentTime;
}