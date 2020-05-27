//2019_09 write
#include <SPI.h>
#include "DW1000Ranging.h"

//i2c
#include <Wire.h>
int SLAVE_ADDRESS = 0x04;   //I2Cのアドレス『0x04』
char cmd;
byte mes[2] = {0, 0};
byte num[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// connection pins
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
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance

  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY);

  //I2C
  Wire.begin(SLAVE_ADDRESS);

  //I2Cでリクエスト受信したときに呼び出す関数を登録する
  Wire.onRequest(RequestMassage);
}

void loop() {
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
    str_out = String(d0_true) + "," + String(d1_true) + "," + String(d2_true) + "," + String(d3_true);
    //Serial.println(str_out);
    distance[0] = 0;
    distance[1] = 0;
    distance[2] = 0;
    distance[3] = 0;
    num[0] = d0_true & 0xff;
    num[1] =  (d0_true >> 8) & 0xff;
    num[2] = d1_true & 0xff;
    num[3] =  (d1_true >> 8) & 0xff;
    num[4] = d2_true & 0xff;
    num[5] =  (d2_true >> 8) & 0xff;
    num[6] = d3_true & 0xff;
    num[7] =  (d3_true >> 8) & 0xff;
  }
}

void newRange() {
  address1 = DW1000Ranging.getDistantDevice()->getShortAddress();
  range1 = DW1000Ranging.getDistantDevice()->getRange();

  int t = millis();

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

void RequestMassage() {
  Wire.write(num, 8);
  //delay(30);
  delay(100);
}

