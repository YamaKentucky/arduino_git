///**
//2020/10/15
//UWBドローンのArduino[tag]に書き込むプログラム
//Tag6_kaiより改変
//UWBの接続が途絶えると更新が停止する問題を解決し，接続が途絶えると前の値をプロットし続ける．
//3.3V8MHzに変更してから書き込み
//*/
//
//
//#include <SPI.h>
//#include "DW1000Ranginghighspeed.h"
//
//// connection pins
//const uint8_t PIN_RST = 9; // reset pin
//const uint8_t PIN_IRQ = 2; // irq pin
//const uint8_t PIN_SS = SS; // spi select pin
//const int led=4;
//
//const int anchor1 = 6018;
//const int anchor2 = 6274;
//const int anchor3 = 5762;
//const int anchor4 = 6530;
//
//int address1 = 0;
//int distance[4] = {0, 0, 0, 0};
//int device_point[4] = {0, 0, 0, 0};
//int device_value;
//double range1 = 0;
//String str_out;
//const int threshold = 2000;
//int begin_device=-1;
//int d0_old = 0, d1_old = 0, d2_old = 0, d3_old = 0, d0_true = 0, d1_true = 0, d2_true = 0, d3_true = 0;
//int d0_fake=0,d1_fake=0,d2_fake=0,d3_fake=0;
//int i=0;
//void setup() {
//  Serial.begin(115200);
//  pinMode(led, OUTPUT);
//  delay(1000);
//  //init the configuration
//  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
//  //define the sketch as anchor. It will be great to dynamically change the type of module
//  DW1000Ranging.attachNewRange(newRange);
//  DW1000Ranging.attachNewDevice(newDevice);
//  DW1000Ranging.attachInactiveDevice(inactiveDevice);
//  //Enable the filter to smooth the distance
//  //DW1000Ranging.useRangeFilter(true);
//
//  //we start the module as a tag
//  //DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_SHORTDATA_FAST_ACCURACY);
//  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_FAST_ACCURACY);
////  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
//  Serial.print("0,0,0,0\n");
//
//}
//
//void loop() {
//DW1000Ranging.loop();
//
//
//  if (abs(d0_old - distance[0]) < threshold ) {
//    d0_true = distance[0];
//    d0_old = distance[0];
//  }
//  if (abs(d1_old - distance[1]) < threshold ) {
//    d1_true = distance[1];
//    d1_old = distance[1];
//  }
//
//  if (abs(d2_old - distance[2]) < threshold ) {
//    d2_true = distance[2];
//    d2_old = distance[2];
//  }
//
//  if (abs(d3_old - distance[3]) < threshold ) {
//    d3_true = distance[3];
//    d3_old = distance[3];
//  }
//  
//  if(device_point[0]==0){
//    d0_true=d0_fake;
//  }
//  if(device_point[1]==0){
//    d1_true=d1_fake;
//  }
//  if(device_point[2]==0){
//    d2_true=d2_fake;
//  }
//  if(device_point[3]==0){
//    d3_true=d3_fake;
//  }
////Serial.print(d0_true);Serial.print("\t");
////Serial.print(d1_true);Serial.print("\t");
////Serial.print(d2_true);Serial.print("\t");
////Serial.println(d3_true);
//
//
//if(device_value==-4||begin_device==1){
//  begin_device=1;
//  if (d0_true > 0 &&d1_true > 0 && d2_true > 0 && d3_true > 0) {
//   digitalWrite(led,HIGH);
//      str_out = String(d0_true) + "," + String(d1_true) + "," + String(d2_true) + "," + String(d3_true);
//      Serial.print(str_out + "\n");
//      //Serial.println(str_out + ";");//for debug
//      d0_fake = d0_true;
//      d1_fake = d1_true;
//      d2_fake = d2_true;
//      d3_fake = d3_true;
//      d0_old  = distance[0] ;
//      d1_old  = distance[1] ;
//      d2_old  = distance[2] ;
//      d3_old  = distance[3] ;
//      distance[0] = 0;
//      distance[1] = 0;
//      distance[2] = 0;
//      distance[3] = 0;
//      delay(10);
//            if(device_value==0){  /*-----*/
//                str_out = String(d0_true) + "," + String(d1_true) + "," + String(d2_true) + "," + String(d3_true);
//                Serial.print(str_out + "\n");
//                delay(100);
////              software_reset();   /*reset*/
//////              while(1);           /*-----*/
//            }
//    }else{    
//      digitalWrite(led,LOW);
//      }
//}
//}
////void software_reset() {
////  asm volatile ("  jmp 0");  
////} 
//void newRange() {
//  //Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
//  //Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
//  //Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
//  address1 = DW1000Ranging.getDistantDevice()->getShortAddress();
//  range1 = DW1000Ranging.getDistantDevice()->getRange();
//
//  int t = millis();
//  if (address1 == anchor1) {
//    distance[0] = range1 * 100 - 63;
//  }
//  if (address1 == anchor2) {
//    distance[1] = range1 * 100 - 63;
//  }
//  if (address1 == anchor3) {
//    distance[2] = range1 * 100 - 63;
//  }
//  if (address1 == anchor4) {
//    distance[3] = range1 * 100 - 63;
//  }
//}
//
//void newDevice(DW1000Device* device) {
////  Serial.print("\n");
//  Serial.print(" 1_device added_! ->->-> ");
//  //Serial.println(device->getShortAddress(), HEX);
//    int device_name=device->getShortAddress();
//      Serial.print(device_name);
//    if(device_name==anchor1){
//      Serial.print("anchor1");
//     device_point[0]=-1;
//    }else if(device_name==anchor2){
//      Serial.print("anchor2");
//       device_point[1]=-1;
//    }else if(device_name==anchor3){
//      Serial.print("anchor3");
//       device_point[2]=-1;
//    }else if(device_name==anchor4){
//      Serial.print("anchor4");
//       device_point[3]=-1;
//    }
//    device_value=device_point[0]+device_point[1]+device_point[2]+device_point[3];
//    Serial.print("---> \n");
//    Serial.print(device_point[0]);Serial.print(",");Serial.print(device_point[1]);Serial.print(",");
//    Serial.print(device_point[2]);Serial.print(",");Serial.print(device_point[3]);Serial.print("\n");
//  //Serial.println(device->getShortAddress());
//}
//
//void inactiveDevice(DW1000Device* device) {
////  Serial.print("\n");
//  Serial.print("delete inactive device: ->->-> ");
//  //Serial.println(device->getShortAddress(), HEX);
//  int device_name=device->getShortAddress();
//  Serial.print(device_name);
//    if(device_name==anchor1){
//      Serial.print("anchor1");
//      device_point[0]=0;
//    }else if(device_name==anchor2){
//      Serial.print("anchor2");
//      device_point[1]=0;
//    }else if(device_name==anchor3){
//      Serial.print("anchor3");
//      device_point[2]=0;
//    }else if(device_name==anchor4){
//      Serial.print("anchor4");
//      device_point[3]=0;
//    }
//    device_value=device_point[0]+device_point[1]+device_point[2]+device_point[3];
//    Serial.println("---> \n");
//    Serial.print(device_point[0]);Serial.print(",");Serial.print(device_point[1]);Serial.print(",");
//    Serial.print(device_point[2]);Serial.print(",");Serial.print(device_point[3]);Serial.print("\n");
////  Serial.println(device->getShortAddress());
//}




