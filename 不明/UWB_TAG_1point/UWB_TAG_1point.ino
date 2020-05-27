#include <SPI.h>
#include "DW1000Ranging.h"

int t1,T;
// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

//int anchor1 = 12336;
int anchor1 = 6530;
//int anchor1 = 12336;
//int anchor2 = 12592;
//int anchor3 = 12848;
//int anchor4 = 13104;

int address1 = 0;
int address2 = 0;
int address3 = 0;

double range1 = 0;
int distance = 0;
String str_out;

int a1 = 0;
//int a2 = 0;
//int a3 = 0;
//int a4 = 0;

int big_num = 0;

int incomingByte = 0;

void setup() {
  pinMode(5,OUTPUT);
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
  //DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_SHORTDATA_FAST_ACCURACY);
}

void loop() {
  t1 = millis();
  DW1000Ranging.loop();
  if (distance!=0){
    str_out = String(distance);
    Serial.print(str_out);
    int t = millis();
    Serial.print(",");
    Serial.println(t);
    

    incomingByte = Serial.read();

    if (incomingByte == 'A'){

      digitalWrite(5,HIGH);
    }
    distance = 0;
    
    //delay(100);
   
  }
//  T = millis() - t1;
//  Serial.print(",");
//  Serial.println(T);
}

void newRange() {
  //Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  //Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  //Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
  address1 = DW1000Ranging.getDistantDevice()->getShortAddress();
  range1 = DW1000Ranging.getDistantDevice()->getRange();
  
  if (address1 == anchor1){
    distance = range1 * 100 - 33*(4-a1);
  }
  delay(10);
  
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  address2 = device->getShortAddress();
  Serial.println(address2);
  
  if (a1 == 0){
    big_num = 0;
  }
  
  if (address2 == anchor1){
    a1 = big_num+1;
  }
  Serial.println(a1);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  address3 = device->getShortAddress();
  Serial.println(address3);
  
  if (address3 == anchor1){
    a1 = 0;
  }
  
  Serial.println(a1);
  
}

