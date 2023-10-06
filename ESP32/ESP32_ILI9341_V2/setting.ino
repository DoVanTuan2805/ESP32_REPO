void screenAdjust() {
  Up();
  Down();
  settingOK();
}
void Up() {
  tft.fillRoundRect(PAGE2_X, RECT_Y(0), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE2_X, RECT_Y(0), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(PAGE2_X + 20, RECT_Y(0) + 15);
  tft.print("UP");
}
void Down() {
  tft.fillRoundRect(PAGE2_X, RECT_Y(1), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE2_X, RECT_Y(1), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(PAGE2_X + 20, RECT_Y(1) + 15);
  tft.print("DOWN");
}
void settingOK() {
  tft.fillRoundRect(PAGE2_X, RECT_Y(2), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE2_X, RECT_Y(2), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(PAGE2_X + 20, RECT_Y(2) + 15);
  tft.print("OK");
}