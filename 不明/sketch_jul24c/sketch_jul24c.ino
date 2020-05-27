#include <TimeLib.h>
int year, month, day, hour, min, second;

void setup() {

    Serial.begin(9600);

    RTC::setDateTime(2012,8,2,11,59,30);                // 設定

}

void loop() {

    RTC::getDateTime(year,month,day,hour,min,second);   // 読み出し

    Serial.print(year);

    Serial.print(",");

    Serial.print(month);

    Serial.print(",");

    Serial.print(day);

    Serial.print(",");

    Serial.print(hour);

    Serial.print(",");

    Serial.print(min);

    Serial.print(",");

    Serial.println(second);

    delay(1000);

}
