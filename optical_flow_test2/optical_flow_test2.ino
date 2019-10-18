//2019_09 write
#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>


VL53L0X rangeSensor;
#define LONG_RANGE

Bitcraze_PMW3901 flow(10); //Pin select (CS)

float deltaX_sum = 0;
float deltaY_sum = 0;
float deltaX_ = 0;
float deltaY_ = 0;

int t1, t2, elapsed;
int update_rate = 42; //msec
int altitude = 780; //mm
int lesolution = 30; //pixel 30*30
int fov = 42; //degree
int scalar = 15.8; //no unit
int range_b = 0;
int distance = 0;
String str_out;

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);

  // Initialize flow sensor
  if (!flow.begin()) {
    Serial.println("Initialization of the flow sensor failed");
    while (1) { }
  }

  // Initialize range sensor
  Wire.begin();
  rangeSensor.init();
  rangeSensor.setTimeout(500);
}

int16_t deltaX, deltaY;

void loop() {
  t1 = millis();
  elapsed = 0;

  flow.readMotionCount(&deltaX, &deltaY);
  float range = rangeSensor.readRangeSingleMillimeters();

  //  Serial.print(", Range: ");

  if (range > 0 && 2000 > range ) {
    distance = range;
  } else {
    distance = range_b;
  }
  range_b = distance;

  //  deltaX_sum = deltaX_sum + deltaX * update_rate;
  //  deltaY_sum = deltaY_sum + deltaY * update_rate;


  //deltaX = deltaX * distance  * 0.76772;
  //deltaY = deltaY * distance  * 0.76772;
  deltaX = deltaX * distance * 0.0651 * 0.76772;
  deltaY = deltaY * distance * 0.0651 * 0.76772;
  deltaX_sum = deltaX_sum + deltaX * update_rate * 0.001;
  deltaY_sum = deltaY_sum + deltaY * update_rate * 0.001;


  //  Serial.print(distance);Serial.print(",");
  //  Serial.print(deltaX);
  //  Serial.print(",");
  //  Serial.print(deltaY);
  //  Serial.print(",");
  //  Serial.print(deltaX_sum);
  //  Serial.print(",");
  //  Serial.print(deltaY_sum);

  str_out = String(distance) + "," + String(deltaX) + "," + String(deltaY) + "," + String(deltaX_sum) + "," + String(deltaY_sum);
  Serial.println(str_out);

  while (elapsed < update_rate) {
    elapsed = millis() - t1;
  }

  t2 = millis() - t1;
  //Serial.print(t2);
  //Serial.print("\n");
}
