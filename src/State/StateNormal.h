#pragma once
#include "Core/State.h"
#include "Display/DisplayOled.h"
#include "Display/SpriteOled.h"
//#include "Sound/SoundManager.h"
#include "Core/FSM.h"
//#include <RTClib.h>
//#include "Move/MovementModule.h"
//#include "Settings/GlobalSettings.h"
// #include "Module/RTCModule.h"
// #include "Module/BatteryModule.h"
// #include "Sensors/TouchButtons.h"

class StateNormal : public State {
public:
    StateNormal(DisplayOled& disp);
    
    void enter() override;
    void update(float dt) override;
    //StateCommand handleEvent(Event e) override;
    void Draw(float dt);

private:

    const float Open_Eyes = 10000;
    const float Close_Eyes = 1000;
    bool IsOpen;
    float timer;

    //DateTime _time;
    
    bool isDrawingBattery = true;
    void drawBatteryPercent(int x, int y, int percent);
    void drawBatteryIcon(int x, int y, int percent);

    void DrawClock(float dt);
    bool IsDrawClock = false;
    const float ApdateTimeConst = 1000;
    
    void DrawVolumeCount(float dt);
    bool IsDrawVolume = false;
    uint8_t _volume;
    
    DisplayOled* display;
    SpriteOled sprite;
    //Sound sound;
    float blinkTimer = 3000;
};