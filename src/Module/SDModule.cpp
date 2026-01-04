#include "SDModule.h"

void SDModule::begin()
{
    if (!SD.begin(SD_CS))
    {
        Serial.println("SD fail");
    }
    else
        Serial.println("SD Connect. SD OK!");
}

float SDModule::getFloatConfig(const char *key, float defaultValue)
{
    File configFile = SD.open("config.txt");
    if (!configFile){
        if(CreateConfigFile())
            return defaultValue;
    }

    float result = defaultValue;
    while (configFile.available())
    {
        String line = configFile.readStringUntil('\n');
        line.trim();

        if (line.startsWith(key))
        {
            int colonIndex = line.indexOf(':');
            if (colonIndex != -1)
            {
                String valuePart = line.substring(colonIndex + 1);
                valuePart.trim();
                result = valuePart.toFloat();
                break; // Нашли, выходим
            }
        }
    }
    configFile.close();
    return result;
}

int SDModule::getIntConfig(const char *key, int defaultValue)
{
    return (int)getFloatConfig(key, (float)defaultValue);
}
bool SDModule::CreateConfigFile()
{
    Serial.println(F("Writing /config.txt ..."));
    File file = SD.open("config.txt", FILE_WRITE);
  if (file) {
    file.println("speed: 180");
    file.println("angle: 90");
    file.close();
    Serial.println(F("Create config.txt"));
    return true;
  } else {
    Serial.println(F("Failed to open config.txt for writing!!! "));
    return false;
  }
}