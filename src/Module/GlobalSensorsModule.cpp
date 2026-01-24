#include "GlobalSensorsModule.h"

GlobalSensorsModule::GlobalSensorsModule() : light(32), sound(34)
{
    begin();
}

void GlobalSensorsModule::begin()
{
    light.update();
    sound.update();
    Serial.print("Свет: ");
    Serial.println(light.GetSensorState());
    Serial.print("Звук: ");
    Serial.println(sound.GetSensorState());
}

void GlobalSensorsModule::update(float dt)
{
    timer -= dt;
    if (timer < 0)
    {
        timer = UPDATETIME;
        light.update();
        sound.update();
    }
}
bool GlobalSensorsModule::GetLightSensor(){return light.GetSensorState();}
bool GlobalSensorsModule::GetSoundSensor(){return sound.GetSensorState();}