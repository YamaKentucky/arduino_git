

void setup() {
  analogReadResolution(16);
  Serial.begin(115200);
}

void loop() {
float z, Z = 0;
  for (int i = 0; i < 1000; i++) {
    z = z + analogRead(0);
  }
  Z = z / 1000;
  Serial.println(Z);
  delay(1000);
  /*z = analogRead(0);
    Serial.println(z);*/
}
