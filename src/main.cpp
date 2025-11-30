#include <Arduino.h>
#include "Core/EventBus.h"
#include "State/StateNormal.h"
#include "Display/DisplaySystem.h"
#include "Sensors/MotionSensor.h"
#include "State/FSM.h"

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "Module/RTCModule.h"

Adafruit_PCD8544 display(5, 6, 7, 8, 9);
DisplaySystem displaySys(display);

FSM fsm(new StateNormal(displaySys),&displaySys);
MotionSensor pir(30); //Pir sensor

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
  display.begin();
  display.setContrast(60);

  lastTime = millis();

  //fsm.changeState(&stSleepy);
  Serial.begin(9600);

  RTCModule::getInstance().begin();
}

void loop()
{
  float dt = getDeltaTime();

  pir.update();
  RTCModule::getInstance().update();
  // 1. собираем события (пока пусто, позже добавим датчики)
  while (EventBus::hasEvents())
  {
    fsm.handleEvent(EventBus::poll());
  }

  // 2. логика состояния
  fsm.update(dt);

  // 3. отрисовка
  displaySys.update();
  FpsCount(dt);
}

void FpsCount(float dt)
{
  callsPerSecond++;
  currentMillis += dt;
  if (currentMillis >= 1000) 
  {
    Serial.print("Вызовов в секунду: ");
    Serial.println(callsPerSecond);
    callsPerSecond = 0;
    currentMillis = 0;
  }    
}