#include "GlobalSensorsModule.h"

GlobalSensorsModule::GlobalSensorsModule() : light(18),sound(19)
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