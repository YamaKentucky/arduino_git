
#include <Servo.h>
Servo mServo;

void setup() {
  mServo.attach(9);
  mServo.write(87);
  Serial.begin(9600);
}

void loop() {
  int pos;
  int wait_t;
  int val;

  pos = random(1, 4);
  wait_t = random(300, 1000);
  val = analogRead(0);

  if (pos == 1) {
    mServo.write(60);
    delay(wait_t);
    if (512 < val){
     tone(11,440);
     delay(200);
     tone(11,349);
     delay(300);
     noTone(11);
    }
    else if(val<512){
      tone(11,262);
      delay(200);
      noTone(11);
      tone(11,262);
      delay(300);
      noTone(11);
    }
    
}
else if (pos == 2) {
  mServo.write(120);
  delay(wait_t);
  if (val < 512){
    tone(11, 440);
    delay(200);
    tone(11,349); 
    delay(300);
    noTone(11);
  }
  else if(512<val){
   tone(11,262);
   delay(200);
   noTone(11);
   tone(11,262);
   delay(200);
   noTone(11);
   }
   
 }
 
mServo.write(87);
delay(500);
Serial.println(val);

if(millis()>60000){
  tone(11,330);
  delay(1000);
  noTone(11);
  while(1);
  } 
}
  
 
