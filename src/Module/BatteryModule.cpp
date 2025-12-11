#include "BatteryModule.h"

void BatteryModule::begin(uint8_t pin) {
    this->pin = pin;
}

void BatteryModule::update(float dt) {
    
    lastUpdate += dt;

    if (lastUpdate - dt < 20000) return;  // обновление раз в 20 секунд
        lastUpdate = 0;

    int raw = analogRead(pin);
    voltage = (raw / 1023.0f) * 5.0f;  // измеренное напряжение

      Serial.println(getVoltage());//Печать значения в порт
}

float BatteryModule::getVoltage() const {
    return voltage;
}
int BatteryModule::getBatteryPercent()
{
    
    float voltage = getVoltage();

    // Адаптируй под свой делитель!
    if (voltage > 4.18) voltage = 4.18;
    if (voltage < 3.20) voltage = 3.20;

    return map(voltage * 100, 320, 418, 0, 100);
}