void initRL() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);            // standard 50 hz servo
  myservo.attach(SERVO_PIN, 1000, 2000);  // attaches the servo on pin 18 to the servo object
  myservo.write(0);
  pinMode(SOLANH, OUTPUT);
  pinMode(MAYSUOI, OUTPUT);
  pinMode(BOMOXI, OUTPUT);
  pinMode(LOCNUOC, OUTPUT);
  pinMode(LED, OUTPUT);
  OffBomOxi();
  OffLed();
  OffLocNuoc();
  OffMaySuoi();
  OffSolanh();
}
void OnSolanh() {
  digitalWrite(SOLANH, 1);
}
void OffSolanh() {
  digitalWrite(SOLANH, 0);
}

void OnMaySuoi() {
  digitalWrite(MAYSUOI, 1);
}
void OffMaySuoi() {
  digitalWrite(MAYSUOI, 0);
}

void OnLocNuoc() {
  digitalWrite(LOCNUOC, 1);
}
void OffLocNuoc() {
  digitalWrite(LOCNUOC, 0);
}

void OnLed() {
  digitalWrite(LED, 1);
}
void OffLed() {
  digitalWrite(LED, 0);
}

void OnBomOxi() {
  digitalWrite(BOMOXI, 1);
}
void OffBomOxi() {
  digitalWrite(BOMOXI, 0);
}