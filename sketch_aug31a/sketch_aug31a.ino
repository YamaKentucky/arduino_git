#include <avr/sleep.h>
#include <avr/interrupt.h>
int count = 0;

void wakeUpNow() {
  Serial.println("wake up!"); //復帰時にシリアルモニターに表示
  digitalWrite(4, LOW);
  delay(1000);
}

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(115200);
}

void sleepNow() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts();
  sleep_enable();
  attachInterrupt(0, wakeUpNow, RISING);
  sleep_cpu();
  sleep_disable();
}

void loop()
{
  if (count > 10) {
    Serial.println("Goodnight!");
    delay(100);
    count = 0;
    sleepNow(); //スリープモードにする
  }

  Serial.print(count); //動作中の表示
  Serial.println("sec");
  if ((count % 2) == 0) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  count++;
  delay(1000);
}
