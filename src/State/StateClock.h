#pragma once
#include "State.h"
#include "Display/DisplaySystem.h"
#include "Display/DisplayOled.h"
#include "Display/Sprite.h"
#include "Display/SpriteOled.h"
#include "Sound/SoundManager.h"
#include "StateCommand.h"
//#include <RTClib.h>
#include "Module/RTCModule.h"

class StateClock : public State {
public:
    StateClock(DisplaySystem& dispOld);
    StateClock(DisplayOled& disp);
    
    void enter() override;
    void update(float dt) override;
    //StateCommand handleEvent(Event e) override;
    void Draw(float dt);

private:
    const float ApdateTimeConst = 1000;
    float timer;

    DateTime _time;

    DisplayOled* display;
    DisplaySystem* displayOld;
    Sprite spriteOld;
    SpriteOled sprite;
    Sound sound;
};