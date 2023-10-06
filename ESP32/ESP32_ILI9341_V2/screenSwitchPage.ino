#define SWITCH_PAGE1_X 15
#define SWITCH_PAGE1_Y 190

#define SWITCH_PAGE2_X 115
#define SWITCH_PAGE2_Y 190

#define SWITCH_PAGE3_X 215
#define SWITCH_PAGE3_Y 190

#define W_SWITCH_PAGE 90
#define H_SWITCH_PAGE 40
void switchPage(bool showHide) {
  tft.drawRoundRect(5, 5, 310, 230, 5, ILI9341_ORANGE);
  if (showHide == true) {
    tft.drawRoundRect(SWITCH_PAGE1_X, SWITCH_PAGE1_Y, W_SWITCH_PAGE, H_SWITCH_PAGE, 5, ILI9341_ORANGE);  // x y w h
    tft.drawRoundRect(SWITCH_PAGE2_X, SWITCH_PAGE2_Y, W_SWITCH_PAGE, H_SWITCH_PAGE, 5, ILI9341_ORANGE);  // x y w h
    tft.drawRoundRect(SWITCH_PAGE3_X, SWITCH_PAGE3_Y, W_SWITCH_PAGE, H_SWITCH_PAGE, 5, ILI9341_ORANGE);  // x y w h

    if (page == PAGE1) {
      tft.fillRoundRect(SWITCH_PAGE1_X + 2, SWITCH_PAGE1_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_CYAN);
      tft.fillRoundRect(SWITCH_PAGE2_X + 2, SWITCH_PAGE2_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
      tft.fillRoundRect(SWITCH_PAGE3_X + 2, SWITCH_PAGE3_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
    } else if (page == PAGE2) {
      tft.fillRoundRect(SWITCH_PAGE2_X + 2, SWITCH_PAGE2_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_CYAN);
      tft.fillRoundRect(SWITCH_PAGE1_X + 2, SWITCH_PAGE1_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
      tft.fillRoundRect(SWITCH_PAGE3_X + 2, SWITCH_PAGE3_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
    } else {
      tft.fillRoundRect(SWITCH_PAGE3_X + 2, SWITCH_PAGE3_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_CYAN);
      tft.fillRoundRect(SWITCH_PAGE1_X + 2, SWITCH_PAGE1_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
      tft.fillRoundRect(SWITCH_PAGE2_X + 2, SWITCH_PAGE2_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
    }

    tft.setCursor(SWITCH_PAGE1_X + 15, SWITCH_PAGE1_Y + 12);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.print("HOME");
    tft.setCursor(SWITCH_PAGE2_X + 3, SWITCH_PAGE2_Y + 12);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.print("SETTING");
    tft.setCursor(SWITCH_PAGE3_X + 8, SWITCH_PAGE3_Y + 12);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(2);
    tft.print("STATUS");
  } else {
    tft.fillRoundRect(SWITCH_PAGE1_X + 2, SWITCH_PAGE1_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
    tft.fillRoundRect(SWITCH_PAGE2_X + 2, SWITCH_PAGE2_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
    tft.fillRoundRect(SWITCH_PAGE3_X + 2, SWITCH_PAGE3_Y + 2, W_SWITCH_PAGE - 4, H_SWITCH_PAGE - 4, 5, ILI9341_WHITE);
  }
}