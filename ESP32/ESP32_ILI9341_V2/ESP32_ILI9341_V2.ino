#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h> /* https://github.com/PaulStoffregen/XPT2046_Touchscreen */
#include "define_Rect_Press.h"
#include "bitmap.h"
extern Adafruit_ILI9341 tft;

extern XPT2046_Touchscreen touch;

extern TS_Point rawLocation;

const int thermistorCooler = 36;
const int thermistorDefort = 39;

bool PAD_DOWN = false;
uint64_t timePress, timeShowScreen, timeReadTemp, timeSleppScreen;

typedef struct {
  uint16_t year;
  uint8_t day;
  uint8_t month;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} DateTime_t;
DateTime_t dateTime;

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
bool wifiCon = false;
int8_t int8SwitchPage = 0;
bool OnOffSystem = false;
bool OnOffDefort = true;

bool showSwitchPage = true;
void setup() {
  Serial.begin(115200);
  init_Screen();

  switchPage(showSwitchPage);
  init_Touch();
  init_Relay();

  dateTime.hour = 23;
  dateTime.minute = 30;
  dateTime.second = 59;

  dateTime.day = 14;
  dateTime.month = 10;
  dateTime.year = 2002;

  setting.int8DTemp = 3;
  setting.int8DEFCycle = 6;
  setting.int8DEFTime = 10;
  setting.int8DelayTime = 3;
  setting.int8DEFExitTemp = 5;

  Temperature.SetTemp = -10;
  // Temperature.RealTemp = -30.15;
  // Temperature.HeatTemp = -27.05;
}

void loop() {
  if (millis() - timeReadTemp >= 2000) {
    Temperature.RealTemp = readThermistor(thermistorCooler);
    Temperature.HeatTemp = readThermistor(thermistorDefort);
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
    if (page == PAGE2) {
      pressPage2(Pos.TouchX, Pos.TouchY);
    }
    PAD_DOWN = false;
  }
  if (PAD_DOWN == false && (millis() - timeSleppScreen >= 10000)) {
    // tft.sendCommand(0x10);  // Sleep
  }
}
