#include<MsTimer2.h>
void setup() {
  Serial.begin(19200);
  // MsTimer2::set(0.002,loop);
   //MsTimer2::start();
}

void loop() {
  
  static float y[2] = {0};
  y[1] = 0.6144 * y[0] + 0.38586 * analogRead(0);
  y[0] = y[1];
  Serial.println(y[1]);
  delay(2);

}
