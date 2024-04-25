#include <WiFi.h>
#include <FirebaseESP32.h>
#include <HCSR04.h>
#include <SoftwareSerial.h>

const char* WIFI_SSID = "Lau 3";
const char* WIFI_PASSWORD = "khongbiet";

HCSR04 hc(5, 18);
SoftwareSerial SerialSTM(25, 26);

#define FIREBASE_HOST "wedsitedatcho-b9ce4-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "1a4N9tIQoB1osG34gZq9E9gBNOmvFU0iknWuNwT2"
FirebaseData fbdb;

float distance = 0;
uint64_t prev_time_distance;
#define BLOCK_IN_FLOOR (6)
#define MAX_FLOOR (3)

String RFID_Out;
bool end_find = false;
void setup() {
  Serial.begin(9600);
  SerialSTM.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  // Đặt thời gian chờ đọc cơ sở dữ liệu thành 1 phút (tối đa 15 phút)
  Firebase.setReadTimeout(fbdb, 1000 * 60);
  // Đặt giới hạn kích thước ghi (ví dụ: tiny, small, medium, large)
  Firebase.setwriteSizeLimit(fbdb, "tiny");  // Tên hàm đã được sửa
  prev_time_distance = millis();
}

void loop() {
  if (millis() - prev_time_distance > 100) {
    distance = hc.dist();
    prev_time_distance = millis();
  }
  while (SerialSTM.available() > 0) {
    String data = SerialSTM.readStringUntil('\n');
    Serial.println(data);
    if (data == "HOME") {
      String dataToSR04 = "SR " + String(distance) + "\n";
      SerialSTM.print(dataToSR04);
      Serial.print(dataToSR04);
    }
    if (getValue(data, ' ', 0) == "IN") {
      String path_RFID = create_path_RFID(getValue(data, ' ', 2), getValue(data, ' ', 3));
      String path_Status = create_path_Status(getValue(data, ' ', 2), getValue(data, ' ', 3));
      Firebase.setString(fbdb, path_RFID, getValue(data, ' ', 1));
      Firebase.setInt(fbdb, path_Status, 1);
    }
    if (getValue(data, ' ', 0) == "OUT") {
      end_find = false;
      RFID_Out = getValue(data, ' ', 1);
      for (int i = 0; i < MAX_FLOOR; i++) {
        for (int j = 0; j < BLOCK_IN_FLOOR; j++) {
          Serial.printf(" %d -  %d\n", i, j);
          if (i == 0) {
            if (j > 2)
              break;
            String path = create_path_RFID(String(i), String(j));
            if (Firebase.getString(fbdb, path)) {
              if (RFID_Out == fbdb.to<const char*>()) {
                Serial.printf("So Tang : %d - Vi Tri : %d\n", i, j);
                end_find = true;
              }
            }
          } else {
            String path = create_path_RFID(String(i), String(j));
            if (Firebase.getString(fbdb, path)) {
              if (RFID_Out == fbdb.to<const char*>()) {
                Serial.printf("So Tang : %d - Vi Tri : %d\n", i, j);
                end_find = true;
              }
            }
          }
        }
        if (end_find == true)
          break;
      }
    }
  }
}
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {  //data.charAt(i) xuất ra kí tự ở v`  ị trí (i)
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
      // (i == maxIndex) true -> i + 1
      // (i == maxIndex) false -> i
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
String create_path_RFID(String so_tang, String vi_tri) {
  String path = "/T" + so_tang + "/BL" + vi_tri + "/RFID";
  return path;
}
String create_path_Status(String so_tang, String vi_tri) {
  String path = "/T" + so_tang + "/BL" + vi_tri + "/Status";
  return path;
}
