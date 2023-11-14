#include "DEFINE_PIN.h"
#include <Wire.h>
#include <ESP32Servo.h>
Servo myservo;

/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 7;

static int hours;
String datReceive;
String modeReceive;
typedef enum {
  AUTO,
  MANUAL
} Mode_t;

Mode_t modeLed, modeBomOxi, modeLocNuoc;
int nhietDoThap = 20, nhietDoCao = 25;
int second, minute, hour, day, wday, month, year, days;
int beginLed, endLed;
int modeTimeBomOxi, modeTimeLocNuoc;
int thoiGianChoCaAn, luongThucAn;
int stateLed, stateBomOxi, stateLocNuoc;
float temperatureC;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  initTime();
  initRL();
  initDs18b20();
  timeHandle();
}
void loop() {
  timeHandle();
  readDs18b20();
  while (Serial2.available() > 0) {
    char c = Serial2.read();
    Serial.println(c);
    if (c == '\n') {
      Serial.println(datReceive);
      receive_handle(modeReceive);
      printAll();
      datReceive = "";
    } else {
      datReceive += c;
    }
  }
  controll_Led();
  controll_BomOxi();
  controll_LocNuoc();
  controll_ThucAn(luongThucAn, thoiGianChoCaAn);
  control_solanh_maysuoi(temperatureC);
}

String getValueString(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {  //data.charAt(i) xuất ra kí tự ở vị trí (i)
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
      // (i == maxIndex) true -> i + 1
      // (i == maxIndex) false -> i
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
int getValueInt(String data, char separator, int index) {
  String datas;
  int dataInt;
  datas = getValueString(data, separator, index);
  dataInt = datas.toInt();
  return dataInt;
}
