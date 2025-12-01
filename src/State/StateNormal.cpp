#include "StateNormal.h"
#include "Display/Sprite.h"
#include "Module/RTCModule.h"

StateNormal::StateNormal(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12)
{
}
StateNormal::StateNormal(DisplaySystem &dispOld)
    : displayOld(&dispOld), spriteOld(&dispOld), sound(12)
{
}

void StateNormal::enter()
{
  
  display->clear();
  // display->drawText("Normal", 0, 0);
  
  timer = 5000;
}
void StateNormal::update(float dt)
{
  Draw(dt);
  sound.Update(dt);
}

StateCommand StateNormal::handleEvent(Event e)
{
  if (e.type == EVENT_MOTION)
  {
    display->clear();
    _time = RTCModule::getInstance().getTime();

    if (_time.hour() > 22 || _time.hour() < 6)
    {
      return CMD_TO_SLEEPY;
    }
  }

  sound.RtDt(15);
  return CMD_NONE;
}

void StateNormal::Draw(float dt)
{
  timer -= dt;
  if (IsOpen)
  {
    if (timer < 0)
    {
      IsOpen = false;
      timer = Close_Eyes;
      sprite.Draw(Emotions::NORMAL);
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