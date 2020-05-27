//UWB
#include <SPI.h>
#include "DW1000Ranging.h"

#include <MsTimer2.h>

//opt
#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>

//opt
VL53L0X rangeSensor;
#define LONG_RANGE
Bitcraze_PMW3901 flow(8);

//opt
float deltaX_sum = 0;
float deltaY_sum = 0;
float deltaX_ = 0;
float deltaY_ = 0;

int t1, elapsed;
int update_rate = 42; //msec
int range_b = 0;
int distance_o = 0;

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
//const uint8_t PIN_SS = SS; // spi select pin
const uint8_t PIN_SS = 7; // spi select pin

int anchor1 = 6018;
int anchor2 = 6274;
int anchor3 = 5762;
int anchor4 = 6530;

int address1 = 0;
int distance[4] = {0, 0, 0, 0};
double range1 = 0;
String str_out;


void setup() {
  Serial.begin(115200);
  delay(1000);
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY);

  // Initialize flow sensor
  if (!flow.begin()) {
    Serial.println("Initialization of the flow sensor failed");
    while (1) { }
  }

  // Initialize range sensor
  Wire.begin();
  rangeSensor.init();
  rangeSensor.setTimeout(500);

  MsTimer2::set(50, opt);     // 500ms毎にflash( )割込み関数を呼び出す様に設定
  MsTimer2::start();             // タイマー割り込み開始
}

int16_t deltaX, deltaY;

void loop() {
  t1 = millis();
  elapsed = 0;
  //DW1000Ranging.loop();
  //opt();
  //flow.readMotionCount(&deltaX, &deltaY);
  float range = rangeSensor.readRangeSingleMillimeters();

  if (range > 0 && 2000 > range ) {
    distance_o = range;
  } else {
    distance_o = range_b;
  }
  range_b = distance_o;

  deltaX = deltaX * distance_o * 0.0651 * 0.76772;
  deltaY = deltaY * distance_o * 0.0651 * 0.76772;
  deltaX_sum = deltaX_sum + deltaX * update_rate * 0.001;
  deltaY_sum = deltaY_sum + deltaY * update_rate * 0.001;

  //if (distance[0] > 0 && distance[1] > 0 && distance[2] > 0 && distance[3] > 0) {
    str_out = String(distance[0]) + "," + String(distance[1]) + "," + String(distance[2]) + "," + String(distance[3]) + "," +
              String(distance_o) + "," + String(deltaX) + "," + String(deltaY) + "," + String(deltaX_sum) + "," + String(deltaY_sum);

    Serial.println(str_out);
//    distance[0] = 0;
//    distance[1] = 0;
//    distance[2] = 0;
//    distance[3] = 0;
  //}

  //  while (elapsed < update_rate) {
  //    elapsed = millis() - t1;
  //  }


  //  Serial.println("loop!");
  //  delay(50);
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

void opt() {
  //Serial.println("opt");
  int time_b = millis();
  flow.readMotionCount(&deltaX, &deltaY);
  float range = rangeSensor.readRangeSingleMillimeters();

  if (range > 0 && 2000 > range ) {
    distance_o = range;
  } else {
    distance_o = range_b;
  }
  range_b = distance_o;

  deltaX = deltaX * distance_o * 0.0651 * 0.76772;
  deltaY = deltaY * distance_o * 0.0651 * 0.76772;
  deltaX_sum = deltaX_sum + deltaX * update_rate * 0.001;
  deltaY_sum = deltaY_sum + deltaY * update_rate * 0.001;
  //  int time_ela = millis() - time_b;
  //  str_out = String(time_ela) + "," + String(distance) + "," + String(deltaX) + "," + String(deltaY) + "," + String(deltaX_sum) + "," + String(deltaY_sum);
  //  Serial.println(str_out);

  //if (distance[0] > 0 && distance[1] > 0 && distance[2] > 0 && distance[3] > 0) {
  str_out = String(distance[0]) + "," + String(distance[1]) + "," + String(distance[2]) + "," + String(distance[3]) + "," +
            String(distance_o) + "," + String(deltaX) + "," + String(deltaY) + "," + String(deltaX_sum) + "," + String(deltaY_sum);

  Serial.println(str_out);
  //    distance[0] = 0;
  //    distance[1] = 0;
  //    distance[2] = 0;
  //    distance[3] = 0;
  //}
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

