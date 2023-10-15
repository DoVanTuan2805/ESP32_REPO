#define LENGTH(x) (strlen(x) + 1)
#define EEPROM_SIZE 200
#define WIFI_RESET 0
String ssid;
String password;
/* DEFINE BUTTON CONFIG */
int lastState = HIGH;
int currentState;
const int LONG_PRESS_TIME = 5000;  // 1000 milliseconds
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;
/* DEFINE BLYNK CONFIG */


// char* auth = "ehPfygBtcYMtB7AFUtscdG7fZtb51tp-";
char* server = "blynk-server.com";
uint16_t port = 8080;

void setupWiFi() {
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
  /*  BLYNK LEGACY  */
  // Blynk.config(auth, server, port);

  /*  BLYNK IOT  */
  // Blynk.config(auth);
  Blynk.config(BLYNK_AUTH_TOKEN);
}
void setupBlynk() {
}
void Button_config_Wifi() {
  currentState = digitalRead(WIFI_RESET);

  if (lastState == HIGH && currentState == LOW)  // button is pressed
    pressedTime = millis();
  else if (lastState == LOW && currentState == HIGH) {  // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if (pressDuration > LONG_PRESS_TIME) {
      Serial.println("Reseting the WiFi credentials");
      write_flash("", 0);
      write_flash("", 40);
      Serial.println("Wifi credentials erased");
      Serial.println("Restarting the ESP");
      ESP.restart();
    }
  }
  // save the the last state
  lastState = currentState;
}

void connectionstatus() {
  if ((WiFi.status() != WL_CONNECTED)) {
    wifiCon = false;
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    Serial.println();
    Serial.println(WiFi.localIP());
    //Alternatively, you can restart your board
    //ESP.restart();
  } else {
    wifiCon = true;
    // Serial.println("wifi OK");
  }
  if (!Blynk.connected()) {
    Serial.println("Lost Blynk server connection");
    Blynk.connect();
  } else {
    // Serial.println("Blynk OK");
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