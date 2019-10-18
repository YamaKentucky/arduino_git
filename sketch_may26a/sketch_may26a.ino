int val=0; //入力される値を格納する為の変数
void setup() {
Serial.begin(115200); //モニターに出力するための設定
}
void loop() {
//ANALOG INの０番ピンからデータを受け付ける
val=analogRead(0);
 
static float y[2] = {0};
  y[1] = 0.7 * y[0] + 0.3 * val;  
  y[0] = y[1];
  Serial.println(y[0]);

delay(0.1);
}
