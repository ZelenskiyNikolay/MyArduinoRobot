#pragma once
#include "State.h"
#include "Display/DisplaySystem.h"
#include "Display/Sprite.h"
#include "Display/SpriteOled.h"
#include "Sound/SoundManager.h"
#include "StateCommand.h"
#include <RTClib.h>
#include "Move/MovementModule.h"
#include "Move/SafetyModule.h"
#include "Settings/GlobalSettings.h"

class StateSleepy : public State
{
public:
    StateSleepy(DisplaySystem &disp);
    StateSleepy(DisplayOled &disp);

    void enter() override;
    void update(float dt) override;
    StateCommand handleEvent(Event e) override;
    void Draw(float dt);

private:
    const float Open_Eyes = 1000;
    const float Close_Eyes = 10000;
    bool IsOpen;
    float timer;

    void DrawClock(float dt);
    bool IsDrawClock = false;
    const float ApdateTimeConst = 1000;
    
    DateTime _time;
    DisplayOled *display;
    DisplaySystem *displayOld;
    Sprite spriteOld;
    SpriteOled sprite;
    Sound sound;
    float blinkTimer = 3000;
};