#include<SD.h>
#include <TimeLib.h>
const int chipSelect = BUILTIN_SDCARD;
File dataFile;

IntervalTimer myTimer;
int Z;//accel
volatile int sw = LOW;
volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 20;
volatile int amari = 0;

void setup() {
  analogReadResolution(16);//kaizoudo
  pinMode(9, OUTPUT); //LED

  //myTimer.begin(ReadAnalog, 2000);  // 500 Hz
  attachInterrupt(0, keisoku, RISING);
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
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  digitalWriteFast(9, HIGH);
}

int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

void keisoku() {
  time_now = millis(); //現在の割り込み時刻を取得
  if ( time_now - time_prev > time_chat) {
    if ( sw == LOW )
      myTimer.begin(ReadAnalog, 2000);  // 500 Hz
    sw = !sw; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev = time_now; //現在の割り込み時刻を前回の割り込み時刻へコピー
}

/*void keisoku() {
  myTimer.begin(ReadAnalog, 4000);  // 250 Hz
  }*/

void ReadAnalog() {
  if (dataFile) {
    Z = analogRead(A0);
    blinkCount = blinkCount + 1;  // increase when get
    dataFile.print(blinkCount);
    dataFile.print(",");
    dataFile.println(Z);
  }
  amari = blinkCount % 500;
  if (blinkCount >= 15000) {
    dataFile.close();
    myTimer.end();
    Serial.print("Finished");
  }
  if (amari == 0 ) {
    digitalWriteFast(9, HIGH);
  }
  else {
    digitalWriteFast(9, LOW);
  }
}

void loop() {
  int t = millis();
  unsigned long blinkCopy;  // holds a copy of the blinkCount

  noInterrupts();
  blinkCopy = blinkCount;
  interrupts();

  Serial.print("blinkCount = ");
  Serial.print(blinkCopy);
  Serial.print(",accel=");
  Serial.println(Z);
  delay(1000 - millis() + t);

}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}
