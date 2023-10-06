void pressSetting(int x, int y) {
  pressUp(x, y);
  pressDown(x, y);
  pressOk(x, y);
}
void pressUp(int x, int y) {
  if (x > SET_PAGE2_MIN_X && x < SET_PAGE2_MAX_X) {
    if (y > SET_PAGE2_MIN_Y && y < SET_PAGE2_MAX_Y) {
      showSwitchPage = false;
      if (mode == STemp) {
        if (Temperature.SetTemp < 50) {
          Temperature.SetTemp++;
        }
      }
      if (mode == DTemp) {
        if (setting.int8DTemp < 15) {
          setting.int8DTemp++;
        }
      }
      if (mode == DEFCycle) {
        if (setting.int8DEFCycle < 99) {
          setting.int8DEFCycle++;
        }
      }
      if (mode == DEFTime) {
        if (setting.int8DEFTime < 45) {
          setting.int8DEFTime++;
        }
      }
      if (mode == DelayTime) {
        if (setting.int8DelayTime < 5) {
          setting.int8DelayTime++;
        }
      }
      if (mode == DEFExitTemp) {
        if (setting.int8DEFExitTemp < 35) {
          setting.int8DEFExitTemp++;
        }
      }
    }
  }
}
void pressDown(int x, int y) {
  if (x > D_TEMP_PAGE2_MIN_X && x < D_TEMP_PAGE2_MAX_X) {
    if (y > D_TEMP_PAGE2_MIN_Y && y < D_TEMP_PAGE2_MAX_Y) {
      showSwitchPage = false;
      if (mode == STemp) {
        if (Temperature.SetTemp > -50) {
          Temperature.SetTemp--;
        }
      }
      if (mode == DTemp) {
        if (setting.int8DTemp > 1) {
          setting.int8DTemp--;
        }
      }
      if (mode == DEFCycle) {
        if (setting.int8DEFCycle > 1) {
          setting.int8DEFCycle--;
        }
      }
      if (mode == DEFTime) {
        if (setting.int8DEFTime > 1) {
          setting.int8DEFTime--;
        }
      }
      if (mode == DelayTime) {
        if (setting.int8DelayTime > 1) {
          setting.int8DelayTime--;
        }
      }
      if (mode == DEFExitTemp) {
        if (setting.int8DEFExitTemp > 5) {
          setting.int8DEFExitTemp--;
        }
      }
    }
  }
}
void pressOk(int x, int y) {
  if (x > DEF_CYCLE_PAGE2_MIN_X && x < DEF_CYCLE_PAGE2_MAX_X) {
    if (y > DEF_CYCLE_PAGE2_MIN_Y && y < DEF_CYCLE_PAGE2_MAX_Y) {
      tft.fillRoundRect(RECT_X, RECT_Y(0), 100, 160, 5, ILI9341_WHITE);
      showSwitchPage = true;
      mode = MAIN_PAGE2;
    }
  }
}