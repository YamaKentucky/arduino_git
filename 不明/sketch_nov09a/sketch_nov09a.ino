
#include <FlexiTimer2.h>
#include <TimeLib.h>
#include <SD.h>
#define FINISH  20000
         
long unsigned int count1 = 0;
const int chipSelect = BUILTIN_SDCARD;
File dataFile;

void setup() {
  pinMode(9, OUTPUT);
  setSyncProvider(getTeensy3Time);
  Serial.begin(115200);
  if (timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
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
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  FlexiTimer2::set(1, 1 / 1000, flash); // INTERVALms毎にflash()割込み関数を呼び出す
  setTime(0, 0, 0, 24, 7, 2017);
  Teensy3Clock.set(now());
  FlexiTimer2::start();               // タイマー割り込み開始
}

void flash() {
  // ファイルにカウンタとAD変換値を書き込む
  count1++;
  dataFile.print(hour());       dataFile.print(":");
  dataFile.print(minute());      dataFile.print(":");
  dataFile.print(second());
  dataFile.print(",");

  int value = analogRead(1);
  dataFile.println(value);

  Serial.println(value);
}

void loop() {
  if (count1 > FINISH) { // カウンタが終了値になったら
    FlexiTimer2::stop();      // タイマー割り込み終了
    dataFile.close();      // ファイルを閉じる
    Serial.println(F("Finished!!"));
    while (1);             // ストップ
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}


