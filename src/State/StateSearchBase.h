#pragma once
#include "Sensors/TouchButtons.h"
#include "Core/State.h"
#include "Display/DisplayOled.h"
#include "Display/SpriteOled.h"
#include "Sensors/IRSensor.h"
#include "Move/SafetyModule.h"

enum LookState
{
    Redy,
   // Move,
    Triger,
    Distanse
};

class StateSearchBase : public State
{
public:
    StateSearchBase(DisplayOled &disp);

    void enter() override;
    void update(float dt) override;
    void Draw(float dt);

private:
    void IrLogic();
    void LookSouth(float dt);
    LookState Look = Redy;

    void RotateToSouth(float dt);
    bool RotateSouth = false;
    bool turnLeft = false;
    int angle = 0;

    bool edgeAlign = false;

    int maxDistance = 0;
    int bestStep = 0;
    int corner = 0;
    int currentStep = 0;

    bool lookSouth = false;
    float timer;
    DisplayOled *display;
    SpriteOled sprite;
    IRSensor ir;
};