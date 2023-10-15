void pressPage1(int x, int y) {
  pressSystem(x, y);
  pressDefort(x, y);
  pressOverViewDefort(x, y);
}
void pressSystem(int x, int y) {
  if (x > SYSTEM_MIN_X && x < SYSTEM_MAX_X) {
    if (y > SYSTEM_MIN_Y && y < SYSTEM_MAX_Y) {
      if (OnOffSystem == true) {
        OnOffSystem = false;
      } else {
        OnOffSystem = true;
      }
      if (OnOffSystem == false) {
        OnOffDefort = false;
        OnOffCooler = false;
      }
      showButtonControl(OnOffCooler, OnOffDefort);
    }
  }
}
void pressDefort(int x, int y) {
  if (x > DEFORT_MIN_X && x < DEFORT_MAX_X) {
    if (y > DEFORT_MIN_Y && y < DEFORT_MAX_Y) {
      if (OnOffDefort == true) {
        OnOffDefort = false;
      } else {
        OnOffDefort = true;
      }
      timeDefort = (hour() * HOUR_TIME) + (minute() * MINUTE_TIME) + second() * SECOND_TIME;
    }
  }
}
void pressOverViewDefort(int x, int y) {
  if (x > OVERVIEW_DEFORT_MIN_X && x < OVERVIEW_DEFORT_MAX_X) {
    if (y > OVERVIEW_DEFORT_MIN_Y && y < OVERVIEW_DEFORT_MAX_Y) {
      if (OnOffOverViewDEF == true) {
        OnOffOverViewDEF = false;
      } else {
        OnOffOverViewDEF = true;
      }
    }
  }
}