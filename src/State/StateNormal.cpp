#include "StateNormal.h"


StateNormal::StateNormal(DisplayOled &disp)
    : display(&disp), sprite(&disp)//, sound(12)
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
  Draw(dt);
  // if (TouchButtons::getInstance().consume(3))
  // {
  //   isDrawingBattery = !isDrawingBattery;
  //   timer = 0; // обнуляем чтобы обновилось сразу
  // }
  // if (TouchButtons::getInstance().consume(2))
  // {
  //   IsDrawVolume = true;
  //   timer = ApdateTimeConst;
  //   _volume = sound.GetVolume();
  //   if (_volume < 10)
  //     _volume++;
  //   sound.SetVolume(_volume);
  //   display->NeedUpdate = true;
  // }
  // if (TouchButtons::getInstance().consume(1))
  // {
  //   IsDrawVolume = true;
  //   timer = ApdateTimeConst;
  //   _volume = sound.GetVolume();
  //   if (_volume > 0)
  //     _volume--;
  //   sound.SetVolume(_volume);
  //   display->NeedUpdate = true;
  // }
  // if (TouchButtons::getInstance().consume(0))
  // {
  //   EventBus::push({EVENT_CHANGE_STATE, STATE_CLOCK});
  // }

  // Draw(dt);

  // if (IsDrawVolume)
  //   DrawVolumeCount(dt);

  // sound.Update(dt);

  // MovementModule::getInstance().MoveDance(dt);
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

     // _time = RTCModule::getInstance().getTime();
      sprite.Draw(Emotions::BLINK);
      // char buffer[6]; // "HH:MM"
      // sprintf(buffer, "%02d:%02d", _time.hour(), _time.minute());
      // display->drawText(buffer, 0, 0, 2);
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

// void StateNormal::Draw(float dt)
// {
//   timer -= dt;
//   if (IsOpen)
//   {
//     if (timer < 0)
//     {
//       Serial.println(isDrawingBattery);

//       IsOpen = false;
//       timer = Close_Eyes;
//       sprite.Draw(Emotions::NORMAL);

//       if (isDrawingBattery)
//       {
//         //int precent = BatteryModule::getInstance().getBatteryPercent();
//         // drawBatteryIcon(0, 0, precent);
//         // drawBatteryPercent(110, 0, precent);
//       }
//       return;
//     }
//   }
//   else
//   {
//     if (timer < 0)
//     {
//       IsOpen = true;
//       timer = Open_Eyes;
//       sprite.Draw(Emotions::SLEEPY);

//       if (isDrawingBattery)
//       {
//         //int precent = BatteryModule::getInstance().getBatteryPercent();
//         // drawBatteryPercent(110, 0, precent);
//         // drawBatteryIcon(0, 0, precent);
//       }
//       return;
//     }
//   }
// }

void StateNormal::drawBatteryIcon(int x, int y, int percent)
{
  // Размеры батареи
  const int bodyWidth = 24;
  const int bodyHeight = 10;

  // Корпус
  display->drawRect(x, y, bodyWidth, bodyHeight, WHITE);

  // Клемма справа
  display->fillRect(x + bodyWidth, y + 3, 2, 4, WHITE);

  // Заполнение (внутри 22×8)
  percent = constrain(percent, 0, 100);
  int fillWidth = map(percent, 0, 100, 0, bodyWidth - 2);

  display->fillRect(x + 1, y + 1, fillWidth, bodyHeight - 2, WHITE);
}
void StateNormal::drawBatteryPercent(int x, int y, int percent)
{
  char buffer[5]; // "HH:MM"
  sprintf(buffer, "%d%s", percent, "%");
  display->drawText(buffer, x, y, 1);
}