/**
2020/10/15
UWBドローンのArduino[tag]に書き込むプログラム
Tag6_kaiより改変
UWBの接続が途絶えると更新が停止する問題を解決し，接続が途絶えると前の値をプロットし続ける．
*/


#include <SPI.h>
#include "DW1000Ranginghighspeed.h"

// connection pins
//const uint8_t PIN_RST = 9; // reset pin
//const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_RST = 2; // reset pin
const uint8_t PIN_IRQ = 3; // irq pin 切削基盤の時はこちら
const uint8_t PIN_SS = SS; // spi select pin
const int led=4;

const int anchor1 = 6018;
const int anchor2 = 6274;
const int anchor3 = 5762;
const int anchor4 = 6530;

int address1 = 0;
int distance[4] = {0, 0, 0, 0};
int device_point[4] = {0, 0, 0, 0};
int device_value;
double range1 = 0;
String str_out;
const int threshold = 2000;
int begin_device=-1;
int d0_old = 0, d1_old = 0, d2_old = 0, d3_old = 0, d0_true = 0, d1_true = 0, d2_true = 0, d3_true = 0;
int d0_fake=0,d1_fake=0,d2_fake=0,d3_fake=0;
int i=0;
int flag=1;
void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
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
  //DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

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
  
  if(device_point[0]==0){
    d0_true=d0_fake;
  }
  if(device_point[1]==0){
    d1_true=d1_fake;
  }
  if(device_point[2]==0){
    d2_true=d2_fake;
  }
  if(device_point[3]==0){
    d3_true=d3_fake;
  }
