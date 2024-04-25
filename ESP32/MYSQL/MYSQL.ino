#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;
String URL = "http://192.168.1.159/esp32_test/esp32_test_data.php";
const char* ssid = "NGOC XUAN";
const char* password = "01021967";
int num;
void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected");
  Serial.println("IP :");
  Serial.print(WiFi.localIP());
}

void loop() {
  num = random(0, 100);
  String put = "NUM=" + String(num);
  http.begin(URL);
  int httpCode = http.POST(put);
  String payload = http.getString();
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  Serial.printf("Code : %d\n", httpCode);
  Serial.printf("payload : %s\n", payload);
  delay(1000);
}
