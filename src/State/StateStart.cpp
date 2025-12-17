#include "StateStart.h"

StateStart::StateStart(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12)
{
}
StateStart::StateStart(DisplaySystem &dispOld)
    : displayOld(&dispOld), spriteOld(&dispOld), sound(12)
{
}

void StateStart::enter()
{
    sound.SoundStop();
    display->clear();
    timer = 0;
    _timerPoint = 20;
    num_menu = false;

    display->drawText("Start menu:", 0, 0, 2);
    display->drawText("1) TEST SCENE NUM", 0, 20, 1);
    display->drawText("2) Normal start", 0, 30, 1);
}
void StateStart::update(float dt)
{
    if (!num_menu)
    {
        if (TouchButtons::getInstance().consume(0))
        {
            num_menu = true;
            timer = 0;
        }

        if (TouchButtons::getInstance().consume(1))
        {
            EventBus::push({EVENT_CHANGE_STATE, STATE_NORMAL});
        }
    }
    else
    {
        if (TouchButtons::getInstance().consume(0))
        {
            if (menu > 0)
            {
                // menu = static_cast<MenuSelection>(static_cast<int>(menu)-1);
                menu = static_cast<MenuSelection>(menu - 1);
            }
        }
        if (TouchButtons::getInstance().consume(1))
        {
            if (menu < MenuSelection::CLOCK_SCENE)
            {
                menu = static_cast<MenuSelection>(menu + 1);
            }
        }
        if (TouchButtons::getInstance().consume(3))
        {
            if (menu == MenuSelection::NORMAL_SCENE)
                EventBus::push({EVENT_CHANGE_STATE, STATE_NORMAL});
            else if (menu == MenuSelection::SLEEPY_SCENE)
                EventBus::push({EVENT_CHANGE_STATE, STATE_SLEEPY});
            if (menu == MenuSelection::CLOCK_SCENE)
                EventBus::push({EVENT_CHANGE_STATE, STATE_CLOCK});
        }
    }
    if (num_menu)
        Draw(dt);

    sound.Update(dt);
}

void StateStart::Draw(float dt)
{
    timer -= dt;
    if (timer <= 0)
    {
        timer = 500;
        display->clear();

        switch (menu)
        {
        case NORMAL_SCENE:
            display->drawText("SELECT:", 0, 0, 2);
            display->drawText("->Normal SCENE", 0, 20, 1);
            display->drawText("  SLEEPY SCENE", 0, 30, 1);
            display->drawText("  CLOCK SCENE", 0, 40, 1);
            display->drawText("1)Up 2)Down 4)Select", 0, 55, 1);
            break;
        case SLEEPY_SCENE:
            display->drawText("SELECT:", 0, 0, 2);
            display->drawText("  Normal SCENE", 0, 20, 1);
            display->drawText("->SLEEPY SCENE", 0, 30, 1);
            display->drawText("  CLOCK SCENE", 0, 40, 1);
            display->drawText("1)Up 2)Down 4)Select", 0, 55, 1);
            break;
        case CLOCK_SCENE:
            display->drawText("SELECT:", 0, 0, 2);
            display->drawText("  Normal SCENE", 0, 20, 1);
            display->drawText("  SLEEPY SCENE", 0, 30, 1);
            display->drawText("->CLOCK SCENE", 0, 40, 1);
            display->drawText("1)Up 2)Down 4)Select", 0, 55, 1);
            break;
        }
    }
}