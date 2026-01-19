
#include "IRSensor.h"
#include <IRremote.hpp>

IRSensor::IRSensor(int pin) : SensorPin(pin)
{
    pinMode(SensorPin, INPUT);
    IrReceiver.begin(SensorPin);
}

void IRSensor::update()
{
    if (IrReceiver.decode())
    {
        uint16_t cmd = IrReceiver.decodedIRData.command;

        switch (cmd)
        {
        case 0x16: // кнопка 1
            lastState = ButtonIR::Button1;
            break;

        case 0x19: // кнопка 2
            lastState = ButtonIR::Button2;
            break;

        case 0xD: // кнопка 3
            lastState = ButtonIR::Button3;
            break;

        case 0xC: // кнопка 4
            lastState = ButtonIR::Button4;
            break;

        case 0x18: // кнопка 5
            lastState = ButtonIR::Button5;
            break;

        case 0x5E: // кнопка 6
            lastState = ButtonIR::Button6;
            break;

        case 0x8: // кнопка 7
            lastState = ButtonIR::Button7;
            break;

        case 0x1C: // кнопка 8
            lastState = ButtonIR::Button8;
            break;

        case 0x5A: // кнопка 9
            lastState = ButtonIR::Button9;
            break;

        case 0x52: // кнопка 0
            lastState = ButtonIR::Button0;
            break;
            // и т.д.
        }
        IrReceiver.resume();
    }
}
ButtonIR IRSensor::GetSensorState()
{
    ButtonIR tmp = lastState;
    lastState = ButtonIR::NOOL;
    return tmp;
}