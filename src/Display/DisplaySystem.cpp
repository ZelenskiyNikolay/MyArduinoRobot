#include "DisplaySystem.h"

DisplaySystem::DisplaySystem(Adafruit_PCD8544 &d)
    : display(&d)
{
}

void DisplaySystem::clear()
{
    display->clearDisplay();
}

void DisplaySystem::drawText(const char *text, int x, int y, int size)
{
    display->setTextColor(BLACK);
    display->setTextSize(size);
    display->setCursor(x, y);
    display->println(text);
    NeedUpdate = true;
}

void DisplaySystem::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
    display->drawLine(x0, y0, x1, y1, color);
    NeedUpdate = true;
}
void DisplaySystem::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    display->fillCircle(x0, y0, r, color);
    NeedUpdate = true;
}
void DisplaySystem::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    display->drawCircle(x0, y0, r, color);
    NeedUpdate = true;
}
void DisplaySystem::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    display->fillRect(x, y, w, h, color);
    NeedUpdate = true;
}
void DisplaySystem::setTextSize(uint8_t size)
{
    display->setTextSize(size);
}
void DisplaySystem::setTextColor(uint16_t color)
{
    display->setTextColor(color);
}
void DisplaySystem::setCursor(int16_t x, int16_t y)
{
    display->setTextColor(x,y);
}
void DisplaySystem::println(const char *text)
{
    display->println(text);
    NeedUpdate = true;
}
void DisplaySystem::update()
{
    if (NeedUpdate)
    {
        display->display();
        NeedUpdate = false;
    }
}
