#include "Sensors/TouchButtons.h"
#include "State.h"
#include "Module/RTCModule.h"
#include "Module/GlobalSensorsModule.h"
#include "Display/DisplaySystem.h"
#include "Display/DisplayOled.h"
#include "Display/Sprite.h"
#include "Display/SpriteOled.h"
#include "Sound/SoundManager.h"
#include "StateCommand.h"
#include "Module/BatteryModule.h"
#include "Settings/GlobalSettings.h"

enum MenuSelection
{
    NORMAL_SCENE,
    SLEEPY_SCENE,
    CLOCK_SCENE
};

enum TestMenu
{
    TEST_BATTERY_SENNSOR,
    TEST_SOUD_SENNSOR,
    TEST_LIGHT_SENNSOR,
    TEST_OPTICAL_SENNSORS
};

class StateStart : public State
{
public:
    StateStart(DisplaySystem &dispOld);
    StateStart(DisplayOled &disp);

    void enter() override;
    void update(float dt) override;
    void Draw(float dt);
private:
    void Menu();
    void Menu1();
    void SensorBat();
    void drawBatteryIcon(int x, int y, int percent);

    MenuSelection menu = MenuSelection::NORMAL_SCENE;
    TestMenu menu1 = TestMenu::TEST_BATTERY_SENNSOR;

    const float ApdateTimeConst = 30000;
    float timer;
    float _timerPoint;
    bool num_menu = false;
    bool sensor_menu = false;
    bool sensor_selected = false;

    DateTime _time;

    DisplayOled *display;
    DisplaySystem *displayOld;
    Sprite spriteOld;
    SpriteOled sprite;
    Sound sound;
};