void control_solanh_maysuoi(float tempC) {
  if (tempC > nhietDoCao) {
    // Serial.println("Here So Lanh");
    OnSolanh();  // On quat, so lanh
    OffMaySuoi();
  } else if (tempC < nhietDoThap) {
    // Serial.println("Here May Suoi");
    OffSolanh();
    OnMaySuoi();
  } else {
    OffMaySuoi();
    OffSolanh();
  }
}