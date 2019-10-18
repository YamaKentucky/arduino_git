volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 30;
volatile int sw = LOW;

#include <TimeLib.h>
#include <SD.h>

const int chipSelect = BUILTIN_SDCARD;


void setup() {
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  attachInterrupt(0, keisoku, RISING);

  setSyncProvider(getTeensy3Time);
  Serial.begin(115200);
  //while (!Serial);  // Wait for Arduino Serial Monitor to open
  //delay(100);
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
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(9, LOW);
  delay(500);
}

void keisoku() {
  analogReadResolution(16);
  float ms2 = 9.80665;
  float x , y , z;
  x = y = z = 0 ;
  int x0 , y0 , z0 ; // 0Gの数値を入れる
  int x1 , y1 , z1 ; // 1Gの数値から0Gの数値を引いた数値を入れる
  x0 = 32866 ; y0 = 32904 ; z0 = 32734 ;
  x1 = 13038 ; y1 = 12990 ; z1 = 13016 ;
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  digitalWrite(9, LOW);
  setTime(16, 56, 50, 24, 7, 2017);
  time_now = millis(); //現在の割り込み時刻を取得
  if ( time_now - time_prev > time_chat) {
    if (dataFile) {
      if ( sw == LOW ) {
        for (int i = 0; i < 20; i++) {
          if ((i % 2) == 0) {
            digitalWrite(10, HIGH);
          }
          else {
            digitalWrite(10, LOW);
          }

          for (int k = 0; k < 200; k++) {
            unsigned long t = micros();
            //x = analogRead(0);
            //y = analogRead(1);
            z = analogRead(2);
            // x = (x  - x0) / x1 ;
            //y = (y  - y0) / y1 ;
            z = (z  - z0) / z1 ;
            dataFile.print(hour());       dataFile.print(":");
            dataFile.print(minute());      dataFile.print(":");
            dataFile.print(second());
            dataFile.print(",");
            //digitalClockDisplay();
            //dataFile.print(x * ms2, 4); dataFile.print(",");
            //dataFile.print(y * ms2, 4); dataFile.print(",");
            dataFile.println(z * ms2, 4);
            Serial.println(micros() - t);
            delayMicroseconds(5000 - micros() + t);
          }

        }
        dataFile.close();
      }
      sw = !sw;
    }
    else {
      Serial.println(F("error opening datalog.txt"));
    }

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




