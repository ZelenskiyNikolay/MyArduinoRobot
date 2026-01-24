//"Release v1.1: restored functionality, calibration, safety correction, dance, IR control"
#include "Incledes.h"


void FpsCount(float dt);

unsigned long lastTime;
float currentMillis;
int callsPerSecond;

float getDeltaTime()
{
  unsigned long now = millis();
  unsigned long dt = now - lastTime;
  lastTime = now;

  return dt;
}

void setup()
{
  byte status = MCUSR;
  MCUSR = 0;     // сброс флагов причины ресета
  wdt_disable(); // отключаем WDT сразу

  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.begin(9600);
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  lastTime = millis();
  Serial.begin(9600);

  RTCModule::getInstance().begin();
  TouchButtons::getInstance().begin();
  
  fsm = new FSM(new StateStart(displaySys), &displaySys);

  BatteryModule::getInstance().begin(A0);
  PowerModule::getInstance().begin();
  GlobalSensorsModule::getInstance().begin();
  wdt_enable(WDTO_1S); // Запускаем WDT
}

void loop()
{
  wdt_reset(); // Защита от зависаний Watchdog

  float dt = getDeltaTime();

  RTCModule::getInstance().update(dt);
  TouchButtons::getInstance().update();
  GlobalSensorsModule::getInstance().update(dt);

  while (EventBus::hasEvents())
  {
    fsm->handleEvent(EventBus::poll());
  }

  // 2. логика состояния
  fsm->update(dt);

  // 3. отрисовка
  displaySys.update();
  
  BatteryModule::getInstance().update(dt);
  PowerModule::getInstance().update(dt);

  FpsCount(dt);
}

int freeMemory()
{
  char top;
  extern int *__brkval;
  extern int __heap_start;
  return (int)&top - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void FpsCount(float dt)
{
  callsPerSecond++;
  currentMillis += dt;
  if (currentMillis >= 1000)
  {
    Serial.print("Вызовов в секунду: ");
    Serial.print(callsPerSecond);
    Serial.print(" Память: ");
    Serial.println(freeMemory());
    callsPerSecond = 0;
    currentMillis = 0;
  }
}
