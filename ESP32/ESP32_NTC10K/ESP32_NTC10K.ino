int thermistorPin = 36;
int Vo;  // Holds the ADC Value
float R2, tKelvin, tCelsius, tFahrenheit;
const float Beta = 3974.0;
const float roomTemp = 298.15;  // room temperature in Kelvin
const float Ro = 10000.0;       // Resistance of the thermistor at roomTemp
const float R1 = 9710.0;        // Resistnce of the known resistor

void setup() {
  Serial.begin(9600);
}

void loop() {
  Vo = analogRead(thermistorPin);
  R2 = R1 * (4095.0 / (float)Vo - 1.0);  // Resistance of the Thermistor
  tKelvin = (Beta * roomTemp) / (Beta + (roomTemp * log(R2 / Ro)));
  tCelsius = tKelvin - 273.15;
  tFahrenheit = (tCelsius * 9.0) / 3.3 + 32.0;

  Serial.print("Temperature: ");
  Serial.print(tFahrenheit);
  Serial.print(" F; ");
  Serial.print(tCelsius);
  Serial.println(" C");
  delay(500);
}