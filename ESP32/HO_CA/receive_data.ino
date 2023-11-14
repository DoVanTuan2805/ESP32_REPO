void receive_handle(String modeReceive) {
  modeReceive = getValueString(datReceive, '/', 0);
  if (modeReceive == "L") {
    if (getValueString(datReceive, '/', 1) == "A") {  // AUTO
      modeLed = AUTO;
      beginLed = getValueInt(datReceive, '/', 2);
      endLed = getValueInt(datReceive, '/', 3);
    } else if (getValueString(datReceive, '/', 1) == "M") {  // MANUAL
      modeLed = MANUAL;
      stateLed = getValueInt(datReceive, '/', 2);
    }
  } else if (modeReceive == "B") {
    if (getValueString(datReceive, '/', 1) == "A") {
      modeBomOxi = AUTO;
      modeTimeBomOxi = getValueInt(datReceive, '/', 2);
    } else if (getValueString(datReceive, '/', 1) == "M") {
      modeBomOxi = MANUAL;
      stateBomOxi = getValueInt(datReceive, '/', 2);
    }
  } else if (modeReceive == "N") {
    if (getValueString(datReceive, '/', 1) == "A") {
      modeLocNuoc = AUTO;
      modeTimeLocNuoc = getValueInt(datReceive, '/', 2);
    } else if (getValueString(datReceive, '/', 1) == "M") {
      modeLocNuoc = MANUAL;
      stateLocNuoc = getValueInt(datReceive, '/', 2);
    }
  } else if (modeReceive == "M") {
    thoiGianChoCaAn = getValueInt(datReceive, '/', 1);
    luongThucAn = getValueInt(datReceive, '/', 2);
  } else if (modeReceive == "S") {
    nhietDoThap = getValueInt(datReceive, '/', 1);
    nhietDoCao = getValueInt(datReceive, '/', 2);
  }
}

void printAll() {
  Serial.printf("MODE LED : %d\n", modeLed);
  Serial.printf("MODE BOM OXI : %d\n", modeBomOxi);
  Serial.printf("MODE LOC NUOC : %d\n", modeLocNuoc);
  Serial.println();
  if (modeLed == AUTO || modeBomOxi == AUTO || modeLocNuoc == AUTO) {
    Serial.printf("LED - BEGIN :%d - END: %d\n", beginLed, endLed);
    Serial.printf("BOM OXI - MODE TIME :%d\n", modeTimeBomOxi);
    Serial.printf("LOC NUOC - MODE TIME :%d\n", modeTimeLocNuoc);
  } else if (modeLed == MANUAL || modeBomOxi == MANUAL || modeLocNuoc == MANUAL) {
    Serial.printf("STATE LED : %d\n", stateLed);
    Serial.printf("STATE BOM OXI : %d\n", stateBomOxi);
    Serial.printf("STATE LOC NUOC : %d\n", stateLocNuoc);
  }
}