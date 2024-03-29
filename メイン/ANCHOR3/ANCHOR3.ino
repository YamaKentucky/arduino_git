/**
1:左手前
2:左奥
3:右奥
4:右手前
  2 ------- 3
(3,2.5)  (3,-2.5)
  |   5m    |
  |6m       |    
  |         | 
  1 ------- 4
(-3,2.5) (-3,-2.5)
 */
#include <SPI.h>
#include "DW1000Ranginghighspeed.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

void setup() {
  Serial.begin(115200);
  pinMode(27,OUTPUT);
  pinMode(28,OUTPUT);
//  pinMode(28,OUTPUT);
//  digitalWrite(28,HIGH);
  delay(1000);
  
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachBlinkDevice(newBlink);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as an anchor
  /*MODE_LONGDATA_FAST_ACCURACY
   * MODE_SHORTDATA_FAST_ACCURACY
   * MODE_LONGDATA_RANGE_ACCURACY
  */
  DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY,false);//##Anchor1:6018
//  DW1000Ranging.startAsAnchor("82:18:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY,false);//##Anchor2:6274
//  DW1000Ranging.startAsAnchor("82:16:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY,false);//##Anchor3:5762
//  DW1000Ranging.startAsAnchor("82:19:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY,false);//##Anchor4:6530
  
}

void loop() {
  DW1000Ranging.loop();
}

void newRange() {
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
}

void newBlink(DW1000Device* device) {
  digitalWrite(27,HIGH);
  digitalWrite(28,HIGH);
  
  Serial.print("blink; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
 
}

void inactiveDevice(DW1000Device* device) {
  digitalWrite(27,LOW);
  digitalWrite(28,LOW);
  
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}
