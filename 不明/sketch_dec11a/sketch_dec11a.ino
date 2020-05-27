volatile int  sw = LOW;
volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 100;
volatile char inputchar = 0;
void setup() {
  attachInterrupt(0, blink, CHANGE);
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {

}

void blink() {
  time_now = millis(); //現在の割り込み時刻を取得
  if ( time_now - time_prev > time_chat) {
    if ( sw == LOW ) //前回の割り込みから20[ms]以上経過かつスイッチの状態がLowならば、LED消点灯を切り替え
      switch (inputchar) {
        case 0:
          Serial.print("EPM ON\n");
          digitalWrite(2, HIGH);
          delay(2000);
          digitalWrite(2, LOW);
          inputchar = 1;
          break;

        case 1:
          Serial.print("EPM OFF\n");
          digitalWrite(1, HIGH);
          delay(500);
          digitalWrite(2, HIGH);
          delay(2000);
          digitalWrite(2, LOW);
          delay(500);
          digitalWrite(1, LOW);
          inputchar = 0;
          break;
      }
    sw = !sw; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev = time_now; //現在の割り込み時刻を前回の割り込み時刻へコピー
}
