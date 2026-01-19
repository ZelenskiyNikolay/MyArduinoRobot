#include "GlobalSensorsModule.h"

GlobalSensorsModule::GlobalSensorsModule() : light(32),sound(34)
{
    begin();
}

void GlobalSensorsModule::begin() {
    light.update();
    sound.update();
    Serial.print("Свет: ");
    Serial.println(light.GetSensorState());
    Serial.print("Звук: ");
    Serial.println(sound.GetSensorState());
}