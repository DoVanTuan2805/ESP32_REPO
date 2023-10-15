void processCooler() {
  static uint64_t timeDelayCurr, timeDelayLast;
  static bool checkDelayTime = false;
  static bool state = false;
  static bool compare = false;
  digitalWrite(RL_COOLER, OnOffCooler);
  if (OnOffSystem == false) {
    if (Temperature.RealTemp > (Temperature.SetTemp + setting.int8DTemp)) {
      timeDelayCurr = millis();
      checkDelayTime = true;
      if (state == false) {
        if (checkDelayTime == true) {
          state = true;
          timeDelayLast = millis();
        }
      }
      if ((state == true) && (timeDelayCurr - timeDelayLast > (setting.int8DelayTime * 60000))) {
        OnOffCooler = true;
        state = false;
      }
    } else {
      state = false;
      checkDelayTime = false;
      OnOffCooler = false;
    }
  }
}