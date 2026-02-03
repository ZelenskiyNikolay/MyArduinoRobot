#pragma once
#include "Sensors/TouchButtons.h"
#include "Core/State.h"
#include "Display/DisplayOled.h"
#include "Display/SpriteOled.h"
#include "Sensors/IRSensor.h"
#include "Move/SafetyModule.h"
#include "Settings/GlobalSettings.h"

enum LookState
{
    Redy,
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

    void SouthConfirm(float dt);
    bool ToSouthConfirm = false;
    int distance = 0;
    LookState SC = Redy;
    int itaration = 0;
    int measurements[3];
    bool Confirm = false;

    void RotateToSouth(float dt);
    bool RotateSouth = false;
    bool turnLeft = false;
    int angle = 0;

    bool edgeAlign = false;

    void MoveToEastDiscrete(float dt);
    LookState MoveToEast = Redy;
    int cur = 0;
    bool moveEast = false;

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