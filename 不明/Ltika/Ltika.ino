void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val;
  val = analogRead(0);
  Serial.print("analog value =");
  Serial.println(val);

  if (val < 360) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(3, LOW);
  }

  else if (val < 720) {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(3, LOW);
  }

  else if(val>720)   {
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(3, HIGH);
  }
}

// put your main code here, to run repeatedly:


