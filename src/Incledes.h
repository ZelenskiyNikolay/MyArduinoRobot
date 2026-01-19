#pragma once
#include <Arduino.h>
#include <avr/wdt.h>
#include "Core/FSM.h"


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