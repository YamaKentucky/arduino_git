volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 30;
volatile int sw = LOW;
const int Hz = 2000;
const int Byou = 20;

#include <TimeLib.h>
#include <SD.h>

const int chipSelect = BUILTIN_SDCARD;


void setup() {
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

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
  if (SD.exists("datalog.csv")) {
    SD.remove("datalog.csv");
    Serial.println(F("File exist! Remove File."));
  }
}
//void printDigits(int digits) {
// utility function for digital clock display: prints preceding colon and leading 0
//  dataFile.print(":");
// if (digits < 10)
// dataFile.print('0');
// dataFile.print(digits);
//}

void loop() {
  float x , y , zA, zB;
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    setTime(0, 0, 0, 24, 7, 2017);
    Teensy3Clock.set(now());
    for (int i = 0; i < Byou; i++) {
      analogReadResolution(16);
      dataFile.print(hour());       dataFile.print(":");
      dataFile.print(minute());      dataFile.print(":");
      dataFile.print(second());
      dataFile.print(",");
      /*if ((i % 2) == 0) {
        digitalWrite(10, HIGH);
        }
        else {
        digitalWrite(10, LOW);
        }*/
      for (int k = 0; k < Hz; k++) {
        unsigned long t = micros();
        //x = analogRead(0);
        //y = analogRead(1);
        zA = analogRead(1);
        //zB = analogRead(2);
        //digitalClockDisplay();
        dataFile.print(" "); dataFile.print(",");
        dataFile.println(zA);
        //dataFile.print(",");
        //dataFile.println(zB);
        unsigned long D =   micros() - t;
        Serial.println(D);
        delayMicroseconds(469) ;
      }

    }
    dataFile.close();

  }
  Serial.println("Finisfed");
  digitalWrite(10, HIGH);
  delay(500000);
}




time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}




