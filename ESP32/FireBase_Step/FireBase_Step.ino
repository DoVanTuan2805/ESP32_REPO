#include <WiFi.h>
#include <FirebaseESP32.h>
const char* WIFI_SSID = "Lau 3";
const char* WIFI_PASSWORD = "khongbiet";

#define FIREBASE_HOST "wedsitedatcho-b9ce4-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "1a4N9tIQoB1osG34gZq9E9gBNOmvFU0iknWuNwT2"
FirebaseData fbdb;
uint8_t num1, num2, num1s, num2s;
String test;
void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Đặt thời gian chờ đọc cơ sở dữ liệu thành 1 phút (tối đa 15 phút)
  Firebase.setReadTimeout(fbdb, 1000 * 60);

  // Đặt giới hạn kích thước ghi (ví dụ: tiny, small, medium, large)
  Firebase.setwriteSizeLimit(fbdb, "tiny");  // Tên hàm đã được sửa
}

void loop() {
  if (Firebase.getInt(fbdb, "/T0/BL2")) {
    num1 = fbdb.to<int>();
    Serial.println(num1);
  }
  if (Firebase.getString(fbdb, "/T0/BL1/RFID")) {
    test = fbdb.to<const char *>();
    Serial.println(test);
  }
  // Firebase.set(fbdb, F("/test/json"), rand());
  delay(100);
}
