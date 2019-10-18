unsigned long time;

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, keisoku, CHANGE);
}
void loop() {
  Serial.println("Standingby");
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(9, LOW);
  delay(500);
}

void keisoku() {
  analogReadResolution(16);
  float ms2 = 9.80665;
  float x , y , z;
  x = y = z = 0 ;
  int x0 , y0 , z0 ; // 0Gの数値を入れる
  int x1 , y1 , z1 ; // 1Gの数値から0Gの数値を引いた数値を入れる
  x0 = 32866 ; y0 = 32904 ; z0 = 32734 ;
  x1 = 13038 ; y1 = 12990 ; z1 = 13016 ;
  z = analogRead(2);
  z = (z  - z0) / z1 ;
  for (int i = 0; i < 10; i++) {
    for (int k = 0; k < 100; k++) {
      unsigned long last = 0;
      unsigned long time = 0;
      time = millis();
      if (time - last > 10) {
        Serial.println(z * ms2, 4);
        last = time;
      }
    }
  }

}
