//#define HWSERIAL Serial1
String recv_data = String(0); // 受信データ

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
int16_t deltaX, deltaY;

int t1, t2, elapsed;
int update_rate = 39; //msec
int altitude = 780; //mm
int lesolution = 30; //pixel 30*30
int fov = 42; //degree
int scalar = 15.8; //no unit
int range_b = 0;
int distance = 0;
String str_out;
int incomingByte = 0;

void setup() {
  Serial1.begin(115200); //from arduino with UWB
  Serial3.begin(115200); //to raspberry pi
  Serial.begin(115200);  //to debug PC

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

void loop() {
  t1 = millis();
  t2 = 0;
  elapsed = 0;
  flow.readMotionCount(&deltaX, &deltaY);
  float range = rangeSensor.readRangeSingleMillimeters();

  if (range > 0 && 2000 > range ) {
    distance = range;
  } else {
    distance = range_b;
  }
  range_b = distance;

  deltaX = deltaX * distance * 0.0651 * 0.76772;
  deltaY = deltaY * distance * 0.0651 * 0.76772;
  deltaX_sum = deltaX_sum + deltaX * update_rate * 0.001;
  deltaY_sum = deltaY_sum + deltaY * update_rate * 0.001;

  str_out = String(distance) + "," + String(deltaX) + "," + String(deltaY) + "," + String(deltaX_sum) + "," + String(deltaY_sum);
  //Serial.println(str_out);

  while (elapsed < update_rate) {
    elapsed = millis() - t1;
  }

  if (Serial1.available() > 0) {
    //recv_data = HWSERIAL.readStringUntil('\n');
    recv_data = Serial1.readStringUntil(';');
    //Serial.println(recv_data);
    //delay(1000);
  }
  str_out = str_out + ',' + recv_data;
  Serial.println(str_out);
  Serial3.println(str_out);
  t2 = millis() - t1;
  //Serial.println(t2);
  
  incomingByte = Serial3.read();
  if (incomingByte == 'A'){
    digitalWrite(5, HIGH)
  }
}
