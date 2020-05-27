/**

   @todo
    - move strings to flash (less RAM consumption)
    - fix deprecated convertation form string to char* startAsTag
    - give example description
*/
#include <SPI.h>
#include "DW1000Ranging.h"

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
double range1 = 0;
String str_out;


void setup() {
  Serial.begin(115200);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);

  //we start the module as a tag
  //DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_SHORTDATA_FAST_ACCURACY);
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY);
}

void loop() {
  DW1000Ranging.loop();
}

void newRange() {
  //Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  //Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  //Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
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

  if (distance[0] != 0 && distance[1] != 0 && distance[2] != 0 && distance[3] != 0) {
    Serial.print(t); Serial.print(",");
    str_out = String(distance[0]) + "," + String(distance[1]) + "," + String(distance[2]) + "," + String(distance[3]);
    Serial.println(str_out);
    distance[0] = 0;
    distance[1] = 0;
    distance[2] = 0;
    distance[3] = 0;
  }
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  //Serial.println(device->getShortAddress(), HEX);
  Serial.println(device->getShortAddress());
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  //Serial.println(device->getShortAddress(), HEX);
  Serial.println(device->getShortAddress());
}

