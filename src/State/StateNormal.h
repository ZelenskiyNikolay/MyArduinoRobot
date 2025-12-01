#pragma once
#include "State.h"
#include "Display/DisplaySystem.h"
#include "Display/DisplayOled.h"
#include "Display/Sprite.h"
#include "Display/SpriteOled.h"
#include "Sound/SoundManager.h"
#include "StateCommand.h"
#include <RTClib.h>

class StateNormal : public State {
public:
    StateNormal(DisplaySystem& dispOld);
    StateNormal(DisplayOled& disp);
    
    void enter() override;
    void update(float dt) override;
    StateCommand handleEvent(Event e) override;
    void Draw(float dt);

private:

    const float Open_Eyes = 10000;
    const float Close_Eyes = 1000;
    bool IsOpen;
    float timer;

    DateTime _time;
    
    DisplayOled* display;
    DisplaySystem* displayOld;
    Sprite spriteOld;
    SpriteOled sprite;
    Sound sound;
    float blinkTimer = 3000;
};