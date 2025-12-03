#include <Arduino.h>
#include "Core/EventBus.h"
#include "State/StateNormal.h"
#include "State/StateSleepy.h"
#include "Display/DisplaySystem.h"
#include "Sensors/MotionSensor.h"
#include "Sensors/TouchButtons.h"
#include "State/FSM.h"
#include "Display/DisplayOled.h"
#include <SD.h>

#include <Adafruit_GFX.h>
// #include <Adafruit_PCD8544.h>
#include <Adafruit_SSD1306.h>

#include "Module/RTCModule.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Пины SPI OLED
#define OLED_MOSI 51
#define OLED_CLK 52
#define OLED_DC 8
#define OLED_CS 10
#define OLED_RESET 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         &SPI, OLED_DC, OLED_RESET, OLED_CS);
DisplayOled displaySys(display);

FSM *fsm = nullptr;

MotionSensor pir(30); // Pir sensor

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
  // display.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.begin(9600);
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // display.setContrast(60);
  display.clearDisplay();

  lastTime = millis();

  Serial.begin(9600);

  RTCModule::getInstance().begin();
  TouchButtons::getInstance().begin();

  fsm = new FSM(new StateNormal(displaySys), &displaySys);
}

void loop()
{

  float dt = getDeltaTime();

  pir.update();
  RTCModule::getInstance().update();

  TouchButtons::getInstance().update();

  // 1. собираем события (пока пусто, позже добавим датчики)
  while (EventBus::hasEvents())
  {
    fsm->handleEvent(EventBus::poll());
  }

  // 2. логика состояния
  fsm->update(dt);

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
