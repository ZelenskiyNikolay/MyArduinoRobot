#include "StateNormal.h"
#include "Display/Sprite.h"
#include "Module/RTCModule.h"
#include "Sensors/TouchButtons.h"

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

  timer = 0;
}
void StateNormal::update(float dt)
{
  if (TouchButtons::getInstance().consume(2))
  {
    IsDrawVolume = true;
    timer = ApdateTimeConst;
    _volume = sound.GetVolume();
    if (_volume < 10)
      _volume++;
    sound.SetVolume(_volume);
  }
  if (TouchButtons::getInstance().consume(1))
  {
    IsDrawVolume = true;
    timer = ApdateTimeConst;
    _volume = sound.GetVolume();
    if (_volume > 0)
      _volume--;
    sound.SetVolume(_volume);
  }
  if (TouchButtons::getInstance().consume(0))
  {
    EventBus::push({EVENT_CHANGE_STATE, STATE_CLOCK});
  }

  Draw(dt);

  if (IsDrawVolume)
    DrawVolumeCount(dt);

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
  if (!IsDrawClock)
    sound.RtDt(15);
  return CMD_NONE;
}
void StateNormal::DrawVolumeCount(float dt)
{
  char buffer[7]; // "HH:MM"

  sprintf(buffer, "Vol:%02d", _volume);
  display->drawText(buffer, 0, 0, 2);
  timer -= dt;
  if (timer < 0)
    IsDrawVolume = false;
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