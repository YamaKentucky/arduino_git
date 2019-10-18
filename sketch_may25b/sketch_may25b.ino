void setup()
{
// シリアルモニターの初期化をする
Serial.begin(115200) ;
}
void loop()
{
long x , y , z ;
x = y = z = 0 ;
x = analogRead(3) ; // Ｘ軸
y = analogRead(4) ; // Ｙ軸
z = analogRead(5) ; // Ｚ軸
Serial.print("X:") ;
Serial.print(x-650) ;
Serial.print(" Y:") ;
Serial.print(y-663) ;
Serial.print(" Z:") ;
Serial.println(z-663) ;
delay(50) ;
}
