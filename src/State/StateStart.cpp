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
            //EventBus::push({EVENT_CHANGE_STATE, STATE_SEARCH_BASE});
            EventBus::push({EVENT_CHANGE_STATE, STATE_CALIBRATION});
            //EventBus::push({EVENT_CHANGE_STATE, STATE_NORMAL});
        }

        if (TouchButtons::getInstance().consume(2))
        {
            sound.RtDt(5);
            menu = BATARY;
            num_menu = true;
            timer = 0;
        }
        if (TouchButtons::getInstance().consume(3))
        {
            menu = Time;
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
        else if (menu == Time)
            DrawClock(dt);
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
void StateStart::SensorBat()
{

    display->drawText("BATTERY SENSOR:", 0, 0, 1);
    char buffer1[16];
    int percent = BatteryModule::getInstance().getBatteryPercent();

    BatteryModule::getInstance().drawBatteryIcon(*display, 0, 10, percent);

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

    BatteryModule::getInstance().drawBatteryIcon(*display, 0, 10, percent);

    sprintf(buffer1, "Charge:%02d%s", percent, " %");
    display->drawText(buffer1, 0, 40, 1);

    float v = BatteryModule::getInstance().getVoltage();
    int whole = v;
    int fract = (v - whole) * 100;

    sprintf(buffer1, "Voltage:%d.%02d V", whole, fract);
    display->drawText(buffer1, 0, 50, 1);
}

void StateStart::DrawClock(float dt)
{

    display->clear();

    _time = RTCModule::getInstance().getTime();
    char buffer[9]; // "HH:MM"
    sprintf(buffer, "%02d:%02d", _time.hour(), _time.minute());

    Serial.print("RTC cached: ");
    Serial.print(_time.hour());
    Serial.print(":");
    Serial.println(_time.minute());

    display->drawText(buffer, 0, 0, 4);

}