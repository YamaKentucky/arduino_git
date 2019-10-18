#include <avr/sleep.h>

void wakeUpNow() {
  Serial.println("Goodmorning");
  delay(500);
}

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(19200);
  attachInterrupt(1, sleepNow, CHANGE);
}

void sleepNow() {
  
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  Serial.println("Goodnight!");
  delay(300);
  attachInterrupt(0, wakeUpNow, FALLING);
  noInterrupts();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  interrupts();
  sleep_cpu();
  sleep_disable();
  detachInterrupt(0);
}

void loop() {
  Serial.println("Awake!"); //動作中の表示
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(500);
}
