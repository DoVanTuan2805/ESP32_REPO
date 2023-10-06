void pageSetTemp() {
  tft.fillRoundRect(RECT_X, RECT_Y(0) + 15, 80, 80, 5, ILI9341_WHITE);

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 15);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("SET TEMP");

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 45);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(Temperature.SetTemp);
  tft.drawRGBBitmap(RECT_X + 50, RECT_Y(0) + 40, (uint16_t *)bitmapArray, 20, 20);
}
void pageDTemp() {
  tft.fillRoundRect(RECT_X, RECT_Y(0) + 15, 80, 80, 5, ILI9341_WHITE);

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 15);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("MIN TEMP");

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 45);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(Temperature.SetTemp + setting.int8DTemp);
  tft.drawRGBBitmap(RECT_X + 50, RECT_Y(0) + 40, (uint16_t *)bitmapArray, 20, 20);

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 65);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("SET TEMP");

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 95);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(Temperature.SetTemp);
  tft.drawRGBBitmap(RECT_X + 50, RECT_Y(0) + 90, (uint16_t *)bitmapArray, 20, 20);
}

void pageDEFCycle() {
  tft.fillRoundRect(RECT_X, RECT_Y(0) + 15, 80, 80, 5, ILI9341_WHITE);

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 15);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("DEF CYCLE:");

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 45);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(setting.int8DEFCycle);
}

void pageDEFTime() {
  tft.fillRoundRect(RECT_X, RECT_Y(0) + 15, 80, 80, 5, ILI9341_WHITE);

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 15);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("DEF TIME:");

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 45);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(setting.int8DEFTime);
}

void pageDelayTime() {
  tft.fillRoundRect(RECT_X, RECT_Y(0) + 15, 80, 80, 5, ILI9341_WHITE);

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 15);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("DELAY TIME");

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 45);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(setting.int8DelayTime);
}

void pageDEFExitTemp() {
  tft.fillRoundRect(RECT_X, RECT_Y(0) + 15, 80, 80, 5, ILI9341_WHITE);

  tft.setCursor(RECT_X + 10, RECT_Y(0) + 15);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("TEMP EXIT:");

  tft.setCursor(RECT_X + 20, RECT_Y(0) + 45);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(setting.int8DEFExitTemp);
  tft.drawRGBBitmap(RECT_X + 50, RECT_Y(0) + 40, (uint16_t *)bitmapArray, 20, 20);
}
