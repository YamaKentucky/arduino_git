#include <Wire.h>
#include "PX4Flow.h"

PX4Flow sensor = PX4Flow(); 

void setup()
{
  Wire.begin();       
  Serial.begin(115200);  
}

void loop()
{
  sensor.update();
  
  Serial.print("#");
  Serial.print(sensor.vx());Serial.print(",");
  Serial.print(sensor.vy());Serial.print(",");
  Serial.println(sensor.altitude());

  delay(100);
}
