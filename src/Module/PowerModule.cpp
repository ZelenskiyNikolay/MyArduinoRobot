#include "PowerModule.h"

void PowerModule::begin()
{
    pinMode(PIN_CHRG, INPUT);
    pinMode(PIN_DONE, INPUT);
    pinMode(PIN_5V, INPUT);
}

void PowerModule::update(float dt)
{
    timer -= dt;

    if (timer > 0)
        return;

    timer = UPDATE_TIME;
    isCharging = analogRead(PIN_CHRG)> 150; 
    //isDone = analogRead(PIN_DONE) > 500; // ~2.4В+
    powerConect = digitalRead(PIN_5V);

    if (powerConect)
    {
        State = PowerState::POWER_EXTERNAL;
        if (isCharging)
            Charging = PowerCHARGING::CHARGING;
        else if (!isCharging)
            Charging = PowerCHARGING::CHARGING_DONE;
    }
    else
    {
        State = PowerState::POWER_BATTERY;
        Charging = PowerCHARGING::NO_UPDATE;
    }

    DrawLog(dt);
}

void PowerModule::DrawLog(float dt)
{
    timerDraw -= dt;

    if (timerDraw > 0)
        return;

    timerDraw = 100;

    if (powerConect)
    {
        Serial.println("External power conect.");

        if (isCharging)
            Serial.println("Charging...");
        else if (!isCharging)
            Serial.println("Charge DONE");
    }
    else
        Serial.println("No external power");

}