#include "Sprite.h"

void Sprite ::Draw(Emotions emotions)
{
    switch (emotions)
    {
    case NORMAL:
        drawEyes_Normal();
        break;

    case SLEEPY:
        drawEyes_Sleepy();
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
void Sprite:: drawEyes_Normal()
{
    display->clear();
	display->drawCircle(20, 15, 10, BLACK);
	display->drawCircle(64, 15, 10, BLACK);

    display->fillCircle(20, 15, 6, BLACK);
    display->fillCircle(64, 15, 6, BLACK);
	
	display->fillRect(20, 40, 50, 2, BLACK);
}
void Sprite::drawEyes_Sleepy(){
    display->clear();
    // Левый глаз
    display->drawCircle(20, 15, 10, BLACK);   // наружное кольцо
    display->fillCircle(20, 15, 6, BLACK);    // зрачок

    // Правый глаз
    display->drawCircle(64, 15, 10, BLACK);  
    display->fillCircle(64, 15, 6, BLACK);    

    // Сонный эффект — закрытые веки
    display->fillRect(14, 9, 13, 6, WHITE);  // левый "веко"
    display->fillRect(58, 9, 13, 6, WHITE);  // правый "веко"

    // Рот (можно чуть опустить вниз, как у Normal)
    display->fillRect(20, 40, 50, 2, BLACK);
}
void Sprite::drawEyes_Blink() {
    display->clear();

    // Глаза закрыты
    display->fillRect(10, 15, 20, 2, BLACK);  // левый
    display->fillRect(54, 15, 20, 2, BLACK);  // правый
	
	display->fillRect(40, 35, 10, 8, BLACK);
}

void Sprite::drawEyes_Angry() {
    display->clear();

    // Глаза
    display->drawCircle(20, 15, 10, BLACK);  // левый глаз
    display->fillCircle (20, 15, 6, BLACK);

    display->drawCircle(64, 15, 10, BLACK);  // правый глаз
    display->fillCircle(64, 15, 6, BLACK);

    // Брови — выше внешнего кольца глаза, двойная линия
    // Левая бровь
    display->drawLine(8, 3, 31, 7, BLACK);   // первая линия
    display->drawLine(8, 4, 31, 8, BLACK);   // вторая линия

    // Правая бровь
    display->drawLine(52, 7, 75, 2, BLACK);  // первая линия
    display->drawLine(52, 8, 75, 3, BLACK);  // вторая линия

    // Рот злой (как линия)
    display->fillRect(20, 40, 50, 2, BLACK);
}