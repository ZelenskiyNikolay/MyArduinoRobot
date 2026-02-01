#include "StateNormal.h"

StateNormal::StateNormal(DisplayOled &disp)
    : display(&disp), sprite(&disp), sound(12), ir(A7)
{
}

void StateNormal::enter()
{
  display->clear();
  timer = 0;
  isDrawingBattery = true;
  sound.SoundStop();
}
void StateNormal::update(float dt)
{
  SafetyModule::getInstance().update();
  ir.update();

  if (TouchButtons::getInstance().consume(3))
  {
    timer = 0;
    DRAWBAT = !DRAWBAT;
  }
  if (TouchButtons::getInstance().consume(2))
  {
    Clock = !Clock;
  }
  if (TouchButtons::getInstance().consume(1))
  {
    EventBus::push({EVENT_CHANGE_STATE, STATE_START});
  }
  if (TouchButtons::getInstance().consume(0))
  {
    dance = !dance;
  }

  if (BatteryModule::getInstance().getBatteryPercent() < 40)
    DRAWBAT = true;

  // if (GlobalSensorsModule::getInstance().GetSoundSensor())
  //   SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 5, 5);

  // if (GlobalSensorsModule::getInstance().GetLightSensor())
  //   Light = true;
  // else if (!GlobalSensorsModule::getInstance().GetLightSensor() && steep == 4)
  // {
  //   Light = false;
  //   steep = 0;
  // }

  if (Light)
    LightReaction(dt);

  IrLogic();

  if (Clock)
    DrawClock(dt);
  else if (!DRAWBAT)
    Draw(dt);
  else if (DRAWBAT)
    LOWBat();

  if (IsDrawVolume)
    DrawVolumeCount(dt);

  sound.Update(dt);

  // if (dance)
  //   MovementModule::getInstance().MoveDance(dt);
}

void StateNormal::IrLogic()
{

  ButtonIR tmp = ir.GetSensorState();
  switch (tmp)
  {
  case Button1:
    SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, 0, 0);
    break;
  case Button2:
    SafetyModule::getInstance().NewMov(MotionState::FORWARD, 20, 20);
    break;
  case Button3:
    SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT, 0, 0);
    break;
  case Button4:
    SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT90);
    break;
  case Button6:
    SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT90);
    break;
  case Button5:
    SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 2, 2);
    break;
  case Button8:
    SafetyModule::getInstance().NewMov(MotionState::BACKWARD, 20, 20);
    break;
  case Button0:
    dance = !dance;
    break;

  default:
    break;
  }
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

      sprite.Draw(Emotions::NORMAL);
      return;
    }
  }
}
void StateNormal::LOWBat()
{
  display->clear();
  display->drawText("LOW BATTERY:", 0, 0, 1);
  char buffer1[16];
  int percent = BatteryModule::getInstance().getBatteryPercent();

  BatteryModule::getInstance().drawBatteryIcon(*display, 0, 10, percent);

  sprintf(buffer1, "Charge:%02d%s", percent, " %");
  display->drawText(buffer1, 0, 40, 1);

  float v = BatteryModule::getInstance().getVoltage();
  int whole = v;
  int fract = (v - whole) * 100;

  sprintf(buffer1, "Voltage:%d.%02d V", whole, fract);
  display->drawText(buffer1, 0, 50, 1);
}
void StateNormal::LightReaction(float dt)
{
  if (steep == 0)
  {
    SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, 0, 0);
    timer1 = 100;
    steep++;
    return;
  }
  if (steep == 1)
  {
    timer1 -= dt;
    if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
    {
      SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT, 0, 0);
      timer1 = 100;
      steep++;
      return;
    }
  }
  if (steep == 2)
  {
    timer1 -= dt;
    if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
    {
      SafetyModule::getInstance().NewMov(MotionState::TURN_LEFT, 0, 0);
      timer1 = 100;
      steep++;
      return;
    }
  }
  if (steep == 3)
  {
    timer1 -= dt;
    if (timer1 < 0 && !SafetyModule::getInstance().isBusy())
    {
      SafetyModule::getInstance().NewMov(MotionState::TURN_RIGHT, 0, 0);
      timer1 = 100;
      steep++;
      return;
    }
  }
}

void StateNormal::DrawClock(float dt)
{
  timer -= dt;
  if (timer < 0)
  {
    display->clear();
    timer = ApdateTimeConst;
    _time = RTCModule::getInstance().getTime();
    char buffer[9]; // "HH:MM"
    sprintf(buffer, "%02d:%02d", _time.hour(), _time.minute());
    display->drawText(buffer, 0, 0, 4);
  }
}