//Serial.print(d0_true);Serial.print("\t");
//Serial.print(d1_true);Serial.print("\t");
//Serial.print(d2_true);Serial.print("\t");
//Serial.println(d3_true);


if(device_value==4||begin_device==1){
  begin_device=1;
  if (d0_true > 0 &&d1_true > 0 && d2_true > 0 && d3_true > 0) {
   digitalWrite(led,HIGH);
      str_out = String(d0_true) + "," + String(d1_true) + "," + String(d2_true) + "," + String(d3_true)+","+String(flag);
      Serial.print(str_out + "\n");
      //Serial.println(str_out + ";");//for debug
      d0_fake = d0_true;
      d1_fake = d1_true;
      d2_fake = d2_true;
      d3_fake = d3_true;
      d0_old  = distance[0] ;
      d1_old  = distance[1] ;
      d2_old  = distance[2] ;
      d3_old  = distance[3] ;
      distance[0] = 0;
      distance[1] = 0;
      distance[2] = 0;
      distance[3] = 0;
            if(device_value==0){  /*-----*/
//              software_reset();   /*reset*/
              while(1);           /*-----*/
            }
    }else{    
      digitalWrite(led,LOW);
      }
}
}
//void software_reset() {
//  asm volatile ("  jmp 0");  
//} 
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
}

void newDevice(DW1000Device* device) {
  flag=0;
  Serial.print(" 1 device added ! -> ");
  //Serial.println(device->getShortAddress(), HEX);
    int device_name=device->getShortAddress();
      Serial.print(device_name);
    if(device_name==anchor1){
      Serial.print("anchor1");
     device_point[0]=1;
    }else if(device_name==anchor2){
      Serial.print("anchor2");
       device_point[1]=1;
    }else if(device_name==anchor3){
      Serial.print("anchor3");
       device_point[2]=1;
    }else if(device_name==anchor4){
      Serial.print("anchor4");
       device_point[3]=1;
    }
    device_value=device_point[0]+device_point[1]+device_point[2]+device_point[3];
    Serial.print("---> ");
    Serial.print(device_point[0]);Serial.print(device_point[1]);
    Serial.print(device_point[2]);Serial.print(device_point[3]);Serial.println("");
  //Serial.println(device->getShortAddress());
}

void inactiveDevice(DW1000Device* device) {
  flag=1;
  Serial.print("delete inactive device: ");
  //Serial.println(device->getShortAddress(), HEX);
  int device_name=device->getShortAddress();
  Serial.print(device_name);
    if(device_name==anchor1){
      Serial.print("anchor1");
      device_point[0]=0;
    }else if(device_name==anchor2){
      Serial.print("anchor2");
      device_point[1]=0;
    }else if(device_name==anchor3){
      Serial.print("anchor3");
      device_point[2]=0;
    }else if(device_name==anchor4){
      Serial.print("anchor4");
      device_point[3]=0;
    }
    device_value=device_point[0]+device_point[1]+device_point[2]+device_point[3];
    Serial.print("---> ");
    Serial.print(device_point[0]);Serial.print(device_point[1]);
    Serial.print(device_point[2]);Serial.print(device_point[3]);Serial.println("");
//  Serial.println(device->getShortAddress());
}
