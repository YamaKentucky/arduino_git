volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 20;
volatile int sw = LOW;

#include <TimeLib.h>
#include <SD.h>

const int chipSelect = BUILTIN_SDCARD;


void setup() {

  attachInterrupt(0, keisoku, RISING);

  setSyncProvider(getTeensy3Time);
  Serial.begin(115200);
  while (!Serial);  // Wait for Arduino Serial Monitor to open
  delay(100);
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
}

//void printDigits(int digits) {
// utility function for digital clock display: prints preceding colon and leading 0
//  dataFile.print(":");
// if (digits < 10)
// dataFile.print('0');
// dataFile.print(digits);
//}

void loop() {
  Serial.println("Standingby");
  delay(1000);
}

void keisoku() {
  setTime(16, 56, 50, 24, 7, 2017);
  time_now = millis(); //現在の割り込み時刻を取得
  if ( time_now - time_prev > time_chat) {
    if ( sw == LOW )
      for (int i = 0; i < 10; i++) {
        File dataFile = SD.open("datalog.csv", FILE_WRITE);
        if (dataFile) {
          for (int k = 0; k < 200; k++) {
            int value = analogRead(0);
            dataFile.print(year());       dataFile.print("/");
            dataFile.print(month());     dataFile.print("/");
            dataFile.print(day());        dataFile.print(",");
            dataFile.print(hour());       dataFile.print(":");
            dataFile.print(minute());      dataFile.print(":");
            dataFile.print(second());
            dataFile.print(",");
            //digitalClockDisplay();
            dataFile.println(value);
            Serial.print(year());     Serial.print("/");
            Serial.print(month());    Serial.print("/");
            Serial.print(day());       Serial.print(",");
            Serial.print(hour());     Serial.print(":");
            Serial.print(minute());   Serial.print(":");
            Serial.print(second());
            Serial.print(",");
            Serial.println(value);
            delay(5);
          }
          dataFile.close();

        }
        else {
          Serial.println(F("error opening datalog.txt"));
        }
      }
    sw = !sw;
  }
  time_prev = time_now; //現在の割り込み時刻を前回の割り込み時刻へコピー

}

//void digitalClockDisplay() {
// digital clock display of the time
//Serial.print(year());     Serial.print("/");
//Serial.print(month());    Serial.print("/");
//Serial.print(day());       Serial.print(",");
//Serial.print(hour());     Serial.print(":");
//Serial.print(minute());   Serial.print(":");
//Serial.print(second());     Serial.print(":");      Serial.print(5 * k);
//Serial.print(",");
//}



time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}




