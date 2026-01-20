#pragma once
#include "Core/State.h"
#include "Display/DisplayOled.h"
#include "Display/SpriteOled.h"
#include "Sound/SoundManager.h"
#include <RTClib.h>
#include "Move/MovementModule.h"
#include "Settings/GlobalSettings.h"
#include "Move/SafetyModule.h"
#include "Sensors/IRSensor.h"
#include "Sensors/TouchButtons.h"
#include "Module/SDModule.h"

class StateCalibration : public State {
public:
    StateCalibration(DisplayOled& disp);
    
    void enter() override;
    void update(float dt) override;
    void Draw(float dt);

private:
    float distance = 0;
    bool IsOpen;
    float timer;
    float timer1;

    int steep_calibration=0;

    DateTime _time;
    
    void ProcessCalibration(float dt);

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
    Sound sound;
    IRSensor ir;
    float blinkTimer = 3000;
};