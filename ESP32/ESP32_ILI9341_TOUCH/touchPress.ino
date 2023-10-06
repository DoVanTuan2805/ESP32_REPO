void press(int x, int y) {
  if (x < SET_MAX_X && x > SET_MIN_X) {
    if (y < SET_MAX_Y && y > SET_MIN_Y) {
      mode_s++;
      if (mode_s > 5) {
        mode_s = 0;
      }
      tft.fillRoundRect(MENU1_X + 5, RECT_Y(0) + 5, W - 10, H - 10, 5, ILI9341_CYAN);
      tft.fillRoundRect(195, 25, 115, 145, 5, ILI9341_WHITE);
      switch (mode_s) {
        case 0:
          mode = SET_TEMP;
          break;
        case 1:
          mode = RANGE_TEMP;
          break;
        case 2:
          mode = SET_HOUR_COOLER;
          break;
        case 3:
          mode = SET_MINUTE_DEFORT;
          break;
        case 4:
          mode = DELAY_TIME;
          break;
        case 5:
          mode = TEMP_EXIT_DEFORT;
          break;
      }
      modeScreen(mode);
      Serial.println(mode);
    }
  }
  if (x < UP_MAX_X && x > UP_MIN_X) {
    if (y < UP_MAX_Y && y > UP_MIN_Y) {
      Serial.println("Press Up");
      if (mode == SET_TEMP) {
        if (DataMode.SetTemp < 50) {
          DataMode.SetTemp++;
        }
      }
      if (mode == RANGE_TEMP) {
        if (DataMode.rangeTempMin < 15) {
          DataMode.rangeTempMin++;
        }
      }
      if (mode == SET_HOUR_COOLER) {
        if (DataMode.hourCooler < 99) {
          DataMode.hourCooler++;
        }
      }
    }
  }
  if (x < DOWN_MAX_X && x > DOWN_MIN_X) {
    if (y < DOWN_MAX_Y && y > DOWN_MIN_Y) {
      Serial.println("Press Down");
      if (mode == SET_TEMP) {
        if (DataMode.SetTemp > -50) {
          DataMode.SetTemp--;
        }
      }
      if (mode == RANGE_TEMP) {
        if (DataMode.rangeTempMin > 1) {
          DataMode.rangeTempMin--;
        }
      }
      if (mode == SET_HOUR_COOLER) {
        if (DataMode.hourCooler > 1) {
          DataMode.hourCooler--;
        }
      }
    }
  }
}
