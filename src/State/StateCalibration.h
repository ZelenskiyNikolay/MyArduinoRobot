#pragma once
#include "State.h"
#include "Display/DisplaySystem.h"
#include "Display/DisplayOled.h"
#include "Display/Sprite.h"
#include "Display/SpriteOled.h"
#include "Sound/SoundManager.h"
#include "StateCommand.h"
#include <RTClib.h>
#include "Move/MovementModule.h"
#include "Settings/GlobalSettings.h"
#include "Move/SafetyModule.h"

class StateCalibration : public State {
public:
    StateCalibration(DisplaySystem& dispOld);
    StateCalibration(DisplayOled& disp);
    
    void enter() override;
    void update(float dt) override;
    //StateCommand handleEvent(Event e) override;
    void Draw(float dt);

private:

    bool IsOpen;
    float timer;
    float timer1;

    DateTime _time;
    
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
    DisplaySystem* displayOld;
    Sprite spriteOld;
    SpriteOled sprite;
    Sound sound;
    float blinkTimer = 3000;
};