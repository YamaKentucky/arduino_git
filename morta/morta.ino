#include <Servo.h>
Servo mServo;
int inPin = 7;
int val = 0;
unsigned long duration;
String str_send_data;
unsigned long sTime = 0;
unsigned long rTime = 0;
unsigned long cTime = 0;
 
void setup() {   
  mServo.attach(9);             
  Serial.begin(115200);
  sTime = millis();
  pinMode(inPin, INPUT);
}
 
void loop() {
  cTime = millis() - sTime;
  rTime = millis();
  duration = pulseIn(inPin, HIGH, 100000);
  //str_send_data = String(cTime) + "," + String(duration);
  //Serial.println(str_send_data);
 
 Serial.println(duration);
  while(millis() - rTime < 100){
    delay(0.01);
    mServo.write(duration*180/750);
  }
}
