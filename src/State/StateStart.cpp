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

    display->drawText("Start menu:", 0, 0, 2);
    display->drawText("1) TEST SCENE NUM", 0, 20, 1);
    display->drawText("2) Normal start", 0, 30, 1);
    display->drawText("3) Test sensors", 0, 40, 1);
}
void StateStart::update(float dt)
{
    if (!num_menu && !sensor_menu)
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
        if (TouchButtons::getInstance().consume(2))
        {
            sound.RtDt(2);
            sensor_menu = true;
            timer = 0;
        }
    }
    else if (num_menu)
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
            {
                GlobalSettings::getInstance().NOT_CHENGE_STATE = true;
                EventBus::push({EVENT_CHANGE_STATE, STATE_NORMAL});
            }
            else if (menu == MenuSelection::SLEEPY_SCENE)
            {
                GlobalSettings::getInstance().NOT_CHENGE_STATE = true;
                EventBus::push({EVENT_CHANGE_STATE, STATE_SLEEPY});
            }
            else if (menu == MenuSelection::CLOCK_SCENE)
            {
                GlobalSettings::getInstance().NOT_CHENGE_STATE = true;
                EventBus::push({EVENT_CHANGE_STATE, STATE_CLOCK});
            }
        }
    }
    else if (sensor_menu)
    {
        if (TouchButtons::getInstance().consume(0))
        {
            if (menu1 > 0)
            {
                menu1 = static_cast<TestMenu>(menu1 - 1);
            }
        }
        if (TouchButtons::getInstance().consume(1))
        {
            if (menu1 < TestMenu::TEST_OPTICAL_SENNSORS)
            {
                menu1 = static_cast<TestMenu>(menu1 + 1);
            }
        }
        if (TouchButtons::getInstance().consume(3))
        {
            sensor_menu = false;
            sensor_selected = true;
            timer = 0;
        }
    }
    else if (sensor_selected)
    {
        if (TouchButtons::getInstance().consume(0))
        {
            sensor_menu = false;
            sensor_selected = false;
            num_menu = false;
            enter();
            return;
        }
    }

    if (num_menu || sensor_menu || sensor_selected)
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

        if (num_menu)
            Menu();
        else if (sensor_menu)
            Menu1();
        else if (sensor_selected)
        {
            switch (menu1)
            {
            case TEST_BATTERY_SENNSOR:
                SensorBat();
                break;
            }
        }
    }
}

void StateStart::drawBatteryIcon(int x, int y, int percent)
{
    // Размеры батареи
    const int bodyWidth = 96;
    const int bodyHeight = 20;

    // Корпус
    display->drawRect(x, y, bodyWidth, bodyHeight, WHITE);

    // Клемма справа
    display->fillRect(x + bodyWidth, y + 3, 2, bodyHeight - 6, WHITE);

    // Заполнение (внутри 22×8)
    percent = constrain(percent, 0, 100);
    int fillWidth = map(percent, 0, 100, 0, bodyWidth - 2);

    display->fillRect(x + 1, y + 1, fillWidth, bodyHeight - 2, WHITE);
}
void StateStart::SensorBat()
{

    display->drawText("BATTERY SENSOR:", 0, 0, 1);
    char buffer1[16];
    int percent = BatteryModule::getInstance().getBatteryPercent();

    drawBatteryIcon(0, 10, percent);

    sprintf(buffer1, "Charge:%02d%s", percent, " %");
    display->drawText(buffer1, 0, 40, 1);

    float v = BatteryModule::getInstance().getVoltage();
    int whole = v;
    int fract = (v - whole) * 100;

    sprintf(buffer1, "Voltage:%d.%02d V", whole, fract);
    display->drawText(buffer1, 0, 50, 1);
}
void StateStart::Menu1()
{
    switch (menu1)
    {
    case TEST_BATTERY_SENNSOR:
        display->drawText("SELECT:", 0, 0, 1);
        display->drawText("->Battery sensor", 0, 10, 1);
        display->drawText("  Sound sensor", 0, 20, 1);
        display->drawText("  Light sensor", 0, 30, 1);
        display->drawText("  Optical sensor", 0, 40, 1);
        display->drawText("1)Up 2)Down 4)Select", 0, 56, 1);
        break;
    case TEST_SOUD_SENNSOR:
        display->drawText("SELECT:", 0, 0, 1);
        display->drawText("  Battery sensor", 0, 10, 1);
        display->drawText("->Sound sensor", 0, 20, 1);
        display->drawText("  Light sensor", 0, 30, 1);
        display->drawText("  Optical sensor", 0, 40, 1);
        display->drawText("1)Up 2)Down 4)Select", 0, 56, 1);
        break;
    case TEST_LIGHT_SENNSOR:
        display->drawText("SELECT:", 0, 0, 1);
        display->drawText("  Battery sensor", 0, 10, 1);
        display->drawText("  Sound sensor", 0, 20, 1);
        display->drawText("->Light sensor", 0, 30, 1);
        display->drawText("  Optical sensor", 0, 40, 1);
        display->drawText("1)Up 2)Down 4)Select", 0, 56, 1);
        break;
    case TEST_OPTICAL_SENNSORS:
        display->drawText("SELECT:", 0, 0, 1);
        display->drawText("  Battery sensor", 0, 10, 1);
        display->drawText("  Sound sensor", 0, 20, 1);
        display->drawText("  Light sensor", 0, 30, 1);
        display->drawText("->Optical sensor", 0, 40, 1);
        display->drawText("1)Up 2)Down 4)Select", 0, 56, 1);
        break;
    }
}
void StateStart::Menu()
{
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