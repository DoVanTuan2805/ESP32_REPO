int modetimeOxi0[2] = { 6, 8 };
int modetimeOxi1[4] = { 6, 8, 18, 20 };  // 18
int modetimeOxi2[6] = { 6, 8, 12, 14, 18, 20 };
int modetimeOxi3[8] = { 6, 8, 12, 14, 18, 20, 21, 23 };


int modetimeLoc0[2] = { 6, 18 };
int modetimeLoc1[4] = { 6, 10, 14, 18 };
int modetimeLoc2[6] = { 6, 8, 10, 14, 16, 18 };
int modetimeLoc3[8] = { 4, 6, 8, 10, 14, 16, 18, 20 };

#define ThucAnIt      1000
#define ThucAnVua     2000
#define ThucAnNhieu   3000

void controll_Led() {
  if (modeLed == AUTO) {
    henGioLed(beginLed, endLed);
  } else if (modeLed == MANUAL) {
    if (stateLed == 1) {
      OnLed();
    } else if (stateLed == 0) {
      OffLed();
    }
  }
}

void controll_BomOxi() {
  if (modeBomOxi == AUTO) {
    henGioBomOxi(modeTimeBomOxi);
  } else {
    if (stateBomOxi == 1) {
      OnBomOxi();
    } else if (stateBomOxi == 0) {
      OffBomOxi();
    }
  }
}

void controll_LocNuoc() {
  if (modeLocNuoc == AUTO) {
    henGioLocNuoc(modeTimeLocNuoc);
  } else {
    if (stateLocNuoc == 1) {
      OnLocNuoc();
    } else if (stateLocNuoc == 0) {
      OffLocNuoc();
    }
  }
}

void controll_ThucAn(int luongthucan, int giothucan) {
  static bool checkgetTime;
  static int timePrev;

  if (giothucan == hour) {
    if (days != day) {
      days = day;
      checkgetTime = 0;
    }
    if (checkgetTime == 0) {
      setServoOn();
      timePrev = millis();
      checkgetTime = 1;
    }
    if (checkgetTime == 1) {
      if (luongthucan == 0) {
        if (millis() - timePrev > ThucAnIt) {
          setServoOff();
        }
      } else if (luongthucan == 1) {
        if (millis() - timePrev > ThucAnVua) {
          setServoOff();
        }
      } else if (luongthucan == 2) {
        if (millis() - timePrev > ThucAnNhieu) {
          setServoOff();
        }
      }
    }
  }
}

void henGioLed(int begin, int end) {
  if (begin <= hour && hour < end) {
    OnLed();
  } else {
    OffLed();
  }
}
void henGioBomOxi(int modeTime) {
  if (modeTime == 0) {
    if (modetimeOxi0[0] <= hour && hour < modetimeOxi0[1]) {
      OnBomOxi();
    } else {
      OffBomOxi();
    }
  } else if (modeTime == 1) {
    if ((modetimeOxi1[0] <= hour && hour < modetimeOxi1[1])
        || (modetimeOxi1[2] <= hour && hour < modetimeOxi1[3])) {
      OnBomOxi();
    } else {
      OffBomOxi();
    }
  } else if (modeTime == 2) {
    if ((modetimeOxi2[0] <= hour && hour < modetimeOxi2[1])
        || (modetimeOxi2[2] <= hour && hour < modetimeOxi2[3])
        || (modetimeOxi2[4] <= hour && hour < modetimeOxi2[5])) {
      OnBomOxi();
    } else {
      OffBomOxi();
    }
  } else if (modeTime == 3) {
    if ((modetimeOxi3[0] <= hour && hour < modetimeOxi3[1])
        || (modetimeOxi3[2] <= hour && hour < modetimeOxi3[3])
        || (modetimeOxi3[4] <= hour && hour < modetimeOxi3[5])
        || (modetimeOxi3[6] <= hour && hour < modetimeOxi3[7])) {
      OnBomOxi();
    } else {
      OffBomOxi();
    }
  }
}
void henGioLocNuoc(int modeTime) {
  if (modeTime == 0) {
    if ((modetimeLoc0[0] <= hour && hour <= (modetimeLoc0[0] + 1))
        || (modetimeLoc0[1] <= hour && hour <= (modetimeLoc0[1] + 1))) {
    }
  } else if (modeTime == 1) {
    for (int i = 0; i < sizeof(modetimeLoc1); i++) {
      if (modetimeLoc1[i] <= hour && hour <= (modetimeLoc1[i] + 1)) {
        OnLocNuoc();
        break;
      } else {
        OffLocNuoc();
      }
    }
  } else if (modeTime == 2) {
    for (int i = 0; i < sizeof(modetimeLoc2); i++) {
      if (modetimeLoc2[i] <= hour && hour <= (modetimeLoc2[i] + 1)) {
        OnLocNuoc();
        break;
      } else {
        OffLocNuoc();
      }
    }
  } else if (modeTime == 3) {
    for (int i = 0; i < sizeof(modetimeLoc3); i++) {
      if (modetimeLoc3[i] <= hour <= (modetimeLoc3[i] + 1)) {
        OnLocNuoc();
        break;
      } else {
        OffLocNuoc();
      }
    }
  }
}
void setServoOn() {
  myservo.write(180); 
}
void setServoOff() {
  myservo.write(0); 
}