#pragma once
#include <Arduino.h>

class TouchButtons {
public:
    static TouchButtons& getInstance() {
        static TouchButtons instance;
        return instance;
    }

    void begin();
    void update();
    bool consume(uint8_t id);

    bool wasToggled(uint8_t id);   // ← ОДИН МЕТОД !!!

    bool getState(uint8_t id) {   // вернуть текущее включено/выключено
        return toggleState[id];
    }

private:
    TouchButtons() {}

    static const uint8_t COUNT = 4;

    uint8_t pins[COUNT] = {22, 23, 24, 25};

    bool raw[COUNT];         // сырое состояние
    bool lastRaw[COUNT];     // предыдущее сырое состояние
    bool toggleState[COUNT]; // ВАЖНО: состояние-тумблер
    bool toggledFlag[COUNT]; // флаг на 1 кадр

    bool flagPressed[COUNT];
};
