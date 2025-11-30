#include "StateSleepy.h"
#include "Display/Sprite.h"


StateSleepy::StateSleepy(DisplaySystem& disp)
    : display(&disp),sprite(&disp),sound(12)
{}

void StateSleepy::enter()
{
  display->clear();
  display->drawText("StateSleepy 23-", 0, 0);
  display->drawText("23-06 hors", 0, 8);
}

void StateSleepy::update(float dt)
{
  Draw(dt);
  sound.Update(dt);
}

StateCommand StateSleepy::handleEvent(Event e)
{
  if (e.type == EVENT_MOTION)
  {
    sprite.Draw(Emotions::ANGRY);
    sound.RtDt(5);
    return CMD_TO_NORMAL;
  }
  return CMD_NONE;
}

void StateSleepy::Draw(float dt)
{
  timer -= dt;
  if (IsOpen)
  {
    if (timer < 0)
    {
      IsOpen = false;
      timer = Close_Eyes;
      sprite.Draw(Emotions::BLINK);
      return;
    }
  }
  else
  {
    if (timer < 0)
    {
      IsOpen = true;
      timer = Open_Eyes;

      sprite.Draw(Emotions::SLEEPY);
      return;
    }
  }
}