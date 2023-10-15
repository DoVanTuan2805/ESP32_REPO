#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "EEPROM.h"

char* auth = "ehPfygBtcYMtB7AFUtscdG7fZtb51tp-";
// char ssid[] = "NGOC XUAN";
// char pass[] = "01021967";
#define LENGTH(x) (strlen(x) + 1)
#define EEPROM_SIZE 200
#define WIFI_RESET 0
String ssid;
String password;
unsigned long millis_RESET;
void setup() {
  Serial.begin(115200);
  pinMode(WIFI_RESET, INPUT);
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to init EEPROM");
    delay(1000);
  } else {
    ssid = read_flash(0);
    Serial.print("SSID = ");
    Serial.println(ssid);
    password = read_flash(40);
    Serial.print("Password = ");
    Serial.println(password);
  }

  WiFi.begin(ssid.c_str(), password.c_str());

  delay(3500);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_AP_STA);
    WiFi.beginSmartConfig();

    Serial.println("Waiting for SmartConfig.");
    while (!WiFi.smartConfigDone()) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("SmartConfig received.");

    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi Connected.");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    ssid = WiFi.SSID();
    password = WiFi.psk();
    Serial.print("SSID:");
    Serial.println(ssid);
    Serial.print("password:");
    Serial.println(password);
    Serial.println("Store SSID & password in Flash");
    write_flash(ssid.c_str(), 0);
    write_flash(password.c_str(), 40);
  } else {
    Serial.println("WiFi Connected");
  }
  Blynk.config(auth, "blynk-server.com", 8080);
}

void loop() {
  Blynk.run();
  // Serial.println("xin chao");
  millis_RESET = millis();
  while (digitalRead(WIFI_RESET) == LOW) {
    Serial.println("Here");
  }

  if (millis() - millis_RESET >= 5000) {
    Serial.println("Reseting the WiFi credentials");
    write_flash("", 0);
    write_flash("", 40);
    Serial.println("Wifi credentials erased");
    Serial.println("Restarting the ESP");
    delay(500);
    ESP.restart();
  }
}

void write_flash(const char* toStore, int startAddr) {
  int i = 0;
  for (; i < LENGTH(toStore); i++) {
    EEPROM.write(startAddr + i, toStore[i]);
  }
  EEPROM.write(startAddr + i, '\0');
  EEPROM.commit();
}
String read_flash(int startAddr) {
  char in[128];
  int i = 0;
  for (; i < 128; i++) {
    in[i] = EEPROM.read(startAddr + i);
  }
  return String(in);
}