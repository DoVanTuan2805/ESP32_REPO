#define PAGE1_X 25
#define PAGE1_Y 25

#define W_PAGE1_TEMP 85
#define H_PAGE1_TEMP 75
char data1[14], data2[16];

void showPage1() {
  showClock();
  showTemp(Temperature.RealTemp, Temperature.HeatTemp, Temperature.SetTemp);
  showConnectWifi(wifiCon);
}
void showClock() {
  sprintf(data1, "%d - %d - %d", dateTime.hour, dateTime.minute, dateTime.second);
  sprintf(data2, "%d - %d - %d", dateTime.day, dateTime.month, dateTime.year);

  tft.drawRoundRect(PAGE1_X - 5, PAGE1_Y - 5, 280, 25, 5, ILI9341_GREEN);
  tft.setCursor(PAGE1_X, PAGE1_Y);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.print("CLOCK : ");
  tft.setTextColor(ILI9341_OLIVE);
  tft.print(data1);

  tft.drawRoundRect(PAGE1_X - 5, PAGE1_Y + 25, 280, 25, 5, ILI9341_GREEN);
  tft.setCursor(PAGE1_X, PAGE1_Y + 30);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.print("TIME  : ");
  tft.setTextColor(ILI9341_OLIVE);
  tft.print(data2);

  memset(data1, 0, sizeof(data1));
  memset(data2, 0, sizeof(data2));
}
void showTemp(float RealT, float HeatT, int8_t setTemp) {
  tft.fillRoundRect(PAGE1_X - 5, PAGE1_Y + 60, W_PAGE1_TEMP, H_PAGE1_TEMP, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE1_X - 5, PAGE1_Y + 60, W_PAGE1_TEMP, H_PAGE1_TEMP, 5, ILI9341_GREEN);

  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.setCursor(PAGE1_X, PAGE1_Y + 70);
  tft.print("COOLER");
  if (RealT > -100) {
    // TEXT REAL TEMP
    tft.setCursor(PAGE1_X + 5, PAGE1_Y + 95);
    tft.setTextColor(ILI9341_RED);
    tft.print(RealT);
    tft.drawRGBBitmap(PAGE1_X + 20, PAGE1_Y + 110, (uint16_t *)bitmapArray, 20, 20);
  } else {
    tft.setCursor(PAGE1_X, PAGE1_Y + 95);
    tft.setTextColor(ILI9341_RED);
    tft.print("ERROR");
  }

  tft.fillRoundRect(PAGE1_X + 8 + W_PAGE1_TEMP, PAGE1_Y + 60, W_PAGE1_TEMP, H_PAGE1_TEMP, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE1_X + 8 + W_PAGE1_TEMP, PAGE1_Y + 60, W_PAGE1_TEMP, H_PAGE1_TEMP, 5, ILI9341_GREEN);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.setCursor(PAGE1_X + 8 + W_PAGE1_TEMP + 5, PAGE1_Y + 70);
  tft.print("DEFORT");
  if (HeatT > -100) {
    // TEXT HEAT TEMP
    tft.setCursor(PAGE1_X + 8 + W_PAGE1_TEMP + 5, PAGE1_Y + 95);
    tft.setTextColor(ILI9341_RED);
    tft.print(HeatT);
    tft.drawRGBBitmap(PAGE1_X + 10 + W_PAGE1_TEMP + 20, PAGE1_Y + 110, (uint16_t *)bitmapArray, 20, 20);
  } else {
    tft.setCursor(PAGE1_X + 8 + W_PAGE1_TEMP + 5, PAGE1_Y + 95);
    tft.setTextColor(ILI9341_RED);
    tft.print("ERROR");
  }

  tft.fillRoundRect(PAGE1_X + 21 + (2 * W_PAGE1_TEMP), PAGE1_Y + 60, W_PAGE1_TEMP, H_PAGE1_TEMP, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE1_X + 21 + (2 * W_PAGE1_TEMP), PAGE1_Y + 60, W_PAGE1_TEMP, H_PAGE1_TEMP, 5, ILI9341_GREEN);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.setCursor(PAGE1_X + 21 + (2 * W_PAGE1_TEMP) + 18, PAGE1_Y + 70);
  tft.print("SET");
  tft.setCursor(PAGE1_X + 21 + (2 * W_PAGE1_TEMP) + 18, PAGE1_Y + 95);
  tft.setTextColor(ILI9341_RED);
  tft.print(setTemp);
  tft.drawRGBBitmap(PAGE1_X + 25 + (2 * W_PAGE1_TEMP) + 20, PAGE1_Y + 110, (uint16_t *)bitmapArray, 20, 20);
}
void showConnectWifi(bool isCon) {
  if (!isCon) {  // disconnect
    tft.fillRoundRect(PAGE1_X, PAGE1_Y + 140, 280, 25, 5, ILI9341_WHITE);
    tft.drawRGBBitmap(PAGE1_X, PAGE1_Y + 140, (uint16_t *)disconnection, 20, 20);
    // STATUS WIFI STRING : OFFLINE
    tft.setCursor(PAGE1_X + 25, PAGE1_Y + 145);
    tft.setTextColor(ILI9341_RED);
    tft.print(": DISCONNECTED");
  } else {
    tft.fillRoundRect(PAGE1_X, PAGE1_Y + 140, 280, 25, 5, ILI9341_WHITE);
    tft.drawRGBBitmap(PAGE1_X, PAGE1_Y + 140, (uint16_t *)connection, 20, 20);
    // STATUS WIFI STRING : ONLINE
    tft.setCursor(PAGE1_X + 25, PAGE1_Y + 145);
    tft.setTextColor(ILI9341_GREEN);
    tft.print(": CONNECTED");
  }
}