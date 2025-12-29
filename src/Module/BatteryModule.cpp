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

    //voltage *= 0.95f; //калибровка

    Serial.println(getVoltage());//Печать значения в порт
}

float BatteryModule::getVoltage() const {
    return voltage;
}
int BatteryModule::getBatteryPercent()
{
    
    float voltage = getVoltage();

    // Адаптируй под свой делитель!
    if (voltage > 4.0f) return 100;
    if (voltage < 3.40f) return 0;

    return map(voltage * 100, 340, 420, 0, 100);
}