

/**
2021/04/06
UWBドローンのTeensy[OPT+tag]に書き込むプログラム
uart_uwb_optより改変
2つのl1x距離センサ，OPTセンサを使用するためのプログラム
UWBの接続が途絶えると更新が停止する問題を解決し，接続が途絶えると前の値をプロットし続ける．
*/

//#define HWSERIAL Serial1
String recv_data = String(0); // 受信データ

#include "Bitcraze_PMW3901.h"
#include <Wire.h>
#include <VL53L0X.h>
#include <VL53L1X.h>
VL53L1X sensor_up;
VL53L1X sensor_down;

//#define SHUT_UP 5
//#define SHUT_DOWN 6

#define SHUT_UP 6
#define SHUT_DOWN 5 //切削基盤の時はこちら

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

const int debugmode=1;

void setup() {
  Serial1.begin(115200); //from arduino with UWB
  Serial3.begin(115200); //to raspberry pi
  Serial.begin(115200);  //to debug PC
  pinMode(13, OUTPUT);
  if (debugmode==1){
    Serial.print("debug__mode");
    digitalWrite(13, HIGH);
    return;
  }
    
  setup_sensor("flow"); // Initialize flow sensor

  pinMode(SHUT_UP, OUTPUT);
  pinMode(SHUT_DOWN, OUTPUT);
  digitalWrite(SHUT_UP, LOW);
  digitalWrite(SHUT_DOWN, LOW); 
  delay(100);
  setup_sensor("range"); // Initialize range sensor
  delay(100);

}

void setup_sensor(int mode){
  if (mode=="range"){
    Wire.begin();
    Wire.beginTransmission(0x29);
    Wire.setClock(400000); // use 400 kHz I2C
     /*##############################sensor@up config##############################*/  
      digitalWrite(SHUT_UP,HIGH);
      delay(150);
      sensor_up.init();
      delay(100);
      sensor_up.setAddress(0x33);
      sensor_up.setDistanceMode(VL53L1X::Medium);
      sensor_up.setMeasurementTimingBudget(33000);
      sensor_up.startContinuous(10);
      sensor_up.setTimeout(500); 
    /*##############################sensor@down config##############################*/
      digitalWrite(SHUT_DOWN,HIGH);
      delay(150);
      sensor_down.init();
      delay(100);
      sensor_down.setAddress(0x35);
      sensor_down.setDistanceMode(VL53L1X::Medium);
      sensor_down.setMeasurementTimingBudget(33000);
      sensor_down.startContinuous(10);
      sensor_down.setTimeout(500);

  }else if(mode="flow"){
    if (!flow_down.begin()) {
        Serial.println("Initialization of the flow sensor_downside failed");
//        while (1) {
        SCB_AIRCR = 0x05FA0004;//}//reset for teensyLC}
    }
    if (!flow_up.begin()) {
        Serial.println("Initialization of the flow sensor_upside failed");
        SCB_AIRCR = 0x05FA0004;
//        while (1) {SCB_AIRCR = 0x05FA0004;}//reset for teensyLC }
    }

  }
}




void loop() {
  t1 = millis();
  t2 = 0;
  elapsed = 0;
/*//////////////////////////////////////////////////////////*/  
  flow_up.readMotionCount(&deltaX_up, &deltaY_up);
    sum_dxdy("up");
  flow_down.readMotionCount(&deltaX_down, &deltaY_down);
    sum_dxdy("down");
/*//////////////////////////////////////////////////////////*/

  str_out =String(distance_dwn) + "," +String(deltaX_down) + "," + String(deltaY_down) + "," + String(dX_sum_dwn) + "," + String(dY_sum_dwn);
  str_out =str_out + "," + String(distance_up) + "," + String(deltaX_up) + "," + String(deltaY_up) + "," + String(dX_sum_up) + "," + String(dY_sum_up);
   
//  Serial.println(str_out);
//
//////  while (elapsed < update_rate) {
//////    elapsed = millis() - t1;
//////  }

////////////////////////////////////////////////////


  if (Serial1.available() > 0) {                 
    recv_data = Serial1.readStringUntil('\n');
  }

  if(recv_data.length()<22){
   str_out = str_out + ',' + recv_data;
//    Serial.println("distance\tdeltaX\tdeltaY\tdeltaX_sum\tdeltaY_sum\trecv_data");
    Serial.print(distance_dwn);Serial.print("\t\t");Serial.print(deltaX_down);Serial.print("\t");Serial.print(deltaY_down);Serial.println("\t");
//    Serial.print(deltaX_sum);Serial.print("\t\t");Serial.print(deltaY_sum);Serial.print("\t\t");
//    Serial.print(recv_data);Serial.print("\n");
//    Serial.println(str_out);
    Serial3.println(str_out);
  }
//
//    Serial.println("dXup_sum\tdYup_sum\tdXdwn_sum\tdYdwn_sum");
//    Serial.print(dX_sum_up);  Serial.print("\t\t"); Serial.print(dY_sum_up);  Serial.print("\t\t"); 
//    Serial.print(dX_sum_dwn); Serial.print("\t\t"); Serial.print(dY_sum_dwn); Serial.println("\t\t"); 
//    Serial.println("range_up\tup_dX\tup_dY\trange_dwn\tdwn_dX\tdwn_dY");
//    Serial.print(range_up);   Serial.print("\t\t"); Serial.print(deltaX_up);    Serial.print("\t"); Serial.print(deltaY_up);  Serial.print("\t");
//    Serial.print(range_dwn); Serial.println("\t\t"); Serial.print(deltaX_down);  Serial.print("\t"); Serial.println(deltaY_down);
}

void sum_dxdy(int mode){
  if(mode=="up"){
    range_up=sensor_up.read();
    if (sensor_up.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
     if (range_up > 0 && 3000 > range_up ) {
    distance_up = range_up;
  } else {
    distance_up = range_up_b;
  }
  range_up_b = distance_up;
     deltaX_up = -1 * deltaX_up * distance_up * 0.0651 * 0.76772;//2*tan(fov/2)
     deltaY_up = deltaY_up * distance_up * 0.0651 * 0.76772;
     dX_sum_up = dX_sum_up + deltaX_up * update_rate * 0.001;
     dY_sum_up = dY_sum_up + deltaY_up * update_rate * 0.001;

  }else if(mode=="down"){
    range_dwn=sensor_down.read();
    if (sensor_down.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
    if (range_dwn > 0 && 3000 > range_dwn ) {
      distance_dwn = range_dwn;
    } else {
      distance_dwn = range_dwn_b;
    }
    range_dwn_b = distance_dwn;
     deltaX_down = deltaX_down * distance_dwn * 0.0651 * 0.76772;//2*tan(fov/2)
     deltaY_down = deltaY_down * distance_dwn * 0.0651 * 0.76772;
     dX_sum_dwn = dX_sum_dwn + deltaX_down * update_rate * 0.001;
     dY_sum_dwn = dY_sum_dwn + deltaY_down * update_rate * 0.001;

  }
  /*,distance,deltaX,deltaY,dX_sum,dY_sum){*/
  
}
