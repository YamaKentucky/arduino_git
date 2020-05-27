void setup()
{
  // シリアルモニターの初期化をする
  Serial.begin(9600) ;
}
void loop()
{
  analogReadResolution(16);
  int i , a ;
  float x , y , z;
  float ms2 = 9.80665;
  // KXR94-2050の個体差を調整する
  int x0 , y0 , z0 ; // 0Gの数値を入れる
  int x1 , y1 , z1 ; // 1Gの数値から0Gの数値を引いた数値を入れる
  x0 = 32866 ; y0 = 32904 ; z0 = 32734 ;
  x1 = 13038 ; y1 = 12990 ; z1 = 13016 ;

  // 各データを100回読込んで平均化する
  x = y = z = 0 ;
  for (i = 0 ; i < 1000 ; i++) {
    x = x + analogRead(0) ; // Ｘ軸を読込む
    y = y + analogRead(1) ; // Ｙ軸を読込む
    z = z + analogRead(2) ; // Ｚ軸を読込む
  }
  x = ((x / 1000) - x0) / x1 ;
  y = ((y / 1000) - y0) / y1 ;
  z = ((z / 1000) - z0) / z1 ;

  // 角度を計算して表示を行う
  //Serial.print("X=") ;
  Serial.print(x * ms2, 4) ; // X軸方向加速度表示
  Serial.print(",");
  //Serial.print(" Y=") ;
  Serial.print(y * ms2, 4) ; // X軸方向加速度表示
  Serial.print(",");
  //Serial.print(" Z=") ;
  Serial.println(z * ms2, 4) ; // Z軸方向加速度表示
  /*Serial.print(" XZ=") ;
    a=atan2(x,z) / 3.14159 * 180.0 ; // XZ方向傾斜角度
    Serial.print(a) ;
    Serial.print(" YZ=") ;
    a=atan2(y,z) / 3.14159 * 180.0 ; // YZ方向傾斜角度
    Serial.println(a) ;
  */
  delay(50) ;
}
