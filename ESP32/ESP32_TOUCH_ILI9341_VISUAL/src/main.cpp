#include "Arduino.h"
#include "init.h"
int parseForNumber(int x, int y);

bool PAD_DOWN = false;
typedef struct
{
  int Touch_X;
  int Touch_Y;
} Touch_t;
Touch_t Position;
bool tt;

void setup()
{
  Serial.begin(115200);
  init_Relay();
  init_Screen();
  menu1();
  init_Touch();
  // init_Sensor();
  Serial.println("Touch screen ready.");
}
void loop()
{
  if (touch.tirqTouched())
  {
    if (touch.touched())
    {
      rawLocation = touch.getPoint();
      Position.Touch_X = rawLocation.x;
      Position.Touch_Y = rawLocation.y;
      tft.setCursor(250 + 10, 220 + 10);
      tft.setTextColor(ILI9341_BLUE);
      tft.print("X: ");
      tft.print(Position.Touch_X);
      tft.print("-- Y: ");
      tft.print(Position.Touch_Y);
      PAD_DOWN = true;
    }
  }
  if (PAD_DOWN == true)
  {
    int num = parseForNumber(Position.Touch_X, Position.Touch_Y);
    PAD_DOWN = false;
    delay(100);
  }
}
int parseForNumber(int x, int y)
{
  int mx = x / 50;
  int my = y / 50;
  Serial.print(mx);
  Serial.print("--- Y : ");
  Serial.print(my);
  Serial.println();
  if ((mx < 40 && mx > 20))
  {
    if ((my < 80 && my > 60))
    {
      if (tt == 0)
      {
        tt = 1;
      }
      else
      {
        tt = 0;
      }
    }
  }
  int number = 0;
  return number;
}