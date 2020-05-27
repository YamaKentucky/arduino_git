void setup() {
  // open a serial connection
  Serial.begin(9600);
}

void loop() {
  
  analogReadResolution(24);
  Serial.print(", 24-bit : ");
  Serial.println(analogRead(A0));

  // a little delay to not hog serial monitor
  delay(100);
}
