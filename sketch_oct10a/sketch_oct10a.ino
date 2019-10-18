void setup()
{
// シリアルモニターの初期化をする
Serial.begin(9600) ;
}
void loop()
{
long x , y , z ;
x = y = z = 0 ;
x = analogRead(0) ; // Ｘ軸
y = analogRead(1) ; // Ｙ軸
z = analogRead(2) ; // Ｚ軸
//Serial.print("X:") ;
Serial.print(x) ;
Serial.print(",") ;
//Serial.print(" Y:") ;
Serial.print(y) ;
Serial.print(",") ;
//Serial.print(" Z:") ;
Serial.println(z) ;
delay(50) ;
}
