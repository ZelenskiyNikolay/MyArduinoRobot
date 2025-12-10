#include "StateClock.h"
#include "Sensors/TouchButtons.h"
#include "State.h"
#include "Module/RTCModule.h"

const char* weekDaysRU[] = {
  "Sun",  // 0
  "Mon",  // 1
  "Tue",  // 2
  "Wed",  // 3
  "Thu",  // 4
  "Fri",  // 5
  "Sat"   // 6
};

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
  sound.SoundStop();
  display->clear();
  timer = 0;
  _timerPoint = 20;
  Points = true;
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

void StateClock::Draw(float dt)
{
  int dow;
  timer -= dt;
  _timerPoint -= dt;
  if (timer <= 0)
  {
    _time = RTCModule::getInstance().getTime();
    timer = ApdateTimeConst;
  }
  if (_timerPoint <= 0)
  {
    Points = !Points;
    _timerPoint = 1000;
    display->clear();

    char buffer1[16];
    dow = _time.dayOfTheWeek();
    sprintf(buffer1, "%s  %02d/%02d",weekDaysRU[dow],_time.day(),_time.month());
    display->drawText(buffer1, 0, 0, 2);

    char buffer[6]; // "HH:MM"
    if (Points)
      sprintf(buffer, "%02d:%02d", _time.hour(), _time.minute());
    if (!Points)
      sprintf(buffer, "%02d %02d", _time.hour(), _time.minute());
    display->drawText(buffer, 5, 30, 4);
  }
}