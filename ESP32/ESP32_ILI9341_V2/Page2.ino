#define PAGE2_X 15
#define PAGE2_Y 25
#define W_PAGE2 130
#define H_PAGE2 40

#define SPLIT_RECT_Y 10
#define SPLIT_RECT_X 30
#define RECT_Y(x) (PAGE2_Y + (x * H_PAGE2) + (x * SPLIT_RECT_Y))
#define RECT_X (PAGE2_X + W_PAGE2 + SPLIT_RECT_X)
void showPage2() {
  setTemperature();
  D_Temp();
  DEF_Cylcle();
  DEF_Time();
  Delay_Time();
  DEF_Exit_Temp();
}
void setTemperature() {
  tft.fillRoundRect(PAGE2_X, RECT_Y(0), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE2_X, RECT_Y(0), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(PAGE2_X + 10, RECT_Y(0) + 15);
  tft.print("SET TEMP");
}
void D_Temp() {
  tft.fillRoundRect(PAGE2_X, RECT_Y(1), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE2_X, RECT_Y(1), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(PAGE2_X + 10, RECT_Y(1) + 15);
  tft.print("D - TEMP");
}
void DEF_Cylcle() {
  tft.fillRoundRect(PAGE2_X, RECT_Y(2), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE2_X, RECT_Y(2), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(PAGE2_X + 5, RECT_Y(2) + 15);
  tft.print("DEF CYCLE");
}
void DEF_Time() {
  tft.fillRoundRect(RECT_X, RECT_Y(0), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(RECT_X, RECT_Y(0), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(RECT_X + 10, RECT_Y(0) + 15);
  tft.print("DEF TIME");
}
void Delay_Time() {
  tft.fillRoundRect(RECT_X, RECT_Y(1), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(RECT_X, RECT_Y(1), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(RECT_X + 5, RECT_Y(1) + 15);
  tft.print("DELAY TIME");
}
void DEF_Exit_Temp() {
  tft.fillRoundRect(RECT_X, RECT_Y(2), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.drawRoundRect(RECT_X, RECT_Y(2), W_PAGE2, H_PAGE2, 5, ILI9341_RED);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(RECT_X + 5, RECT_Y(2) + 15);
  tft.print("EXIT TEMP");
}