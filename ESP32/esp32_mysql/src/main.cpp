#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_wifi.h>
// PATH : C:\xampp\htdocs\esp32_test
String URL = "http://192.168.1.159:8080/esp32_test/postdemo.php";

/* Set these to your desired credentials. */
const char *ssid = "WiFi";
const char *pass = "00001111";

// Web/Server address to read/write from
const char *host = "192.168.43.128"; // https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup()
{
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF); // Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA); // This line hides the viewing of ESP as wifi hotspot

  WiFi.begin(ssid, pass); // Connect to your WiFi router
  Serial.println("");
  byte macAddress[6];
  esp_wifi_get_mac(ESP_IF_WIFI_STA, macAddress);

  // Print the MAC address to the serial monitor
  Serial.print("MAC address: ");
  for (int i = 0; i < 6; i++)
  {
    Serial.print(macAddress[i], HEX);
    if (i < 5)
    {
      Serial.print(":");
    }
  }
  Serial.println();
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop()
{
  HTTPClient http; // Declare object of class HTTPClient

  String postData;

  // Post Data
  postData = "temperature=" + String(random(0, 20)) + "&humidity=" + String(random(0, 20));

  http.begin(URL);                                                     // Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Specify content-type header

  int httpCode = http.POST(postData); // Send the request
  String payload = http.getString();  // Get the response payload

  Serial.println(httpCode); // Print HTTP return code
  Serial.println(payload);  // Print request response payload

  http.end(); // Close connection

  delay(5000); // Post Data at every 5 seconds
}