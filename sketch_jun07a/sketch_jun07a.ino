#include <Servo.h> 
 
//サーボの設定
Servo myservo_Accel;
int Accel_pin_out = 9;
int Accel_val = 90;
 
Servo myservo_Steering;
int Steering_pin_out = 10;
int Steering_val = 90;
 
//入力の設定
int Accel_pin_in = 6;
int Steering_pin_in = 7;
unsigned long Accel_duration = 0;
unsigned long Steering_duration = 0;
 
void setup() {    
  Serial.begin(9600);            
  myservo_Accel.attach(Accel_pin_out);
  myservo_Steering.attach(Steering_pin_out);
  pinMode(Accel_pin_in, INPUT);
  pinMode(Steering_pin_in, INPUT);
}
 
void loop() {
  //入力
  //Accel_duration=pulseIn(Accel_pin_in,HIGH,10000)+25;
  Steering_duration = pulseIn(Steering_pin_in, HIGH, 10000);
   
  //演算
 // Accel_val = map(Accel_duration, 0, 666, 180, 0) ;  
  Steering_val = map(Steering_duration, 0, 666, 0, 180);  
  Serial.println(Steering_val);
  //出力
 // myservo_Accel.write(Accel_val);
  myservo_Steering.write(Steering_val);
   
  //待ち
  delay(10);  
}
