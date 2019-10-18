int res = 0;
void setup() {
  Serial.begin(115200);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  if (digitalRead(2) == HIGH && res != 1) {
    delay(100);
    res = 1;
    Serial.println("Right");

  }

  else if ( digitalRead(3) == HIGH && res != 2 ) {
    delay(100);
    res = 2;
    Serial.println("Left");
  }

  else if (  digitalRead(4) == HIGH && res != 0) {
    delay(100);
    res = 0;
    Serial.println("Stop");
  }


  switch (res) {
    case 0:
      digitalWrite(0, HIGH);
      digitalWrite(1, HIGH);

      delay(100);
      break;

    case 1:
      digitalWrite(0, HIGH);
      digitalWrite(1, LOW);

      delay(100);
      break;

    case 2:
      digitalWrite(0, LOW);
      digitalWrite(1, HIGH);

      delay(100);
      break;
  }
}
