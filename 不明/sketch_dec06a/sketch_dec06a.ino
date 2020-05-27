void setup() {
  Serial.begin(115200);

}

void loop() {
  //analogReadResolution(16);
  float zA = analogRead(A0);
  Serial.println(zA);
  delay(50);
}
