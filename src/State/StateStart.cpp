#include "StateStart.h"

StateStart::StateStart(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12)
{
}

void StateStart::enter()
{
    sound.SoundStop();
    display->clear();
    timer = 0;

    display->drawText("  ROBIK", 0, 0, 2);
    display->drawText("              v1.2b", 0, 20, 1);
    display->drawText("press 3 Battary %", 0, 45, 1);
    display->drawText("press 1 to start.", 0, 55, 1);

    num_menu = false;
}
void StateStart::update(float dt)
{
    PowerModule &power = PowerModule::getInstance();
    BatteryModule &bat = BatteryModule::getInstance();

    if(bat.getBatteryPercent() < 99)
        if (power.State == POWER_EXTERNAL && power.Charging == CHARGING)
        {
            if (menu != BATARY_CHARGING)
            {
                sound.RtDt(2);
                menu = BATARY_CHARGING;
                num_menu = true;
                timer = 0;
            }
        }
        else
        {
            if (menu == BATARY_CHARGING)
            {
                menu = LABEL;
                num_menu = false;
                sound.RtDt(2);
            }
        }

    if (!num_menu)
    {
        if (TouchButtons::getInstance().consume(0))
        {

            EventBus::push({EVENT_CHANGE_STATE, STATE_CALIBRATION});
        }

        if (TouchButtons::getInstance().consume(2))
        {
            sound.RtDt(5);
            menu = BATARY;
            num_menu = true;
            timer = 0;
        }
    }
    else if (num_menu)
    {
        if (TouchButtons::getInstance().consume(3))
        {
            menu = LABEL;
            num_menu = false;
            sound.RtDt(7);
        }
    }
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

        if (menu == BATARY)
            SensorBat();
        else if (menu == LABEL)
            DrawLabel();
        else if (menu == BATARY_CHARGING)
            ChargeBat();
    }
}
void StateStart::DrawLabel()
{
    display->clear();

    display->drawText("  ROBIK", 0, 0, 2);
    display->drawText("              v1.2b", 0, 20, 1);
    display->drawText("press 3 Battary %", 0, 45, 1);
    display->drawText("press 1 to start.", 0, 55, 1);
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
void StateStart::ChargeBat()
{

    display->drawText("CHARGING BATTERY:", 0, 0, 1);
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