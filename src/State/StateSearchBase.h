#pragma once
#include "Sensors/TouchButtons.h"
#include "Core/State.h"
#include "Display/DisplayOled.h"
#include "Display/SpriteOled.h"

class StateSearchBase : public State
{
public:
    StateSearchBase(DisplayOled &disp);

    void enter() override;
    void update(float dt) override;
    void Draw(float dt);
private:
    float timer;
    DisplayOled *display;
    SpriteOled sprite;
};