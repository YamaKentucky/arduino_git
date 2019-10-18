#include <MsTimer2.h>

void f(){
  float val;
  val=analogRead(0);
  Serial.println(val-780,4);
}

void setup() {
  Serial.begin(230400);
  MsTimer2::set(3.5,f);
  MsTimer2::start();
 }
void loop() {
  
}



