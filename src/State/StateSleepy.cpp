#include "StateSleepy.h"
#include "Display/Sprite.h"
#include "Module/RTCModule.h"
#include "Sensors/TouchButtons.h"

StateSleepy::StateSleepy(DisplaySystem &disp)
    : displayOld(&disp), spriteOld(&disp), sound(12)
{
}
StateSleepy::StateSleepy(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12)
{
}

void StateSleepy::enter()
{
  display->clear();
  // display->setContrast();
  sprite.Draw(Emotions::SLEEPY);
}

void StateSleepy::update(float dt)
{
  IsDrawClock = TouchButtons::getInstance().consume(0);

  if (!IsDrawClock)
    Draw(dt);
  else
    DrawClock(dt);
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
void StateSleepy::DrawClock(float dt)
{
  timer -= dt;
  if (timer < 0)
  {
    display->clear();
    timer = ApdateTimeConst;
    _time = RTCModule::getInstance().getTime();
    char buffer[6]; // "HH:MM"
    sprintf(buffer, "%02d:%02d", _time.hour(), _time.minute());
    display->drawText(buffer, 0, 0, 4);
  }
  else
  {

  }
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