#include <Arduino.h>
#include "soc/rtc_wdt.h"
#include <esp_task_wdt.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>

// #define BLYNK_TEMPLATE_ID "TMPL6-32afmnl"
// #define BLYNK_TEMPLATE_NAME "Cong To Dien"
#define BLYNK_AUTH_TOKEN "lCCX15xQYT_bmfdpb0VfYEqVj2d5qHkJ"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT softSerial

char ssid[] = "NGOC XUAN";
char pass[] = "01021967";

BlynkTimer timerBlynk, timerData, timerPzem;

#define VoltDC V5
#define CurrDC V4
#define PowerDC V6
#define EnergyDC V7

#define VoltAC V0
#define CurrAC V1
#define PowerAC V2
#define EnergyAC V3

static uint8_t pzemSlaveAddr = 0x01;
static uint16_t NewshuntAddr = 0x0001;

#define RELAY1_PIN 0
#define RELAY2_PIN 15

LiquidCrystal_I2C lcd(0x27, 20, 4);

PZEM004Tv30 pzem(&Serial2); // RX TX

SoftwareSerial softSerial;
ModbusMaster node;
uint8_t tt_clear = 0;

typedef struct
{
  float voltage;
  float current;
  float power;
  float energy;
} Data_Pzem_t;

Data_Pzem_t AC, DC;

void ReadPzem(void);
void LcdEnergyAC(void);
void myTimerPush(void);
void myTimerData(void);
BLYNK_WRITE(V1);
void changeAddress(uint8_t OldslaveAddr, uint8_t NewslaveAddr);
void setShunt(uint8_t slaveAddr);

void setup()
{
  Serial.begin(115200);
  softSerial.begin(9600, SWSERIAL_8N1, 32, 33, false, 20);
  setShunt(0x00);
  node.begin(pzemSlaveAddr, softSerial);
  changeAddress(0XF8, 0x01);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk-server.com", 8080);
  timerBlynk.setInterval(2000L, myTimerPush);
  timerPzem.setInterval(2000L, ReadPzem);
  timerData.setInterval(2500L, myTimerData);

  DC.voltage = 0;
  DC.current = 0;
  DC.power = 0;
  DC.energy = 0;

  AC.voltage = 0;
  AC.current = 0;
  AC.power = 0;
  AC.energy = 0;
}
uint64_t timeRead, timeRead1;
void loop()
{
  Blynk.run();
  // timerBlynk.run();
  // timerData.run();
  // timerPzem.run();
  Serial.println("chao");
  if (millis() - timeRead >= 2000)
  {
    ReadPzem();
    timeRead = millis();
  }
  if (millis() - timeRead1 >= 2500)
  {
    LcdEnergyAC();
    myTimerData();
    myTimerPush();
    timeRead1 = millis();
  }
}
void ReadPzem(void)
{
  uint8_t result;

  rtc_wdt_protect_off();
  rtc_wdt_disable();

  result = node.readInputRegisters(0x0000, 6);
  // esp_task_wdt_init(1, true); // enable panic so ESP32 restarts
  // esp_task_wdt_add(NULL);     // add current thread to WDT watch

  if (result == node.ku8MBSuccess) /* If there is a response */
  {
    uint32_t tempdouble = 0x00000000;                    /* Declare variable "tempdouble" as 32 bits with initial value is 0 */
    DC.voltage = node.getResponseBuffer(0x0000) / 100.0; /* get the 16bit value for the voltage value, divide it by 100 (as per manual) */
                                                         // 0x0000 to 0x0008 are the register address of the measurement value
    DC.current = node.getResponseBuffer(0x0001) / 100.0; /* get the 16bit value for the current value, divide it by 100 (as per manual) */

    tempdouble = (node.getResponseBuffer(0x0003) << 16) + node.getResponseBuffer(0x0002); /* get the power value. Power value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit */
    DC.power = tempdouble / 10.0;                                                         /* Divide the value by 10 to get actual power value (as per manual) */

    tempdouble = (node.getResponseBuffer(0x0005) << 16) + node.getResponseBuffer(0x0004); /* get the energy value. Energy value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit */
    DC.energy = tempdouble;
  }
  else
  {
    DC.voltage = 0;
    DC.current = 0;
    DC.power = 0;
    DC.energy = 0;
  }
}

