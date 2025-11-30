#pragma once
#include "State.h"
#include "Display/DisplaySystem.h"
#include "Display/Sprite.h"
#include "Sound/SoundManager.h"
#include "StateCommand.h"


class StateSleepy : public State {
public:
    StateSleepy(DisplaySystem& disp);
    
    void enter() override;
    void update(float dt) override;
    StateCommand handleEvent(Event e) override;
    void Draw(float dt);

private:

    const float Open_Eyes = 1000;
    const float Close_Eyes = 10000;
    bool IsOpen;
    float timer;

    
    DisplaySystem* display;
    Sprite sprite;
    Sound sound;
    float blinkTimer = 3000;
};