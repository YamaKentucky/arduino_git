

/**
2021/04/06
UWBドローンのTeensy[OPT+tag]に書き込むプログラム
uart_uwb_optより改変
2つのl1x距離センサ，OPTセンサを使用するためのプログラム
UWBの接続が途絶えると更新が停止する問題を解決し，接続が途絶えると前の値をプロットし続ける．
#######################これはテスト用
*/

//#define HWSERIAL Serial1
String recv_data = String(0); // 受信データ

#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>
#include <VL53L1X.h>
VL53L1X sensor_up;
VL53L1X sensor_down;

#define SHUT_UP 5
#define SHUT_DOWN 6


//#define L0X//cs10
////#define L1X//cs9
//
//#ifdef L0X
//  VL53L0X rangeSensor;
//#else 
//  VL53L1X rangeSensor;
//#endif


//#define MEDIUM_RANGE
//#define LONG_RANGE
const int cspin=10;
Bitcraze_PMW3901 flow_up(cspin); //Pin select cs 10
Bitcraze_PMW3901 flow_down(9); //Pin select cs 9

float dX_sum_up = 0;
float dY_sum_up = 0;
float dX_sum_dwn = 0;
float dY_sum_dwn = 0;
float deltaX_ = 0;
float deltaY_ = 0;
int16_t deltaX_up, deltaY_up;
int16_t deltaX_down, deltaY_down;
float range_up;
float range_dwn;
int t1, t2, elapsed;
int update_rate = 39; //msec
int altitude = 780; //mm
int lesolution = 30; //pixel 30*30
int fov = 42; //degree
int scalar = 15.8; //no unit
int range_up_b = 0;//range_b 
int range_dwn_b = 0;
int distance_up = 0;
int distance_dwn = 0;

String str_out;
int incomingByte = 0;

void setup() {
  Serial1.begin(115200); //from arduino with UWB
  Serial3.begin(115200); //to raspberry pi
  Serial.begin(115200);  //to debug PC
  setup_sensor("flow"); // Initialize flow sensor

  pinMode(SHUT_UP, OUTPUT);
  pinMode(SHUT_DOWN, OUTPUT);
  digitalWrite(SHUT_UP, LOW);
  digitalWrite(SHUT_DOWN, LOW); 
  delay(100);
  setup_sensor("range"); // Initialize range sensor
  delay(100);
//  setup_sensor("flow"); // Initialize flow sensor
}

void setup_sensor(int mode){
  if (mode=="range"){
    Wire.begin();
    Wire.beginTransmission(0x29);
    Wire.setClock(400000); // use 400 kHz I2C
  }
}




void loop() {
  str_out="79,3,0,0.08,0.00,192,0,0,15.68,6.24,123,115,163,133";
////////////////////////////////////////////////////
    Serial.println("distance\tdeltaX\tdeltaY\tdeltaX_sum\tdeltaY_sum\trecv_data");
    Serial.println(str_out);
    Serial3.println(str_out);
    delay(50);

}
