#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 53

class SDModule
{
public:
    static SDModule &getInstance()
    {
        static SDModule instance;
        return instance;
    }
     void begin();
     // Метод для получения целого числа по ключу
    int getIntConfig(const char* key, int defaultValue);
    
    // Метод для получения float
    float getFloatConfig(const char* key, float defaultValue);

private:
    SDModule() {}
    bool CreateConfigFile();
};