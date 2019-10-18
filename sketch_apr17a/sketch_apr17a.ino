
  #include<Servo.h>

  Servo mServo;
  
  void setup() {
    mServo.attach(9);
    
  // put your setup code here, to run once:

}

void loop() {
 long val=analogRead(0);
 mServo.write(val*180/1024);
}
