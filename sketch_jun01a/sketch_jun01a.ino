#include <Servo.h>

Servo mServo;
void setup() {
 mServo.attach(9);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
long val=analogRead(0);
mServo.write(val*180/1024);
Serial.println(val);
}
