#include <TimeLib.h>
unsigned long prevtime;


void setup() {
  setSyncProvider(getTeensy3Time);
  Serial.begin(115200);
  //while (!Serial);  // Wait for Arduino Serial Monitor to open
  //delay(100);
  if (timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
  setTime(00, 00, 00, 5, 7, 2017);
  Teensy3Clock.set(now());
  prevtime = millis();

}

void loop() {
  unsigned long timenow = millis() - prevtime;
  int s = timenow / 1000;
  int m = (s / 60) % 60;
  int h = s / 3600;
  s = s % 60;


  Serial.print("RTCTIME="); Serial.print(hour());   printDigits(minute());  printDigits(second());
  Serial.print(",");
  Serial.print("CLOCKTIME="); Serial.print(h);    printDigits(m);     printDigits(s);
  Serial.println();
  delay(1000);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
