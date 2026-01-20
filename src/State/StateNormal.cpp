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
}
void StateNormal::update(float dt)
{
  SafetyModule::getInstance().update();
  ir.update();

  if (TouchButtons::getInstance().consume(3))
  {
    dance = false;
    // isDrawingBattery = !isDrawingBattery;
    // timer = 0; // обнуляем чтобы обновилось сразу
  }
  if (TouchButtons::getInstance().consume(2))
  {
    // IsDrawVolume = true;
    // timer = ApdateTimeConst;
    // _volume = sound.GetVolume();
    // if (_volume < 10)
    //   _volume++;
    // sound.SetVolume(_volume);
    // display->NeedUpdate = true;
  }
  if (TouchButtons::getInstance().consume(1))
  {
    // IsDrawVolume = true;
    // timer = ApdateTimeConst;
    // _volume = sound.GetVolume();
    // if (_volume > 0)
    //   _volume--;
    // sound.SetVolume(_volume);
    // display->NeedUpdate = true;
  }
  if (TouchButtons::getInstance().consume(0))
  {
    dance = true;
    // EventBus::push({EVENT_CHANGE_STATE, STATE_CLOCK});
  }

  IrLogic();
  Draw(dt);

  if (IsDrawVolume)
    DrawVolumeCount(dt);

  sound.Update(dt);

  if (dance)
    MovementModule::getInstance().MoveDance(dt);
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