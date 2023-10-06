#include "init.h"
extern Adafruit_ILI9341 tft;
extern XPT2046_Touchscreen touch;
extern TS_Point rawLocation;

void init_Screen()
{
    tft.begin(60000000);
    delay(10);
    tft.setRotation(3);
    tft.fillScreen(ILI9341_WHITE);
    // tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
    pinMode(TFT_BACKLIGHT_PIN, OUTPUT);
    digitalWrite(TFT_BACKLIGHT_PIN, HIGH);
}
void init_Touch()
{
    SPI.begin(_sclk, _miso, _mosi);
    SPI.setClockDivider(1);
    SPI.beginTransaction(SPISettings(60000000, MSBFIRST, SPI_MODE0));
    SPI.endTransaction();
    touch.begin();
}
void init_Relay()
{
    pinMode(RL1, OUTPUT);
    pinMode(RL2, OUTPUT);
    digitalWrite(RL1, LOW);
    digitalWrite(RL2, LOW);
}

void menu1()
{
    tft.drawRect(210, 180, 100, 50, ILI9341_BLUE);
    tft.setTextSize(2);
    tft.setCursor(210 + 10, 180 + 10);
    tft.setTextColor(ILI9341_BLUE);
    tft.println("ON");
    Serial.print(" den day roi");
}
