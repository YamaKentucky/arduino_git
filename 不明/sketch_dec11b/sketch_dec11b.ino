void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0, LED, CHANGE);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  Serial.println("standingby");
  delay(1000);
}

void LED() {
  digitalWrite(3, HIGH);
  delay(3000);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(3000);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  delay(3000);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(3000);
}

