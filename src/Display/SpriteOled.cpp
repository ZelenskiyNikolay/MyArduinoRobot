#include "SpriteOled.h"


void SpriteOled ::Draw(Emotions emotions)
{
    switch (emotions)
    {
    case NORMAL:
        drawEyes_Normal();
        break;

    case SLEEPY:
        drawEyes_Blink();
        break;

    case ANGRY:
        drawEyes_Angry();
        break;

    case SURPRISED:

        //_sound.RtDt(14);
        break;

    case HAPPY:

        //_sound.RtDt(15);
        break;

    case SAD:

        // _sound.RtDt(10);
        break;

    case LEFT_LOOK:

        break;

    case RIGHT_LOOK:

        break;

    case BLINK:
        drawEyes_Blink();
        break;

    case SHOW_TIME:

        // timer = Open_Eyes;
        break;
        // и т.д.
    default:
        break;
    }
}
void SpriteOled:: drawEyes_Normal()
{
    display->clear();

    display->drawCircle(35, 20, 15, SSD1306_WHITE);
    display->drawCircle(93, 20, 15, SSD1306_WHITE);

    display->fillCircle(35, 20, 9, SSD1306_WHITE);
    display->fillCircle(93, 20, 9, SSD1306_WHITE);

    display->fillRect(35, 62, 60, 4, SSD1306_WHITE);
}
void SpriteOled::drawEyes_Sleepy(){
    display->clear();
    // Левый глаз
    display->drawCircle(20, 15, 10, SSD1306_WHITE);   // наружное кольцо
    display->fillCircle(20, 15, 6, SSD1306_WHITE);    // зрачок

    // Правый глаз
    display->drawCircle(64, 15, 10, SSD1306_WHITE);  
    display->fillCircle(64, 15, 6, SSD1306_WHITE);    

    // Сонный эффект — закрытые веки
    display->fillRect(14, 9, 13, 6, SSD1306_WHITE);  // левый "веко"
    display->fillRect(58, 9, 13, 6, SSD1306_WHITE);  // правый "веко"

    // Рот (можно чуть опустить вниз, как у Normal)
    display->fillRect(20, 40, 50, 2, SSD1306_WHITE);
}

void SpriteOled::drawEyes_Angry() {
    display->clear();

    // Глаза
    display->drawCircle(20, 15, 10, SSD1306_WHITE);  // левый глаз
    display->fillCircle (20, 15, 6, SSD1306_WHITE);

    display->drawCircle(64, 15, 10, SSD1306_WHITE);  // правый глаз
    display->fillCircle(64, 15, 6, SSD1306_WHITE);

    // Брови — выше внешнего кольца глаза, двойная линия
    // Левая бровь
    display->drawLine(8, 3, 31, 7, SSD1306_WHITE);   // первая линия
    display->drawLine(8, 4, 31, 8, SSD1306_WHITE);   // вторая линия

    // Правая бровь
    display->drawLine(52, 7, 75, 2, SSD1306_WHITE);  // первая линия
    display->drawLine(52, 8, 75, 3, SSD1306_WHITE);  // вторая линия

    // Рот злой (как линия)
    display->fillRect(20, 40, 50, 2, SSD1306_WHITE);
}

void SpriteOled::drawEyes_Blink() {

    display->clear();

    // Глаза закрыты
    display->fillRect(20, 18, 30, 4, SSD1306_WHITE);  // левый
    display->fillRect(78, 18, 30, 4, SSD1306_WHITE);  // правый
	
	display->fillRect(35, 62, 60, 4, SSD1306_WHITE);
}