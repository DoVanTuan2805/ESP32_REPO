#ifndef _INIT_H
#define _INIT_H

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h> /* https://github.com/PaulStoffregen/XPT2046_Touchscreen */

#define TFT_DC 2
#define _sclk 18
#define _mosi 23 /* 10K pull-up */
#define _miso 19
#define TFT_CS 15 /* 10K pull-up */
#define TFT_RST 4

#define TFT_BACKLIGHT_PIN 2 /* -via transistor- */
#define TOUCH_CS_PIN 5      /* 10K pull-up */
#define TOUCH_IRQ 27

#define RL1 32
#define RL2 33

const uint8_t TFT_ORIENTATION = 0;

static Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

static XPT2046_Touchscreen touch(TOUCH_CS_PIN, TOUCH_IRQ);

static TS_Point rawLocation;

void init_Screen();
void init_Touch();
void init_Relay();
// void init_Sensor();
void menu1();

#endif