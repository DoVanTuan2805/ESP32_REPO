
void processDefort() {
  static bool AutoDEFCycle = false;
  static uint64_t t;
  static uint64_t t1;
  digitalWrite(RL_DEFORT, OnOffDefort);
  minuteNow = (hour() * HOUR_TIME) + (minute() * MINUTE_TIME) + second() * SECOND_TIME;
  if (OnOffSystem == false) {
    if (OnOffDefort == false) {
      AutoDEFCycle = true;
    }
    if (AutoDEFCycle == true) {
      if (minuteNow - minuteLast >= (setting.int8DEFCycle * HOUR_TIME)) {
        Serial.println("Enter DEF Cycle");
        AutoDEFCycle = false;
        OnOffDefort = true;
        minuteLast = minuteNow;
        timeDefort = minuteNow;
      }
    }
    if (OnOffDefort == true && (minuteNow - timeDefort >= (setting.int8DEFTime * MINUTE_TIME))) {
      Serial.println("End DEFTime");
      OnOffDefort = false;
      AutoDEFCycle = true;
      minuteLast = minuteNow;
      Serial.println("START DEF Cycle");
    }
    if (OnOffDefort == true) {
      if (Temperature.HeatTemp > setting.int8DEFExitTemp) {
        Serial.println("EXIT DEF Temp ");
        OnOffDefort = false;
        AutoDEFCycle = true;
        minuteLast = (hour() * HOUR_TIME) + (minute() * MINUTE_TIME) + second() * SECOND_TIME;
      }
    }
  }
}