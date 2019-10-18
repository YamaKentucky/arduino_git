
#include <avr/sleep.h>

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, INPUT);
}

void loop() {
  if (digitalRead(0) == HIGH) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    set_sleep_mode(SLEEP_MODE_IDLE);
    noInterrupts();
    sleep_enable();
    interrupts();
    sleep_cpu();
    sleep_disable();
  }
  else if (digitalRead(0) == LOW) {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  }
}


