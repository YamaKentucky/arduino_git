void setup() {
 Serial.begin(4800);

}

void loop() {
 int val;
  val=analogRead(0);
  Serial.println(val);

}
