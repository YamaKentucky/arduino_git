//加速度センサの値を取得するプログラム
//********************************
void setup()
{
  // シリアルモニターの初期化をする
  Serial.begin(115200) ;
}
void loop()
{
  long x , y , z ;
  x = y = z = 0 ;
  //x = analogRead(3) ; // Ｘ軸
  //y = analogRead(4) ; // Ｙ軸
  float  Z = analogRead(0);
  int i;
  static float val[11];
  float val_z;
  val[10]  = Z ;
  for (i = 0; i < 10; i++) {
    val[i] = val[i + 1];
    val_z += val[i];
  }
  val_z /= 10;
  float z1 = (val_z - 1) * 9.81 ;
  analogReadResolution(16);
  Serial.println((val_z / 49535-1)*9.80665,4) ;
  delay(5) ;
}
