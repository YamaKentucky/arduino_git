/*2021/12/17
距離センサの精度評価
VL53L0X,VL53L1Xのセンサを使用
teensy4 に書き込み
----------|                   |----------|
[VL53L0x] |                   | [VL53L1x]|  
      vdd +---- teensy 5v ----+ VDD 
      GND +---- teensy GND ---+ GND
      SDA +---- tennsy SDA ---+ SDA
      SCL +---- teensy SCL ---+ SCL
          |     teensy 6 -----+ XSHUT
----------|                   |----------|
*/

#include <Wire.h>
#include <VL53L0X.h>
#include <VL53L1X.h>
//VL53L1X sensor_up;
VL53L0X range_0x;
VL53L1X range_1x;

#define old_SHUT_pin 7  //old_SHUT_pin 6
#define new_SHUT_pin 6  //new_SHUT_pin
#define SHUT_pin_up 6  //new_SHUT_pin

int box_0x[100];
int box_1x[100];

int distance;

void setup()
{
  pinMode(old_SHUT_pin, OUTPUT);
  pinMode(new_SHUT_pin, OUTPUT);
  pinMode(SHUT_pin_up, OUTPUT);
  digitalWrite(old_SHUT_pin, LOW);
  digitalWrite(new_SHUT_pin, LOW);
  digitalWrite(SHUT_pin_up, LOW);

  delay(500);
  Wire.begin();
  Wire.beginTransmission(0x29);
  Wire.setClock(400000); // use 400 kHz I2C
  Serial.begin (115200);

//--------------------------------------------------------/*
  delay(150);
  range_0x.init(true);
  delay(100);
  range_0x.setAddress((uint8_t)25);
  range_0x.setMeasurementTimingBudget(33000);
  Serial.println("Set left sensor address");
//--------------------------------------------------------/*
//
//--------------------------------------------------------/*
  digitalWrite(new_SHUT_pin, HIGH);
      delay(150);
      range_1x.init();
      delay(100);
      range_1x.setAddress(0x33);
      range_1x.setDistanceMode(VL53L1X::Medium);
      range_1x.setMeasurementTimingBudget(33000);
      range_1x.startContinuous(10);
      range_1x.setTimeout(500);
  Serial.println("Set right sensor address");
//--------------------------------------------------------*/

////--------------------------------------------------------*/
//    digitalWrite(SHUT_pin_up,HIGH);
//      delay(150);
//      sensor_up.init();
//      delay(100);
//      sensor_up.setAddress(0x33);
//      sensor_up.setDistanceMode(VL53L1X::Medium);
//      sensor_up.setMeasurementTimingBudget(33000);
//      sensor_up.startContinuous(10);
//      sensor_up.setTimeout(500); 
////--------------------------------------------------------*/

  for (int i=0;i<50;i++){
//    Serial.print("-");
    range_0x.readRangeSingleMillimeters();
    range_1x.read();
    delay(10);
  }
  delay(1000); 
}

void loop()
{
  int sum_0x=0;int sum_1x=0;
  float dev_0x=0;float dev_1x=0; 
  int max_0x=0;int min_0x=10000;
  int max_1x=0;int min_1x=10000;
  
  for (int i=0;i<100;i++){
    if (i%2==0){Serial.print("-");}
    box_0x[i] = range_0x.readRangeSingleMillimeters();
    box_1x[i] = range_1x.read();
    delay(10);
  }
  for (int i=0;i<100;i++){//平均を求める//
    sum_0x += box_0x[i];
    if (max_0x < box_0x[i]){ max_0x = box_0x[i]; }
    if (min_0x > box_0x[i]){ min_0x = box_0x[i]; }
    sum_1x += box_1x[i];
    if (max_1x < box_1x[i]){ max_1x = box_1x[i]; }
    if (min_1x > box_1x[i]){ min_1x = box_1x[i]; }
    
  }
  
  int size_0x = sizeof(box_0x) / sizeof(int);
  float ave_0x = sum_0x / size_0x ;
  int size_1x = sizeof(box_1x) / sizeof(int);
  float ave_1x = sum_1x / size_1x ;

  for (int i=0;i<100;i++){
    dev_0x = dev_0x +(ave_0x - box_0x[i])*(ave_0x - box_0x[i]);
    dev_1x = dev_1x +(ave_1x - box_1x[i])*(ave_1x - box_1x[i]);
  }
  dev_0x = dev_0x / size_0x;
  dev_1x = dev_1x / size_1x;
  Serial.println("");
  Serial.print("Min\t");Serial.print(min_0x);Serial.print("\tMin\t");Serial.println(min_1x);
  Serial.print("Max\t");Serial.print(max_0x);Serial.print("\tMax\t");Serial.println(max_1x);
  Serial.print("AVE\t");Serial.print(ave_0x);Serial.print("\tAVE\t");Serial.println(ave_1x);
  Serial.print("DEV\t");Serial.print(dev_0x);Serial.print("\tDEV\t");Serial.println(dev_1x);
  Serial.println("\n");
  for (int i=0;i<100;i++){
    Serial.print("\t");Serial.print(box_0x[i]);Serial.print("\t\t");Serial.println(box_1x[i]);
    
  }
  while (1);
//  
//  
//  Serial.print(range_0x.readRangeSingleMillimeters());
//  Serial.print(" : ");
//  Serial.println(range_1x.read());
////  delay(1000);
}
