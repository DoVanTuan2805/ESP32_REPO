#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include "define_Rect_Press.h"
#include "bitmap.h"
#define BLYNK_TEMPLATE_ID "TMPL6tZTCwoCv"
#define BLYNK_TEMPLATE_NAME "COOLE DEFORT"
#define BLYNK_AUTH_TOKEN "qAEwLENmfqZ6maiBYGus1jbB4WAtUB5v"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include "EEPROM.h"
/*  BLYNK */
WidgetRTC rtc;
BlynkTimer timerRTC, timerReconnect, timerPushTempBlynk, timerPushSetBlynk;
/*  LCD   */
extern Adafruit_ILI9341 tft;
extern XPT2046_Touchscreen touch;
extern TS_Point rawLocation;
/*  SENSOR   */
const int thermistorCooler = 36;
const int thermistorDefort = 39;

#define RL_COOLER 32
#define RL_DEFORT 33

#define SECOND_TIME 1
#define MINUTE_TIME 60
#define HOUR_TIME 3600

bool PAD_DOWN = false;
uint64_t timePress, timeShowScreen, timeReadTemp, timeSleppScreen, timeDefort, timeCycle;

typedef struct {
  uint16_t year;
  uint8_t day;
  uint8_t month;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} DateTime_t;
DateTime_t dateTime, dateTimeLast;

typedef struct {
  int TouchX;
  int TouchY;
} Position_t;
Position_t Pos;

typedef struct {
  int8_t SetTemp;
  float RealTemp;
  float HeatTemp;
} Temperature_t;
Temperature_t Temperature;

typedef struct {
  int8_t int8DTemp;         // RANGE RUN RELAY COOLER
  uint8_t int8DEFCycle;     // TIME HOUR DEFORT
  uint8_t int8DEFTime;      // TIME MINUTE COOLER
  uint8_t int8DelayTime;    // DELAY PROCESS
  uint8_t int8DEFExitTemp;  // TEMP EXIT DEFORT
} Setting_t;
Setting_t setting;

typedef enum {
  MAIN_PAGE2,
  STemp,
  DTemp,
  DEFCycle,
  DEFTime,
  DelayTime,
  DEFExitTemp
} Mode_t;
Mode_t mode;

typedef struct {
  bool Up;
  bool Down;
  bool Ok;
} Choose_t;
Choose_t Choose;

typedef enum {
  PAGE1 = 0,
  PAGE2 = 1,
  PAGE3 = 2
} Page_t;
Page_t page;
float saiso_cb_cooler = 0;
float saiso_cb_defort = 0;

bool wifiCon = false;
int8_t int8SwitchPage = 0;

bool OnOffSystem = false;
bool OnOffDefort = false;
bool OnOffCooler = false;
bool OnOffOverViewDEF = false;

bool showSwitchPage = true;
/*  TIME  FOR DEFORT  */
uint64_t minuteNow;
uint64_t minuteLast;
void setup() {
  Serial.begin(115200);
  init_Screen();

  switchPage(showSwitchPage);
  init_Touch();
  init_Relay();
  setupWiFi();
  init_setting();

  timerReconnect.setInterval(5000L, connectionstatus);
  timerPushTempBlynk.setInterval(1000L, pushTempToBlynk);
  timerPushSetBlynk.setInterval(4000L, pushSettingToBlynk);
  timerRTC.setInterval(1000L, getTimeBlynk);
  Serial.println("START");
}

void loop() {
  Blynk.run();
  timerReconnect.run();
  timerPushTempBlynk.run();
  timerPushSetBlynk.run();
  timerRTC.run();

  Button_config_Wifi();
  // uartHandle();
  processCooler();
  processDefort();
  if (millis() - timeReadTemp >= 2000) {
    Temperature.RealTemp = readThermistor(thermistorCooler) + saiso_cb_cooler;
    Temperature.HeatTemp = readThermistor(thermistorDefort) + saiso_cb_defort;
    timeReadTemp = millis();
  }
  if (millis() - timeShowScreen >= 500) {
    switchPage(showSwitchPage);
    if (page == PAGE1) {
      showPage1();
    }
    if (page == PAGE2) {
      if (mode == MAIN_PAGE2) {
        showPage2();
      } else {
        screenAdjust();
        if (mode == STemp) {
          pageSetTemp();
        } else if (mode == DTemp) {
          pageDTemp();
        } else if (mode == DEFCycle) {
          pageDEFCycle();
        } else if (mode == DEFTime) {
          pageDEFTime();
        } else if (mode == DelayTime) {
          pageDelayTime();
        } else if (mode == DEFExitTemp) {
          pageDEFExitTemp();
        }
      }
    }
    if (page == PAGE3) {
      showPage3();
    }
    timeShowScreen = millis();
  }
  if (touch.tirqTouched()) {
    if (touch.touched()) {
      // tft.sendCommand(0x11); // Wake display
      rawLocation = touch.getPoint();
      Pos.TouchX = rawLocation.x;
      Pos.TouchY = rawLocation.y;
      Serial.print("x = ");
      Serial.print(Pos.TouchX);
      Serial.print(", y = ");
      Serial.print(Pos.TouchY);
      Serial.println();
      timePress = millis();
      timeSleppScreen = millis();
      PAD_DOWN = true;
    }
  }
  if (PAD_DOWN == true && (millis() - timePress >= 500)) {
    Serial.println("Press");
    pressSwitchPage(Pos.TouchX, Pos.TouchY);
    if (page == PAGE1) {
      pressPage1(Pos.TouchX, Pos.TouchY);
    }
    if (page == PAGE2) {
      pressPage2(Pos.TouchX, Pos.TouchY);
    }
    PAD_DOWN = false;
  }
  if (PAD_DOWN == false && (millis() - timeSleppScreen >= 10000)) {
    // tft.sendCommand(0x10);  // Sleep
  }
}
