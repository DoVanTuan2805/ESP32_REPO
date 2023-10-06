void showTemp(float RealT, float HeatT) {
  tft.setCursor(200, 30);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("REAL TEMP");
  tft.setCursor(210, 50);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.fillRect(210, 50, 90, 25, ILI9341_WHITE);
  if (RealT > -100) {
    tft.print(RealT);
    tft.print(" C");
  } else {
    tft.print("ERROR !");
  }
  tft.setCursor(200, 80);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("HEAT TEMP");
  tft.setCursor(210, 100);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.fillRect(210, 100, 90, 25, ILI9341_WHITE);
  if (HeatT > -100) {
    tft.print(HeatT);
    tft.print(" C");
  } else {
    tft.print("ERROR !");
  }
}
void setTemp(int setT) {
  tft.setCursor(200, 130);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("SET TEMP");
  tft.setCursor(220, 150);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.fillRect(220, 150, 70, 25, ILI9341_WHITE);
  tft.print(setT);
  tft.print(" C");
}
void checkWifi(bool isCon) {
  tft.setCursor(200, 180);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("WIFI");
  tft.setCursor(190, 200);
  tft.setTextSize(2);
  if (!isCon) {
    tft.setTextColor(ILI9341_RED);
    tft.print("DISCONNECT");
  } else {
    tft.setTextColor(ILI9341_GREEN);
    tft.print(" CONNECTED");
  }
}