#include <Arduino.h>

#include <avr/wdt.h>


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

  wdt_enable(WDTO_1S); // Запускаем WDT
}

void loop()
{
  wdt_reset(); // Защита от зависаний Watchdog

  float dt = getDeltaTime();


  FpsCount(dt);

}

int freeMemory() {
  char top;
  extern int *__brkval;
  extern int __heap_start;
  return (int) &top - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
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