void LcdEnergyAC(void)
{
  char *line0 = " V    A    W    KWh  ";
  char dataDC[20];

  sprintf(dataDC, "%.1f %.2f  %.2f  %.1f", DC.voltage, DC.current, DC.power, DC.energy);
  lcd.setCursor(0, 0); // x y
  lcd.print(line0);
  lcd.setCursor(0, 3);
  lcd.print(dataDC);
  memset(dataDC, 0, sizeof(dataDC));
  lcd.setCursor(0, 2);
  lcd.print("                    ");
}
void myTimerData(void)
{
  AC.voltage = pzem.voltage();
  AC.energy = pzem.energy();
  AC.power = pzem.power();
  AC.current = pzem.current();
  if (AC.voltage == NAN)
  {
    AC.voltage = 0;
  }
  if (AC.energy == NAN)
  {
    AC.energy = 0;
  }
  if (AC.power == NAN)
  {
    AC.power = 0;
  }
  if (AC.current == NAN)
  {
    AC.current = 0;
  }
  char dataAC[20];
  lcd.setCursor(0, 1);
  sprintf(dataAC, "%.0f %.2f  %.2f  %.1f", AC.voltage, AC.current, AC.power, AC.energy);
  lcd.print(dataAC);
  memset(dataAC, 0, sizeof(dataAC));
}
void myTimerPush(void)
{
  // LcdEnergyAC();
  Blynk.virtualWrite(VoltAC, AC.voltage);
  Blynk.virtualWrite(CurrAC, AC.current);
  Blynk.virtualWrite(PowerAC, AC.power);
  Blynk.virtualWrite(EnergyAC, AC.energy);

  Blynk.virtualWrite(VoltDC, DC.voltage);
  Blynk.virtualWrite(CurrDC, DC.current);
  Blynk.virtualWrite(PowerDC, DC.power);
  Blynk.virtualWrite(EnergyDC, DC.energy);
}
BLYNK_CONNECTED()
{
  Blynk.syncAll();
}
BLYNK_WRITE(V8)
{
  bool relay2 = param.asInt();
  if (relay2 == 1)
  {
    digitalWrite(RELAY2_PIN, 1);
  }
  else
  {
    digitalWrite(RELAY2_PIN, 0);
  }
}
BLYNK_WRITE(V10)
{
  bool relay1 = param.asInt();
  if (relay1 == 1)
  {
    digitalWrite(RELAY1_PIN, 1);
  }
  else
  {
    digitalWrite(RELAY1_PIN, 0);
  }
}
void setShunt(uint8_t slaveAddr) // Change the slave address of a node
{
  static uint8_t SlaveParameter = 0x06;     /* Write command code to PZEM */
  static uint16_t registerAddress = 0x0003; /* change shunt register address command code */

  uint16_t u16CRC = 0xFFFF;                 /* declare CRC check 16 bits*/
  u16CRC = crc16_update(u16CRC, slaveAddr); // Calculate the crc16 over the 6bytes to be send
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewshuntAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewshuntAddr));

  softSerial.write(slaveAddr); /* these whole process code sequence refer to manual*/
  softSerial.write(SlaveParameter);
  softSerial.write(highByte(registerAddress));
  softSerial.write(lowByte(registerAddress));
  softSerial.write(highByte(NewshuntAddr));
  softSerial.write(lowByte(NewshuntAddr));
  softSerial.write(lowByte(u16CRC));
  softSerial.write(highByte(u16CRC));
  while (softSerial.available()) /* while receiving signal from Serial23 from meter and converter */
  {
  }
}
void changeAddress(uint8_t OldslaveAddr, uint8_t NewslaveAddr) // Change the slave address of a node
{
  static uint8_t SlaveParameter = 0x06;        /* Write command code to PZEM */
  static uint16_t registerAddress = 0x0002;    /* Modbus RTU device address command code */
  uint16_t u16CRC = 0xFFFF;                    /* declare CRC check 16 bits*/
  u16CRC = crc16_update(u16CRC, OldslaveAddr); // Calculate the crc16 over the 6bytes to be send
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewslaveAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewslaveAddr));

  softSerial.write(OldslaveAddr); /* these whole process code sequence refer to manual*/
  softSerial.write(SlaveParameter);
  softSerial.write(highByte(registerAddress));
  softSerial.write(lowByte(registerAddress));
  softSerial.write(highByte(NewslaveAddr));
  softSerial.write(lowByte(NewslaveAddr));
  softSerial.write(lowByte(u16CRC));
  softSerial.write(highByte(u16CRC));
  while (softSerial.available()) /* while receiving signal from Serial23 from meter and converter */
  {
  }
}