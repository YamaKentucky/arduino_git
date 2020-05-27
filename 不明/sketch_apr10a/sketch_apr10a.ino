void setup()
{
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
}
void loop()
{
  static int wait_t = 1000;

  digitalWrite(9, HIGH);
  tone(3,262);
  delay(wait_t);
  while (digitalRead(2) == LOW) {
    wait_t = 1000;
  }
  digitalWrite(9, LOW);
  noTone(3);
  
  digitalWrite(10, HIGH);
  tone(3,294);
  delay(wait_t);
  while (digitalRead(2) == LOW) {
    wait_t = 1000;
  }
  digitalWrite(10, LOW);
  noTone(3);

  digitalWrite(11, HIGH);
  tone(3,330);
  delay(wait_t);
  while (digitalRead(2) == LOW) {
    wait_t = 1000;
  }
  digitalWrite(11, LOW);
  noTone(3);

  digitalWrite(12, HIGH);
  tone(3,349);
  delay(wait_t);
  if (digitalRead(2) == LOW) {
    while (digitalRead(2) == LOW);
    noTone(3);
    wait_t -= 100;
    if (wait_t < 100) {
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      delay(1000);
      digitalWrite(9, LOW);
      digitalWrite(9, LOW);
      digitalWrite(9, LOW);
      digitalWrite(9, LOW);
      wait_t = 1000;
    }
  }
  digitalWrite(12, LOW);


}

