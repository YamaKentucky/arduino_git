int inputchar;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  attachInterrupt(1, epm, CHANGE);
}

void loop() {
}

void epm() {
  int a = digitalRead(2);
  int b = digitalRead(3);

  if (a == 1 && b == 0) {
    inputchar = 0;
  }
  if (a == 0 && b == 1) {
    inputchar = 1;
  }
  if (inputchar == 0) {
    Serial.print("EPM ON\n");
    digitalWrite(12, HIGH);
    delay(2000);
    digitalWrite(12, LOW);
    delay(2000);
  }

  if (inputchar == 1) {
    Serial.print("EPM OFF\n");
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(12, HIGH);
    delay(2000);
    digitalWrite(12, LOW);
    delay(500);
    digitalWrite(11, LOW);
    delay(2000);
  }
}

