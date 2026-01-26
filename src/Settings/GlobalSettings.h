#pragma once
#include <Arduino.h>

struct SpacePoint
{
    int north;
    int south;
    int east;
    int west;
};

class GlobalSettings
{
public:
    static GlobalSettings &getInstance()
    {
        static GlobalSettings instance;
        return instance;
    }
    bool NOT_CHENGE_STATE = false;
    bool STATE_START = true;
    SpacePoint Point;
    // int Distance_X = 0;
    // int Distance_Y = 0;

private:
    GlobalSettings() {}
};