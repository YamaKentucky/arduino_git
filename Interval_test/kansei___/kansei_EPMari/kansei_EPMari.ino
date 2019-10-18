#include<SD.h>
const int chipSelect = BUILTIN_SDCARD;
File dataFile;

IntervalTimer myTimer;
int Z;//accel
volatile int sw = LOW;
volatile int  sw_E = LOW;
volatile unsigned long time_prev = 0, time_now;
volatile unsigned long time_prev_E = 0, time_now_E;
volatile char inputchar = 0;
unsigned long time_chat = 20;
const int num = 10000;

float data [num];
volatile unsigned long blinkCount = 0; // use volatile for shared variables
int amari;

void setup() {
  attachInterrupt(0, keisoku, RISING);
  attachInterrupt(1, EPM, RISING);

  analogReadResolution(16);//kaizoudo

  pinMode(3, OUTPUT);  //EPM
  pinMode(4, OUTPUT);  //EPM
  pinMode(9, OUTPUT);  //LED
  pinMode(10, OUTPUT); //LED
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

void keisoku() {
  time_now = millis(); //現在の割り込み時刻を取得
  if ( time_now - time_prev > time_chat) {
    if ( sw == LOW )
      delay(3000);
    digitalWriteFast(7, HIGH);  //douki_ON
    myTimer.begin(ReadAnalog, 2000);  // 500 Hz

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
      Serial.println(data[k + 500 * m]);
      dataFile.print(k + 1 + 500 * m);
      dataFile.print(",");
      dataFile.println(data[k + 500 * m]);
    }
    dataFile.close();
  }
  digitalWrite(9, HIGH);
  digitalWriteFast(7, LOW); 
}

void ReadAnalog() {
  amari = blinkCount % 500;
  Z = analogRead(A0);
  data [blinkCount] = Z;
  blinkCount++;

  if (amari == 0 ) {
    digitalWriteFast(9, HIGH);
  }
  else {
    digitalWriteFast(9, LOW);
  }
  if (blinkCount >= 10000) {
    myTimer.end();
    Serial.println("Finished");
    logging();
  }
}

int i = 0;

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
