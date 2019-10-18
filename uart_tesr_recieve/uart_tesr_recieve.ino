#define HWSERIAL Serial1
String recv_data; // 受信データ

void setup() {
  HWSERIAL.begin(115200);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  //  if ( HWSERIAL.available() >= sizeof('H') + sizeof(int) ) {
  //    // ヘッダの確認
  //    if ( HWSERIAL.read() == 'H' ) {
  //      int low = HWSERIAL.read(); // 下位バイトの読み取り
  //      int high = HWSERIAL.read(); // 上位バイトの読み取り
  //      recv_data = makeWord(high, low); // 上位バイトと下位バイトを合体させてint型データを復元
  //    }
  //    Serial.println("OK!!");
  //    Serial.println(recv_data);
  //  }
  //
  //  // 受信したデータに基づいてLEDをON/OFF
  //  if ( recv_data == 12345 ) {
  //    digitalWrite(13, HIGH);
  //  }
  //
  //  if ( recv_data == 23454 ) {
  //    digitalWrite(13, LOW);
  //  }
  if (HWSERIAL.available() > 0) {
    recv_data = HWSERIAL.readStringUntil('\n');
    Serial.println(recv_data);
    //delay(1000);
  }
}
