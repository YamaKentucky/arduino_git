#include <Servo.h>
Servo mServo;
unsigned long duration;
int Steering_val = 90;

void setup() {
 mServo.attach(9);
Serial. begin(9600);
 pinMode(3,INPUT);
}

void loop() {
 duration = pulseIn(3,HIGH,100000);
 //static float y[2] = {0};
  //y[1] = 0.9 * y[0] + 0.1* duration;
  //y[0] = y[1];
 //Steering_val = map(y[0], 0, 666, 0, 180); 
 mServo.write(duration);
 Serial.println(duration);
 delay(10);
}
