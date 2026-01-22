#pragma once
#include <Arduino.h>

#define PIN_CHRG A1
#define PIN_DONE A2
#define PIN_5V A3
#define UPDATE_TIME 100

enum PowerState {
    POWER_NO_UPDATE,
    POWER_BATTERY,
    POWER_EXTERNAL
};
enum PowerCHARGING {
    POWER_NO_UPDATE,
    POWER_CHARGING,
    POWER_DONE,
};

class PowerModule {
public:
    static PowerModule& getInstance() {
        static PowerModule instance;
        return instance;
    }
   void begin();
   void update(float dt); 
   PowerState State = PowerState::POWER_NO_UPDATE;
   PowerCHARGING Charging = PowerCHARGING::POWER_NO_UPDATE;
private:
    PowerModule(){};
    void DrawLog(float dt);
    float timer=0;
    float timerDraw = 100;
    bool isCharging = false;
    bool isDone = false;
    bool powerConect = false;
};