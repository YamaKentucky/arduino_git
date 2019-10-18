String str_out;
int d0_true = 23983, d1_true = 30098, d2_true = 7989, d3_true = 1897;

void setup() {
  Serial.begin(115200);
  str_out = String(d0_true) + "," + String(d1_true) + "," + String(d2_true) + "," + String(d3_true) ;
}

void loop() {
  //  sendIntData(12345); // int型データの送信
  //  delay(500);
  //
  //  sendIntData(23454); // int型データの送信
  //  delay(500);
  Serial.println(str_out);
  delay(100);
}

// int型のデータを送信する関数
//void sendIntData(int value) {
//  Serial.write('H'); // ヘッダの送信
//  Serial.write(lowByte(value)); // 下位バイトの送信
//  Serial.write(highByte(value)); // 上位バイトの送信
//}
