String uartRcv;
int i = 0;
void uartHandle() {
  static bool dataComplete;
  i = 0;
  while (Serial.available() > 0) {
    dataComplete = false;
    char c = Serial.read();
    // Serial.print(c);
    if (c != '.') {
      uartRcv += c;
    } else {
      String t1 = tach_chuoi(uartRcv, " ", 0);
      String t2 = tach_chuoi(uartRcv, " ", 1);
      if (t1 == "STemp") {        
        Temperature.SetTemp = t2.toInt();
        Serial.println(Temperature.SetTemp);
      } else if (t1 == "DTemp") {
        setting.int8DTemp = t2.toInt();
        Serial.println(setting.int8DTemp);
      }
    }
  }
}
String tach_chuoi(String text, String ki_tu, uint16_t vi_tri) {
  String tmp = text;
  for (int i = 0; i < vi_tri; i++) {
    tmp = tmp.substring(tmp.indexOf(ki_tu) + 1);
    if (tmp.indexOf(ki_tu) == -1 && i != vi_tri - 1) {  // neu ko tim thay ki tu (delim)tra ve -1
      return "";
    }
  }
  return tmp.substring(0, tmp.indexOf(ki_tu));
}