#define RL1 32
#define RL2 33

#define TFT_DC 2
#define _sclk 18
#define _mosi 23 /* 10K pull-up */
#define _miso 19
#define TFT_CS 15 /* 10K pull-up */
#define TFT_RST 4

#define TFT_BACKLIGHT_PIN 2 /* -via transistor- */
#define TOUCH_CS_PIN 5      /* 10K pull-up */
#define TOUCH_IRQ 27

const uint8_t TFT_ORIENTATION = 1;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen touch(TOUCH_CS_PIN, TOUCH_IRQ);

TS_Point rawLocation;
void init_Relay() {
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  digitalWrite(RL1, LOW);
  digitalWrite(RL2, LOW);
}
void init_Screen() {
  tft.begin(60000000);
  tft.setRotation(TFT_ORIENTATION);
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  pinMode(TFT_BACKLIGHT_PIN, OUTPUT);
  digitalWrite(TFT_BACKLIGHT_PIN, HIGH);
}
void init_Touch() {
  SPI.begin(_sclk, _miso, _mosi);
  SPI.setClockDivider(1);
  SPI.beginTransaction(SPISettings(60000000, MSBFIRST, SPI_MODE0));
  SPI.endTransaction();
  touch.begin();
}