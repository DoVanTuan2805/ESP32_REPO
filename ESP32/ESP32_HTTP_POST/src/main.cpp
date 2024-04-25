#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

String apiKey = "ORSDL0RW8FWLQ56R";
const char *serverName = "http://api.thingspeak.com/update";

#define SSID "NGOC XUAN"
#define PASS "01021967"

uint64_t timePost;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
  Serial.print("Connect WIFI !!!");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (millis() - timePost > 5000)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);

      /*
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(random(40));

      int httpResponseCode = http.POST(httpRequestData);
      */

      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      // JSON data to send with HTTP POST
      String httpRequestData = "{\"api_key\":\"" + apiKey + "\",\"field1\":\"" + String(random(40)) + "\"}";
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    timePost = millis();
  }
}
