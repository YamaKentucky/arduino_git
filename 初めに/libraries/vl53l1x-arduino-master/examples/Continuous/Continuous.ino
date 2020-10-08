/*
This example shows how to take simple range measurements with the VL53L1X. The
range readings are in units of mm.
*/

#include <Wire.h>
#include <VL53L1X.h>

VL53L1X rangeSensor;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  rangeSensor.setTimeout(500);
  if (!rangeSensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  rangeSensor.setDistanceMode(VL53L1X::Long);
  rangeSensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  rangeSensor.startContinuous(50);
}

void loop()
{
  Serial.print(rangeSensor.read());
  if (rangeSensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
}
