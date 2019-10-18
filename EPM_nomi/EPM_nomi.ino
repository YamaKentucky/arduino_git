volatile int sw = LOW, sw_E = LOW, sw_S = LOW;
volatile unsigned long time_prev = 0, time_prev_E = 0, time_prev_S = 0, time_now, time_now_E, time_now_S;
volatile char inputchar = 0;
unsigned long time_chat = 20;

void setup() {
  pinMode(3, OUTPUT);  //EPM
  pinMode(4, OUTPUT);  //EPM
  pinMode(9, OUTPUT);  //LED_log
  pinMode(10, OUTPUT); //LED_EPM,Syoki
  digitalWriteFast(9, HIGH);
  attachInterrupt(1, EPM, RISING);
}


void EPM() {
  time_now_E = millis(); //現在の割り込み時刻を取得
  if ( time_now_E - time_prev_E > time_chat) {
    if ( sw_E == LOW ) //前回の割り込みから20[ms]以上経過かつスイッチの状態がLowならば、LED消点灯を切り替え
      switch (inputchar) {
        case 0:
          digitalWrite(10, HIGH); //LED表示
          Serial.print("EPM ON\n");//EPMをONにする
          digitalWrite(4, HIGH);
          delay(2000);
          digitalWrite(4, LOW);
          inputchar = 1;
          break;

        case 1:
          digitalWrite(10, LOW); //LED表示
          Serial.print("EPM OFF\n");//EPMをOFFにする
          digitalWrite(3, HIGH);
          delay(500);
          digitalWrite(4, HIGH);
          delay(2000);
          digitalWrite(4, LOW);
          delay(500);
          digitalWrite(3, LOW);
          inputchar = 0;
          break;
      }
    sw_E = !sw_E; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev_E = time_now_E; //現在の割り込み時刻を前回の割り込み時刻へコピー
}


void loop() {
  delay(1000000);
}
