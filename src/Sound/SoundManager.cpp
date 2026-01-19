#include "SoundManager.h"


Sound::Sound(int piezoPin)
{
    pin = piezoPin;
    pinMode(pin, OUTPUT);
}

uint8_t Sound::GetVolume() { return _volume; }

void Sound::SetVolume(uint8_t volume)
{
    _volume = volume;
}

void Sound::Update(float dt)
{
    if (longSound > 0)
    {
        timer -= dt;
        if (timer < 0)
        {
            if (toneAC_isPlaying_flag)
            {
                toneAC(random(600, 1600), _volume, random(20, 80), true);
                timer = random(10, 80);
                longSound--;
            }
        }
    }
    else
    {
        longSound = 0;
    }
}

void Sound::RtDt(int Long)
{
    longSound = Long;

    timer = random(10, 80);

    toneAC(random(600, 1600), _volume, random(20, 80), true);
}

void Sound::SoundStop()
{
    longSound = 0;
    noToneAC();
    digitalWrite(pin, LOW);
}
