#include "TouchButtons.h"

void TouchButtons::begin()
{
    for (uint8_t i = 0; i < COUNT; i++)
    {
        pinMode(pins[i], INPUT);

        raw[i] = digitalRead(pins[i]);
        lastRaw[i] = raw[i];

        toggleState[i] = false;
        toggledFlag[i] = false;
    }
}

void TouchButtons::update()
{

    uint8_t portA_state = PINA;             // читаем сразу PORTA (пины 22..29)
    raw[0] = (portA_state & (1 << 0)) != 0; // пин 22 (A0)
    raw[1] = (portA_state & (1 << 1)) != 0; // пин 23 (A1)
    raw[2] = (portA_state & (1 << 2)) != 0; // пин 24 (A2)
    raw[3] = (portA_state & (1 << 3)) != 0; // пин 25 (A3)
    
    for (uint8_t i = 0; i < COUNT; i++)
    {

        // raw[i] = digitalRead(pins[i]); // active HIGH (твоя проверка 0 → 4.7V)

        if (raw[i] && !lastRaw[i])
        {
            flagPressed[i] = true;
        }

        lastRaw[i] = raw[i];
    }
}

// сцена проверяет флаг и сбрасывает
bool TouchButtons::consume(uint8_t id)
{
    if (flagPressed[id])
    {
        flagPressed[id] = false;
        return true;
    }
    return false;
}

bool TouchButtons::wasToggled(uint8_t id)
{
    return toggledFlag[id]; // вернёт true только 1 кадр
}
