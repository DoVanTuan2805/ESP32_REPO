void pressPage2(int x, int y) {

  if (mode != MAIN_PAGE2) {
    pressSetting(x, y);
  } else {
    fncSetTemp(x, y);
    fncDTemp(x, y);
    fncDEFCycle(x, y);
    fncDEFTime(x, y);
    fncDelayTime(x, y);
    fncExitTemp(x, y);
  }
}
void clearRightScreen() {
  tft.fillRoundRect(RECT_X, RECT_Y(0), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.fillRoundRect(RECT_X, RECT_Y(1), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
  tft.fillRoundRect(RECT_X, RECT_Y(2), W_PAGE2, H_PAGE2, 5, ILI9341_WHITE);
}
void fncSetTemp(int x, int y) {
  if (x > SET_PAGE2_MIN_X && x < SET_PAGE2_MAX_X) {
    if (y > SET_PAGE2_MIN_Y && y < SET_PAGE2_MAX_Y) {
      clearRightScreen();
      screenAdjust();
      showSwitchPage = false;
      mode = STemp;
    }
  }
}
void fncDTemp(int x, int y) {
  if (x > D_TEMP_PAGE2_MIN_X && x < D_TEMP_PAGE2_MAX_X) {
    if (y > D_TEMP_PAGE2_MIN_Y && y < D_TEMP_PAGE2_MAX_Y) {
      clearRightScreen();
      screenAdjust();
      showSwitchPage = false;
      mode = DTemp;
    }
  }
}
void fncDEFCycle(int x, int y) {
  if (x > DEF_CYCLE_PAGE2_MIN_X && x < DEF_CYCLE_PAGE2_MAX_X) {
    if (y > DEF_CYCLE_PAGE2_MIN_Y && y < DEF_CYCLE_PAGE2_MAX_Y) {
      clearRightScreen();
      screenAdjust();
      showSwitchPage = false;
      mode = DEFCycle;
    }
  }
}
void fncDEFTime(int x, int y) {
  if (x > DEF_TIME_PAGE2_MIN_X && x < DEF_TIME_PAGE2_MAX_X) {
    if (y > DEF_TIME_PAGE2_MIN_Y && y < DEF_TIME_PAGE2_MAX_Y) {
      clearRightScreen();
      screenAdjust();
      showSwitchPage = false;
      mode = DEFTime;
    }
  }
}
void fncDelayTime(int x, int y) {
  if (x > DELAY_TIME_PAGE2_MIN_X && x < DELAY_TIME_PAGE2_MAX_X) {
    if (y > DELAY_TIME_PAGE2_MIN_Y && y < DELAY_TIME_PAGE2_MAX_Y) {
      clearRightScreen();
      screenAdjust();
      showSwitchPage = false;
      mode = DelayTime;
    }
  }
}
void fncExitTemp(int x, int y) {
  if (x > DEF_TIME_EXIT_PAGE2_MIN_X && x < DEF_TIME_EXIT_PAGE2_MAX_X) {
    if (y > DEF_TIME_EXIT_PAGE2_MIN_Y && y < DEF_TIME_EXIT_PAGE2_MAX_Y) {
      clearRightScreen();
      screenAdjust();
      showSwitchPage = false;
      mode = DEFExitTemp;
    }
  }
}
