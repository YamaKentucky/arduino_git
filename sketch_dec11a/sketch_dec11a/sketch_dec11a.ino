void setup() {
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);


}

void loop() {
  int a = digitalRead(8);
  int b = digitalRead(9);
  digitalWrite(11, a);
  digitalWrite(12, b);

}
