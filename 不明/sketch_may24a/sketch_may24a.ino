#include <CapacitiveSensor.h>


CapacitiveSensor cs_4_2=CapacitiveSensor(4,2);

void setup()
{
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);

}

void loop() {
  long cs=cs_4_2.capacitiveSensor(30);
  Serial.println(cs);
  delay(100);

}
