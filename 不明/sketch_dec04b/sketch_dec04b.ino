void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
}

void loop() {
  int val = digitalRead(1);
  digitalWrite(0, val);
}
