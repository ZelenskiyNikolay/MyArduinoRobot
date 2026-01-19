#pragma once
#include <Arduino.h>
#include <toneAC.h>

extern "C" {
    extern unsigned long toneAC_isPlaying_flag; 
}
class Sound {
private:
    int pin;
    float timer;
    int longSound;
    uint8_t _volume=10;
public:
    Sound(int piezoPin);
    void SetVolume(uint8_t volume);
    uint8_t  GetVolume();
    void Update(float dt);
    // базовые звуки
	void RtDt(int Long);
    void SoundStop();

};