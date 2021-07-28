#include<SD.h>
const int chipSelect = BUILTIN_SDCARD;
File dataFile;

IntervalTimer myTimer;
int Z;//accel
volatile int sw = LOW, sw_E = LOW, sw_S = LOW;
volatile unsigned long time_prev = 0, time_prev_E = 0, time_prev_S = 0, time_now, time_now_E, time_now_S;

char syokisw = 0;
volatile char inputchar = 0;
unsigned long time_chat = 20;
const int num = 10000;

float data [2] [num];
volatile unsigned long blinkCount = 0; // use volatile for shared variables
int amari;
int t0, t1;
int starttime;
int finishtime;

void setup() {
  attachInterrupt(1, keisoku, RISING);
  attachInterrupt(2, EPM, RISING);
  attachInterrupt(0, syoki, RISING);


  analogReadResolution(16);//kaizoudo

  pinMode(3, OUTPUT);  //EPM
  pinMode(4, OUTPUT);  //EPM
  pinMode(9, OUTPUT);  //LED_log
  pinMode(10, OUTPUT); //LED_EPM,Syoki
  pinMode(7, OUTPUT); //douki

  Serial.begin(9600);
  digitalWriteFast(9, HIGH);


  Serial.print(F("Initializing SD card..."));
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    // 失敗、何もしない
    while (1);
  }

  Serial.println(F("ok."));
  if (SD.exists("datalog.csv")) {
    SD.remove("datalog.csv");
    Serial.println(F("File exist! Remove File."));
  }
  digitalWriteFast(9, HIGH);
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

void syoki() {
  time_now_S = millis(); //現在の割り込み時刻を取得
  if ( time_now_S - time_prev_S > time_chat) {
    if ( sw_S == 0 ) {
      if (syokisw == 0) {
        t0 = millis();
        Serial.print("syokiawase");
        digitalWrite(10, HIGH); //LED表示
        delay(1000);
        digitalWrite(10, LOW);
        syokisw = 1;
      }
    }
    sw_S = !sw_S; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev_S = time_now_S; //現在の割り込み時刻を前回の割り込み時刻へコピー
}



void keisoku() {
  time_now = millis(); //現在の割り込み時刻を取得
  if ( time_now - time_prev > time_chat) {
    if ( sw == LOW ) {
      //delay(3000);
      digitalWriteFast(7, HIGH);  //douki_ON
      if ((time_now - t0) % 2 == 1) {
        delay(1);
      }
      myTimer.begin(ReadAnalog, 2000);  // 500 Hz
    }
    sw = !sw; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev = time_now; //現在の割り込み時刻を前回の割り込み時刻へコピー
}

void logging() {
  for (int m = 0; m < 20; m++) {
    dataFile = SD.open("datalog.csv", FILE_WRITE);
    for (int k = 0; k < 500; k++) {
      delay(2);
      Serial.print("Number = ");
      Serial.print(k + 1 + 500 * m);
      Serial.print(",");
      Serial.print(data [1][k + 500 * m]);
      Serial.print(",");
      Serial.println(data[0][k + 500 * m]);
      dataFile.print(k + 1 + 500 * m);
      dataFile.print(",");
      //dataFile.print(millis() - t0);
      dataFile.print(data [1][k + 500 * m]);
      dataFile.print(",");
      dataFile.println(data[0][k + 500 * m]);
    }
    dataFile.close();
  }
  digitalWrite(9, HIGH);
  digitalWriteFast(7, LOW);
}

void ReadAnalog() {//2000msごとに起動される
  amari = blinkCount % 500;
  Z = analogRead(A0);
  t1 = millis() - t0;
  data [0] [blinkCount] = Z;
  data [1] [blinkCount] = t1;
  blinkCount++;
  
  if (amari == 0 ) {
    digitalWriteFast(9, HIGH);
    Serial.println(blinkCount);
  }
  else {
    digitalWriteFast(9, LOW);
  }
  if (blinkCount == 0) {
    starttime=millis();
  }
  if (blinkCount >= 10000) {
    finishtime=millis();
    myTimer.end();
    Serial.print("Finished\t");
    Serial.println(finishtime-starttime);

    logging();
  }
}

int i = 0;

/*void EPM() {
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
*/

void loop() {
  delay(1000000);
}
