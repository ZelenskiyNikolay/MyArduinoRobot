#pragma once
#include <Arduino.h>

class GlobalSettings{
public:
    static GlobalSettings &getInstance()
    {
        static GlobalSettings instance;
        return instance;
    }
    bool NOT_CHENGE_STATE = false;
    bool STATE_START = true;

    private:
    GlobalSettings(){}
};