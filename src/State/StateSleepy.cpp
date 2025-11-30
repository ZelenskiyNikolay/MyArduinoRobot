#include "StateSleepy.h"
#include "Display/Sprite.h"
#include "Module/RTCModule.h"

StateSleepy::StateSleepy(DisplaySystem &disp)
    : display(&disp), sprite(&disp), sound(12)
{
}

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

    if (_time.hour() < 22 && _time.hour() > 6)
    {
      return CMD_TO_NORMAL;
    }
  }
  sound.RtDt(2);
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

      _time = RTCModule::getInstance().getTime();
      sprite.Draw(Emotions::BLINK);
      char buffer[6]; // "HH:MM"
      sprintf(buffer, "%02d:%02d", _time.hour(), _time.minute());
      display->drawText(buffer, 0, 0, 2);
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