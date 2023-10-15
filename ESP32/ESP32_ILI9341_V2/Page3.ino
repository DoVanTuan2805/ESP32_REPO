#define PAGE3_X 25
#define PAGE3_Y 20

#define PAGE3_W 125
#define PAGE3_H 70

#define SPLIT_PAGE3_X 20
#define SPLIT_PAGE3_Y 10

#define RECT_PAGE3_X (PAGE3_X + PAGE3_W + SPLIT_PAGE3_X)
#define RECT_PAGE3_Y(x) (PAGE3_Y + (x * SPLIT_PAGE3_Y) + (x * PAGE3_H))

void showPage3() {
  screenCompreesor();
  screenCooler();
  screenOutdoor();
  screenPressur();
}

void screenCompreesor() {
  tft.fillRoundRect(PAGE3_X, RECT_PAGE3_Y(0), PAGE3_W, PAGE3_H, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE3_X, RECT_PAGE3_Y(0), PAGE3_W, PAGE3_H, 5, ILI9341_RED);
}
void screenCooler() {
  tft.fillRoundRect(PAGE3_X, RECT_PAGE3_Y(1), PAGE3_W, PAGE3_H, 5, ILI9341_WHITE);
  tft.drawRoundRect(PAGE3_X, RECT_PAGE3_Y(1), PAGE3_W, PAGE3_H, 5, ILI9341_RED);
}
void screenOutdoor() {
  tft.fillRoundRect(RECT_PAGE3_X, RECT_PAGE3_Y(0), PAGE3_W, PAGE3_H, 5, ILI9341_WHITE);
  tft.drawRoundRect(RECT_PAGE3_X, RECT_PAGE3_Y(0), PAGE3_W, PAGE3_H, 5, ILI9341_RED);
}
void screenPressur() {
  tft.fillRoundRect(RECT_PAGE3_X, RECT_PAGE3_Y(1), PAGE3_W, PAGE3_H, 5, ILI9341_WHITE);
  tft.drawRoundRect(RECT_PAGE3_X, RECT_PAGE3_Y(1), PAGE3_W, PAGE3_H, 5, ILI9341_RED);
}