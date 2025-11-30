#pragma once
#include <Arduino.h>
#include "Display/Sprite.h"

class Sound {
private:
    int pin;
    float timer;
    int longSound;

public:
    Sound(int piezoPin);

    void Update(float dt);
    // базовые звуки
	void RtDt(int Long);
};