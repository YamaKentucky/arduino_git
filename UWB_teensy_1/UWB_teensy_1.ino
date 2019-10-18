#include <SPI.h>
#include "DW1000Ranging.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

int anchor1 = 12336;
int anchor2 = 12592;
int anchor3 = 12848;
int anchor4 = 13104;

int address1 = 0;
int address2 = 0;
int address3 = 0;

double range1 = 0;
int distance[4] = {0,0,0,0};
String str_out;

int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;

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
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

void loop() {
  DW1000Ranging.loop();
  if (distance[0]!=0 && distance[1]!=0 && distance[2]!=0 && distance[3]!=0){
    str_out = String(distance[0]) + "," + String(distance[1]) + "," + String(distance[2])+ "," + String(distance[3]);
    Serial.println(str_out);

    incomingByte = Serial.read();

    if (incomingByte == 'A'){

      digitalWrite(5,HIGH);
    }
    distance[0] = 0;
    distance[1] = 0;
    distance[2] = 0;
    distance[3] = 0;
    
    //delay(100);
   
  }
  
}

void newRange() {
  //Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  //Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  //Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
  address1 = DW1000Ranging.getDistantDevice()->getShortAddress();
  range1 = DW1000Ranging.getDistantDevice()->getRange();
  
  if (address1 == anchor1){
    distance[0] = range1 * 100 - 33*(4-a1);
  }
  if (address1 == anchor2){
    distance[1] = range1 * 100 - 33*(4-a2);
  }
  if (address1 == anchor3){
    distance[2] = range1 * 100 - 33*(4-a3);
  }
  if (address1 == anchor4){
    distance[3] = range1 * 100 - 33*(4-a4);
  }
  delay(10);
  
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  address2 = device->getShortAddress();
  Serial.println(address2);
  
  if (a1+a2+a3+a4 == 0){
    big_num = 0;
  }else{
    if(a1>a2 & a1>a3 & a1>a4){
      big_num = a1;
    }
    if(a2>a1 & a2>a3 & a2>a4){
      big_num = a2;
    }
    if(a3>a1 & a3>a2 & a3>a4){
      big_num = a3;
    }
    if(a4>a1 & a4>a2 & a4>a3){
      big_num = a4;
    }
  }
  if (address2 == anchor1){
    a1 = big_num+1;
  }
  if (address2 == anchor2){
    a2 = big_num+1;
  }
  if (address2 == anchor3){
    a3 = big_num+1;
  }
  if (address2 == anchor4){
    a4 = big_num+1;
  }
  Serial.print(a1);
  Serial.print(a2);
  Serial.print(a3);
  Serial.println(a4);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  address3 = device->getShortAddress();
  Serial.println(address3);
  
  if (address3 == anchor1){
    if (a2>a1){
      a2 = a2 - 1;
    }
    if (a3>a1){
      a3 = a3 - 1;
    }
    if (a4>a1){
      a4 = a4 - 1;
    }
    a1 = 0;
  }
  if (address3 == anchor2){
    if (a1>a2){
      a1 = a1 - 1;
    }
    if (a3>a2){
      a3 = a3 - 1;
    }
    if (a4>a2){
      a4 = a4 - 1;
    }
    a2 = 0;
  }
  if (address3 == anchor3){
    if (a1>a3){
      a1 = a1 - 1;
    }
    if (a2>a3){
      a2 = a2 - 1;
    }
    if (a4>a3){
      a4 = a4 - 1;
    }
    a3 = 0;
  }
  if (address3 == anchor4){
    if (a1>a4){
      a1 = a1 - 1;
    }
    if (a2>a4){
      a2 = a2 - 1;
    }
    if (a3>a4){
      a3 = a3 - 1;
    }
    a4 = 0;
  }
  Serial.print(a1);
  Serial.print(a2);
  Serial.print(a3);
  Serial.println(a4);
  
}

