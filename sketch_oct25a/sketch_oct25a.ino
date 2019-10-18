void setup()
{
  // シリアルモニターの初期化をする
  Serial.begin(9600) ;
}
void loop(){
  analogReadResolution(16);
  unsigned long t = micros();
  long x , y , z ;
  x = y = z = 0 ;
  x = analogRead(0) ; // Ｘ軸
  y = analogRead(1) ; // Ｙ軸
  z = analogRead(2) ; // Ｚ軸
  Serial.print(1000 - micros() + t) ;
  Serial.print(",") ;
  Serial.print(x) ;
  Serial.print(",") ;
  Serial.print(y) ;
  Serial.print(",") ;
  Serial.println(z) ;
  unsigned long D = 1000 - micros() + t;
  delayMicroseconds(D) ;
}
