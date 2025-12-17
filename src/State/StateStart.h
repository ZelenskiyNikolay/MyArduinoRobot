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

enum MenuSelection{
    NORMAL_SCENE,
    SLEEPY_SCENE,
    CLOCK_SCENE
};

class StateStart : public State {
public:
    StateStart(DisplaySystem& dispOld);
    StateStart(DisplayOled& disp);
    
    void enter() override;
    void update(float dt) override;
    void Draw(float dt);

private:
    MenuSelection menu = MenuSelection::NORMAL_SCENE;

    const float ApdateTimeConst = 30000;
    float timer;
    float _timerPoint;
    bool num_menu = false;

    DateTime _time;

    DisplayOled* display;
    DisplaySystem* displayOld;
    Sprite spriteOld;
    SpriteOled sprite;
    Sound sound;
};