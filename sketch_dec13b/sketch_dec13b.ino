volatile int  sw_E = LOW;
volatile int  sw_K = LOW;
volatile unsigned long time_prev_E = 0, time_now_E;
volatile unsigned long time_prev_K = 0, time_now_K;
unsigned long time_chat = 100;
volatile char inputchar = 0;
const int Hz = 1000;
const int Byou = 20;
volatile int i, k;
volatile float zA;

#include <TimeLib.h>
#include <SD.h>
const int chipSelect = BUILTIN_SDCARD;

void setup() {
  analogReadResolution(16);
  attachInterrupt(1, EPM, RISING);
  attachInterrupt(0, keisoku, RISING);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  setSyncProvider(getTeensy3Time);
  Serial.begin(115200);
  if (timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
  //setTime(16, 56, 50, 24, 7, 2017);
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
}

void loop() {
  Serial.println("Standingby");
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(9, LOW);
  delay(500);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}


void keisoku() {
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  digitalWrite(9, LOW);
  time_now_K = millis(); //現在の割り込み時刻を取得
  if ( time_now_K - time_prev_K > time_chat) {
    if (dataFile) {
      if ( sw_K == LOW ) {
        setTime(0, 0, 0, 24, 7, 2017);
        Teensy3Clock.set(now());
        for ( i = 0; i < Byou; i++) {

          dataFile.print(hour());       dataFile.print(":");
          dataFile.print(minute());      dataFile.print(":");
          dataFile.print(second());
          dataFile.print(",");
          if ((i % 2) == 0) {
            digitalWrite(10, HIGH);
          }
          else {
            digitalWrite(10, LOW);
          }
          for (k = 0; k < Hz; k++) {
            unsigned long t = millis();
            zA = analogRead(1);
            dataFile.print(" "); dataFile.print(",");
            dataFile.println(zA);
            Serial.println(millis() - t);
            delay(1.00 - millis() + t);
          }
        }
        dataFile.close();
      }
      sw_K = !sw_K;
    }
    else {
      Serial.println(F("error opening datalog.txt"));
    }

  }

  time_prev_K = time_now_K; //現在の割り込み時刻を前回の割り込み時刻へコピー
  Serial.println("Finisfed");
}



void EPM() {
  time_now_E = millis(); //現在の割り込み時刻を取得
  if ( time_now_E - time_prev_E > time_chat) {
    if ( sw_E == LOW ) //前回の割り込みから20[ms]以上経過かつスイッチの状態がLowならば、LED消点灯を切り替え
      switch (inputchar) {
        case 0:
          digitalWrite(4, HIGH); //LED表示
          digitalWrite(5, LOW);

          Serial.print("EPM ON\n");//EPMをONにする
          digitalWrite(3, HIGH);
          delay(2000);
          digitalWrite(3, LOW);
          inputchar = 1;
          break;

        case 1:
          digitalWrite(4, LOW); //LED表示
          digitalWrite(5, HIGH);

          Serial.print("EPM OFF\n");//EPMをOFFにする
          digitalWrite(2, HIGH);
          delay(500);
          digitalWrite(3, HIGH);
          delay(2000);
          digitalWrite(3, LOW);
          delay(500);
          digitalWrite(2, LOW);
          inputchar = 0;
          break;
      }
    sw_E = !sw_E; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev_E = time_now_E; //現在の割り込み時刻を前回の割り込み時刻へコピー
}
