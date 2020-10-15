//#define HWSERIAL Serial1
String recv_data = String(0); // 受信データ

#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L1X.h>
VL53L1X rangeSensor;
//#define MEDIUM_RANGE
//#define LONG_RANGE
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
delay(1);
  // Initialize flow sensor
  if (!flow.begin()) {
    Serial.println("Initialization of the flow sensor failed");
    while (1) { }
  }
  

  // Initialize range sensor
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  rangeSensor.init();
  rangeSensor.setTimeout(500);
  rangeSensor.setDistanceMode(VL53L1X::Medium);
  rangeSensor.setMeasurementTimingBudget(33000);
//            rangeSensor.setDistanceMode(VL53L1X::Long);//MODE_LONG
//            rangeSensor.setMeasurementTimingBudget(50000);//MODE_LONG
  rangeSensor.startContinuous(10);
}

void loop() {
  t1 = millis();
  t2 = 0;
  elapsed = 0;
  flow.readMotionCount(&deltaX, &deltaY);
//      float range = rangeSensor.readRangeSingleMillimeters();
  float range = rangeSensor.read();
  if (rangeSensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  
  if (range > 0 && 3000 > range ) {
    distance = range;
  } else {
    distance = range_b;
  }
  range_b = distance;

  deltaX = deltaX * distance * 0.0651 * 0.76772;//2*tan(fov/2)
  deltaY = deltaY * distance * 0.0651 * 0.76772;
  deltaX_sum = deltaX_sum + deltaX * update_rate * 0.001;
  deltaY_sum = deltaY_sum + deltaY * update_rate * 0.001;

  str_out = String(distance) + "," + String(deltaX) + "," + String(deltaY) + "," + String(deltaX_sum) + "," + String(deltaY_sum);
  //Serial.println(str_out);

//  while (elapsed < update_rate) {
//    elapsed = millis() - t1;
//  }

  if (Serial1.available() > 0) {                 
    //recv_data = HWSERIAL.readStringUntil('\n');
    recv_data = Serial1.readStringUntil(';');
    //Serial.println(recv_data);
    //delay(1000);
      //str_out = str_out + ',' + recv_data;
  }
//  else{
//    str_out = str_out + ",0,0,0,0";
//  }

  str_out = str_out + ',' + recv_data;
  Serial.println("distance\tdeltaX\tdeltaY\tdeltaX_sum\tdeltaY_sum\trecv_data");
  Serial.print(distance);Serial.print("\t\t");Serial.print(deltaX);Serial.print("\t");Serial.print(deltaY);Serial.print("\t");
  Serial.print(deltaX_sum);Serial.print("\t\t");Serial.print(deltaY_sum);Serial.print("\t\t");
  Serial.print(recv_data);Serial.print("\n");
  //Serial.println(str_out);
  Serial3.println(str_out);
  
 

///*------------LoopTime確認------------*/
//  //Serial.println(incomingByte);
//  incomingByte++;
//  if(incomingByte==200){
//    t2 = millis();
//    Serial.println(t2);
//    while(1);
//  }
///*-----------------------------------*/
}
