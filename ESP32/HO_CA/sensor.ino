#include <OneWire.h>
#include <DallasTemperature.h>


bool valueCBHN = 1;

const int oneWireBus = 5;

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);


uint64_t timeDs1820;

void initDs18b20() {
  sensors.begin();
  pinMode(CBHN , INPUT);
}
void readDs18b20() {
  valueCBHN = digitalRead(CBHN);
  if (millis() - timeDs1820 > 1500) {
    sensors.requestTemperatures();
    temperatureC = sensors.getTempCByIndex(0);
    // Serial.println(hour);
    String data = String(temperatureC) + "/" + String(valueCBHN);
    
    Serial2.println(data);
    timeDs1820 = millis();
  }
}
