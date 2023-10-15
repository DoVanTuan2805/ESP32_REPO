void pressSwitchPage(int x, int y) {
  Serial.println("Here !!");
  if (showSwitchPage == true) {
    if (x > SWITCH_PAGE1_MIN_X && x < SWITCH_PAGE1_MAX_X) {
      if (y > SWITCH_PAGE1_MIN_Y && y < SWITCH_PAGE1_MAX_Y) {
        Serial.println("Switch page 1");
        int8SwitchPage = 0;
        tft.fillRoundRect(5, 5, 310, 230, 5, ILI9341_WHITE);
        switchPage(showSwitchPage);
        delay(10);
        showPage1();
      }
    }

    if (x > SWITCH_PAGE2_MIN_X && x < SWITCH_PAGE2_MAX_X) {
      if (y > SWITCH_PAGE2_MIN_Y && y < SWITCH_PAGE2_MAX_Y) {
        Serial.println("Switch page 2");
        int8SwitchPage = 1;
        tft.fillRoundRect(5, 5, 310, 230, 5, ILI9341_WHITE);
        switchPage(showSwitchPage);
        delay(10);
        showPage2();
      }
    }
    if (x > SWITCH_PAGE3_MIN_X && x < SWITCH_PAGE3_MAX_X) {
      if (y > SWITCH_PAGE3_MIN_Y && y < SWITCH_PAGE3_MAX_Y) {
        Serial.println("Switch page 3");
        int8SwitchPage = 3;
        tft.fillRoundRect(5, 5, 310, 230, 5, ILI9341_WHITE);
        switchPage(showSwitchPage);
        delay(10);
        showPage3();
      }
    }
    if (int8SwitchPage == 0) {
      page = PAGE1;
    } else if (int8SwitchPage == 1) {
      page = PAGE2;
    } else {
      page = PAGE3;
    }
  }
}