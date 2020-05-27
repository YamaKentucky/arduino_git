volatile const int Hz = 1000, Byou = 20;
volatile float zA;
volatile int i, k;
#include <TimeLib.h>
#include <SD.h>
const int chipSelect = BUILTIN_SDCARD;

void setup() {
  analogReadResolution(16);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  attachInterrupt(0, keisoku, RISING);

  setSyncProvider(getTeensy3Time);
  Serial.begin(115200);
  if (timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
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
  delay(1000);
  digitalWrite(9, LOW);
  delay(1000);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void keisoku() {
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  digitalWrite(9, LOW);

  if (dataFile) {
    setTime(0, 0, 0, 24, 7, 2017);
    Teensy3Clock.set(now());
    for (i = 0; i < Byou; i++) {
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
  else {
    Serial.println(F("error opening datalog.txt"));
  }
  Serial.println("Finisfed");
}

