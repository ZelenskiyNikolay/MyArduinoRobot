#pragma once
#include "Sensors/TouchButtons.h"
#include "Core/State.h"
#include "Module/RTCModule.h"
#include "Module/GlobalSensorsModule.h"
#include "Display/DisplayOled.h"
#include "Display/SpriteOled.h"
#include "Sound/SoundManager.h"
#include "Module/BatteryModule.h"
#include "Settings/GlobalSettings.h"
#include "Core/EventBus.h"

enum MenuShow
{
    LABEL,
    BATARY
};


class StateStart : public State
{
public:
    StateStart(DisplayOled &disp);

    void enter() override;
    void update(float dt) override;
    void Draw(float dt);
private:
    void DrawLabel();
    void SensorBat();
    void drawBatteryIcon(int x, int y, int percent);

    MenuShow menu = MenuShow::LABEL;


    const float ApdateTimeConst = 30000;
    float timer;
    float _timerPoint;
    bool num_menu = false;
    bool showBattery = false;

    DateTime _time;

    DisplayOled *display;
    SpriteOled sprite;
    Sound sound;
};