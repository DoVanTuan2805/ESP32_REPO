#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h> /* https://github.com/PaulStoffregen/XPT2046_Touchscreen */
#include "define_Rect_Press.h"
extern Adafruit_ILI9341 tft;

extern XPT2046_Touchscreen touch;

extern TS_Point rawLocation;

float RealTemp = 31.9;
float HeatTemp = 27.6;

int thermistorCooler = 36;
int thermistorDefort = 39;
int Vo;  // Holds the ADC Value
float R2, tKelvin, tCelsius, tFahrenheit;
const float Beta = 3974.0;
const float roomTemp = 298.15;  // room temperature in Kelvin
const float Ro = 10000.0;       // Resistance of the thermistor at roomTemp
const float R1 = 9710.0;        // Resistnce of the known resistor

typedef struct {
  int SetTemp;
  uint8_t rangeTempMin;
  uint8_t hourCooler;
  uint8_t minuteDefort;
  uint8_t delayProcess;
} DataMode_t;
DataMode_t DataMode;
typedef enum {
  SET_TEMP = 0,
  RANGE_TEMP = 1,
  SET_HOUR_COOLER = 2,
  SET_MINUTE_DEFORT = 3,
  DELAY_TIME = 4,
  TEMP_EXIT_DEFORT = 5
} Mode_t;
Mode_t mode;
int mode_s = 0;
typedef struct {
  uint8_t hour;
  uint8_t minute;
} Time_t;
Time_t timeDefort, timeCooler;

bool PAD_DOWN = false;
int TouchX;
int TouchY;
bool tt = 0;
uint64_t timePress, timeReadTemp, timeShowScreen;

void setup() {
  Serial.begin(115200);
  init_Screen();

  RealTemp = readThermistor(thermistorCooler);
  HeatTemp = readThermistor(thermistorDefort);
  mode = SET_TEMP;
  showTemp(RealTemp, HeatTemp);
  timeDefort.hour = 2;
  timeDefort.minute = 20;

  timeCooler.hour = 1;
  timeCooler.minute = 50;

  DataMode.SetTemp = -10;
  DataMode.rangeTempMin = 3;
  DataMode.hourCooler = 6;
  DataMode.minuteDefort = 10;
  setTemp(DataMode.SetTemp);

  tft.fillRoundRect(20, 30, 70, 30, 5, ILI9341_CYAN);
  checkWifi(true);
  init_Touch();
  init_Relay();
  Serial.println("Touch screen ready.");
}

void loop() {
  menu1();
  if (millis() - timeReadTemp >= 2000) {
    RealTemp = readThermistor(thermistorCooler);
    HeatTemp = readThermistor(thermistorDefort);
    timeReadTemp = millis();
  }
  if (touch.tirqTouched()) {
    if (touch.touched()) {
      rawLocation = touch.getPoint();
      TouchX = rawLocation.x;
      TouchY = rawLocation.y;
      // Serial.print("X : ");
      // Serial.print(TouchX);
      // Serial.print("--- Y : ");
      // Serial.print(TouchY);
      // Serial.println();
      timePress = millis();
      PAD_DOWN = true;
    }
  }
  if (PAD_DOWN == true && (millis() - timePress >= 300)) {
    press(TouchX, TouchY);
    // Serial.println(DataMode.SetTemp);
    PAD_DOWN = false;
  }
  if (millis() - timeShowScreen > 500) {
    modeScreen(mode);
    timeShowScreen = millis();
  }
}
float readThermistor(int pin) {
  Vo = analogRead(pin);
  R2 = R1 * (4095.0 / (float)Vo - 1.0);  // Resistance of the Thermistor
  tKelvin = (Beta * roomTemp) / (Beta + (roomTemp * log(R2 / Ro)));
  tCelsius = tKelvin - 273.15;
  return tCelsius;
}