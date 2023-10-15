#define RT V0     // REAL TEMP
#define HT V1     // HEAT TEMP
#define BTSYS V2  // BUTTON SYSTEM
#define BTDEF V3  // BUTTON DEFORT

#define BLYNK_SETTEMP V4
#define BLYNK_DTEMP V5
#define BLYNK_DELAYTIME V6
#define BLYNK_DEFCYCLE V7
#define BLYNK_DEFTIME V8
#define BLYNK_DEFEXITTEMP V9

#define BLYNK_ERROR_COOLER V10
#define BLYNK_ERROR_DEFORT V11
BLYNK_CONNECTED() {
  rtc.begin();
  Blynk.syncAll();
}
void pushTempToBlynk() {
  Blynk.virtualWrite(RT, Temperature.RealTemp);
  Blynk.virtualWrite(HT, Temperature.HeatTemp);

  Blynk.virtualWrite(BTSYS, OnOffSystem);
  Blynk.virtualWrite(BTDEF, OnOffDefort);
}
void pushSettingToBlynk() {
  Blynk.virtualWrite(BLYNK_SETTEMP, Temperature.SetTemp);
  Blynk.virtualWrite(BLYNK_DTEMP, setting.int8DTemp);
  Blynk.virtualWrite(BLYNK_DELAYTIME, setting.int8DelayTime);
  Blynk.virtualWrite(BLYNK_DEFCYCLE, setting.int8DEFCycle);
  Blynk.virtualWrite(BLYNK_DEFTIME, setting.int8DEFTime);
  Blynk.virtualWrite(BLYNK_DEFEXITTEMP, setting.int8DEFExitTemp);
}
void getTimeBlynk() {
  dateTime.hour = hour();
  dateTime.minute = minute();
  dateTime.second = second();

  dateTime.day = day();
  dateTime.month = month();
  dateTime.year = year();
}
BLYNK_WRITE(BTSYS) {
  bool btsys = param.asInt();
  if (btsys == 1) {
    OnOffSystem = true;
  }
  if (btsys == 0) {
    OnOffSystem = false;
  }
  if (OnOffSystem == true) {
    OnOffDefort = false;
    OnOffCooler = false;
  }
  timeDefort = (hour() * HOUR_TIME) + (minute() * MINUTE_TIME) + second() * SECOND_TIME;
}

BLYNK_WRITE(BTDEF) {
  bool btdef = param.asInt();
  if (btdef == 1) {
    OnOffDefort = true;
  } else {
    OnOffDefort = false;
  }
  timeDefort = (hour() * HOUR_TIME) + (minute() * MINUTE_TIME) + second() * SECOND_TIME;
}

BLYNK_WRITE(BLYNK_SETTEMP) {
  Temperature.SetTemp = param.asInt();
}

BLYNK_WRITE(BLYNK_DTEMP) {
  setting.int8DTemp = param.asInt();
}

BLYNK_WRITE(BLYNK_DELAYTIME) {
  setting.int8DelayTime = param.asInt();
}

BLYNK_WRITE(BLYNK_DEFCYCLE) {
  setting.int8DEFCycle = param.asInt();
}

BLYNK_WRITE(BLYNK_DEFTIME) {
  setting.int8DEFTime = param.asInt();
}

BLYNK_WRITE(BLYNK_DEFEXITTEMP) {
  setting.int8DEFExitTemp = param.asInt();
}
BLYNK_WRITE(BLYNK_ERROR_COOLER) {
  saiso_cb_cooler = param.asInt();
}
BLYNK_WRITE(BLYNK_ERROR_DEFORT) {
  saiso_cb_defort = param.asInt();
}
