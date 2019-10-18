void setup() {
  //DDRC = DDRC | B00000100;
  //DDRD = DDRD | B01000000;
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
}

void loop() {
  PORTC |= _BV(5);
  PORTD &= ~_BV(1);
  //digitalWrite(13,HIGH);
  //digitalWrite(14, HIGH);
}
