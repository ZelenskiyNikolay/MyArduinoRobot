#include "StateSearchBase.h"

StateSearchBase::StateSearchBase(DisplayOled &disp)
    : display(&disp), sprite(&disp)//, sound(12)
{
}


void StateSearchBase::enter()
{
    display->clear();
    timer = 0;
}