#include "StateNormal.h"
#include "Display/Sprite.h"


StateNormal::StateNormal(DisplaySystem& disp)
    : display(&disp),sprite(&disp),sound(12)
{}

void StateNormal::enter()
{
  //display->clear();
  //display->drawText("Normal", 0, 0);
  timer=0;
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
    display->drawText("Motion!", 0, 0);
    //return CMD_TO_SLEEPY;
  }
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
      sound.RtDt(15);
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
      sound.RtDt(5);
      sprite.Draw(Emotions::SLEEPY);
      return;
    }
  }
}