void pressSwitchPage(int x, int y) {
  Serial.println("Here !!");
  if (x > SWITCH_PAGE1_MIN_X && x < SWITCH_PAGE1_MAX_X) {
    if (y > SWITCH_PAGE1_MIN_Y && y < SWITCH_PAGE1_MAX_Y) {
      Serial.println("Switch page 1");
      boolSwitchPage = 0;
      tft.fillRoundRect(5, 5, 310, 230, 5, ILI9341_WHITE);
      switchPage();
      delay(10);
      showPage1();
    }
  }

  if (x > SWITCH_PAGE2_MIN_X && x < SWITCH_PAGE2_MAX_X) {
    if (y > SWITCH_PAGE2_MIN_Y && y < SWITCH_PAGE2_MAX_Y) {
      Serial.println("Switch page 2");
      boolSwitchPage = 1;
      tft.fillRoundRect(5, 5, 310, 230, 5, ILI9341_WHITE);
      switchPage();
      delay(10);
      showPage2();
    }
  }
  if (boolSwitchPage == 0) {
    page = PAGE1;
  } else {
    page = PAGE2;
  }
}