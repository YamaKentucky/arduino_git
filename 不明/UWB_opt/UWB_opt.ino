//opt
#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>


//UWB
#include <SPI.h>
#include "DW1000Ranging.h"

//opt
VL53L0X rangeSensor;
#define LONG_RANGE
Bitcraze_PMW3901 flow(8);

//opt
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

//UWB
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

int anchor1 = 6018;
int anchor2 = 6274;
int anchor3 = 5762;
int anchor4 = 6530;

int address1 = 0;
int distance[4] = {0, 0, 0, 0};
int distance_e[4] = {0, 0, 0, 0};
double range1 = 0;
String str_out;
int threshold = 2000;

int d0_old = 0, d1_old = 0, d2_old = 0, d3_old = 0, d0_true = 0, d1_true = 0, d2_true = 0, d3_true = 0;

void setup() {
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

  //Initialize UWB
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY);
}

int16_t deltaX, deltaY;

void loop() {
  t1 = millis();
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

  DW1000Ranging.loop();
  if (abs(d0_old - distance[0]) < threshold ) {
    d0_true = distance[0];
    d0_old = distance[0];
  }

  if (abs(d1_old - distance[1]) < threshold ) {
    d1_true = distance[1];
    d1_old = distance[1];
  }

  if (abs(d2_old - distance[2]) < threshold ) {
    d2_true = distance[2];
    d2_old = distance[2];
  }

  if (abs(d3_old - distance[3]) < threshold ) {
    d3_true = distance[3];
    d3_old = distance[3];
  }



  if (d0_true > 0 && d1_true > 0 && d2_true > 0 && d3_true > 0) {
    str_out = String(d0_true) + "," + String(d1_true) + "," + String(d2_true) + "," + String(d3_true) + "," +
              String(distance) + "," + String(deltaX) + "," + String(deltaY) + "," + String(deltaX_sum) + "," + String(deltaY_sum);
    Serial.println(str_out);
    distance[0] = 0;
    distance[1] = 0;
    distance[2] = 0;
    distance[3] = 0;
  }

  while (elapsed < update_rate) {
    elapsed = millis() - t1;
  }

  t2 = millis() - t1;

}

void newRange() {
  address1 = DW1000Ranging.getDistantDevice()->getShortAddress();
  range1 = DW1000Ranging.getDistantDevice()->getRange();

  //int t = millis();

  if (address1 == anchor1) {
    distance[0] = range1 * 100 - 63;
  }



  if (address1 == anchor2) {
    distance[1] = range1 * 100 - 63;
  }



  if (address1 == anchor3) {
    distance[2] = range1 * 100 - 63;
  }



  if (address1 == anchor4) {
    distance[3] = range1 * 100 - 63;
  }



}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress());
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress());
}

