#define MENU1_X 15
#define MENU1_Y 25

#define W 80
#define H 40

#define SPLIT_RECT 10
#define RECT_X (MENU1_X + W + 10)
#define RECT_Y(x) (MENU1_Y + (x * H) + (x * SPLIT_RECT))
void menu1() {
  // tft.setCursor(20, 20);  // x y

  // BOARDER
  tft.drawRoundRect(5, 5, 310, 230, 5, ILI9341_ORANGE);
  tft.drawRoundRect(195, 25, 115, 145, 5, ILI9341_ORANGE);

  tft.drawRoundRect(MENU1_X, RECT_Y(0), W, H, 5, ILI9341_RED);  // x y w h color


  tft.drawRect(MENU1_X, RECT_Y(1), W, H, ILI9341_BLUE);
  tft.setCursor(MENU1_X + 25, RECT_Y(1) + 12);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("SET");

  tft.drawRect(MENU1_X, RECT_Y(2), W, H, ILI9341_BLUE);
  tft.setCursor(MENU1_X + 28, RECT_Y(2) + 12);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("UP");

  tft.drawRect(MENU1_X, RECT_Y(3), W, H, ILI9341_BLUE);
  tft.setCursor(MENU1_X + 20, RECT_Y(3) + 12);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("DOWN");

  tft.drawRoundRect(RECT_X, RECT_Y(0), W, H, 5, ILI9341_RED);  // x y w h color
  tft.fillRoundRect(RECT_X + 5, RECT_Y(0) + 5, W - 10, H - 10, 5, ILI9341_CYAN);
  tft.drawRect(RECT_X, RECT_Y(1), W, H, ILI9341_BLUE);
  tft.setCursor(RECT_X + 18, RECT_Y(1) + 12);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("HEAT");

  tft.drawRect(RECT_X, RECT_Y(2), W, H, ILI9341_BLUE);
  tft.setCursor(RECT_X + 10, RECT_Y(2) + 5);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1.5);
  tft.print("DEFORT : ");
  // time Defort
  tft.setCursor(RECT_X + 10, RECT_Y(2) + 15);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(timeDefort.hour);
  tft.print(":");
  tft.print(timeDefort.minute);
  tft.print("p");

  tft.drawRect(RECT_X, RECT_Y(3), W, H, ILI9341_BLUE);
  tft.setCursor(RECT_X + 10, RECT_Y(3) + 5);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1.5);
  tft.print("COOLER : ");
  // time Cooler
  tft.setCursor(RECT_X + 10, RECT_Y(3) + 15);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(2);
  tft.print(timeCooler.hour);
  tft.print(":");
  tft.print(timeCooler.minute);
  tft.print("p");
}
void D_Temp() {
  tft.setCursor(200, 30);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("MIN TEMP");
  tft.setCursor(210, 50);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.fillRect(210, 50, 90, 25, ILI9341_WHITE);
  tft.print(DataMode.rangeTempMin + DataMode.SetTemp);

  tft.setCursor(200, 80);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("SET TEMP");
  tft.setCursor(210, 100);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.fillRect(210, 100, 90, 25, ILI9341_WHITE);
  tft.print(DataMode.SetTemp);
}
void DEF_cycle() {
  tft.setCursor(200, 30);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("TIME");

  tft.setCursor(200, 50);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("COOLER : ");

  tft.setCursor(220, 70);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_RED);
  tft.fillRect(210, 70, 90, 25, ILI9341_WHITE);
  tft.print(DataMode.hourCooler);
  tft.print(" H");
}
void modeScreen(Mode_t mode) {
  switch (mode) {
    case SET_TEMP:
      tft.setCursor(MENU1_X + 12, RECT_Y(0) + 15);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(1.5);
      tft.print("SET TEMP");
      showTemp(RealTemp, HeatTemp);
      setTemp(DataMode.SetTemp);
      break;
    case RANGE_TEMP:
      tft.setCursor(MENU1_X + 12, RECT_Y(0) + 15);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(1.5);
      tft.print("D-TEMP");
      D_Temp();
      break;

    case SET_HOUR_COOLER:
      tft.setCursor(MENU1_X + 12, RECT_Y(0) + 15);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(1.5);
      tft.print("DEF CYCLE");
      DEF_cycle();
      break;

    case SET_MINUTE_DEFORT:
      tft.setCursor(MENU1_X + 12, RECT_Y(0) + 15);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(1.5);
      tft.print("DEF TIME");
      break;

    case DELAY_TIME:
      tft.setCursor(MENU1_X + 12, RECT_Y(0) + 15);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(1.5);
      tft.print("DELAY TIME");
      break;

    case TEMP_EXIT_DEFORT:
      tft.setCursor(MENU1_X + 12, RECT_Y(0) + 15);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(1.5);
      tft.print("DEF-EXIT");
      break;
  }
}