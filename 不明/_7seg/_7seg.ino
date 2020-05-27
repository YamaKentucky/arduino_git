void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
}

void loop() {
  int val = analogRead(0);
  if (val < 500) {
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    analogWrite(16, (500 - val) / 2);
  }

  else if (500 <= val && val <= 600) {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
  }

  else  {
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    analogWrite(16, (val - 600) / 2);
  }

}

