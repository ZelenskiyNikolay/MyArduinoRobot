#include "StateClock.h"
#include "Sensors/TouchButtons.h"
#include "State.h"

StateClock::StateClock(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12)
{
}
StateClock::StateClock(DisplaySystem &dispOld)
    : displayOld(&dispOld), spriteOld(&dispOld), sound(12)
{
}

void StateClock::enter()
{

  display->clear();
  timer = 0;
}


void StateClock::update(float dt)
{
  if (TouchButtons::getInstance().consume(0))
  {
    EventBus::push({EVENT_CHANGE_STATE, STATE_NORMAL});
  }

  Draw(dt);
  sound.Update(dt);
}

void StateClock::Draw(float dt){
timer -= dt;
  if (timer < 0)
  {
    _time = RTCModule::getInstance().getTime();
    timer = ApdateTimeConst;
    display->clear();
    char buffer[6]; // "HH:MM"
    sprintf(buffer, "%02d:%02d", _time.hour(), _time.minute());
    display->drawText(buffer, 5, 20, 4);
  }
}