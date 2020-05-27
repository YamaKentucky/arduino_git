//MPU_i2c
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

//gyouretu
#include <Eigen.h>     // Calls main Eigen matrix class library
#include <Eigen/LU>             // Calls inverse, determinant, LU decomp., etc.
using namespace Eigen;  

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;
#define LED_PIN 13
bool blinkState = false;

#define PI 3.141592653589793
//#define Ts 0.023;
float Ap, Ar;
int Ts =0;
Matrix3f B;
Matrix<float,3,1> Av,Eu;


//Gyro_offset
//float mfx, mfy;
//float Gx = 60;
//float Gy = 60;
//float bx = -92;
//float by = 13;

int gx_,gy_,gz_,meangx,meangy,meangz;
float Ax, Ay, Az, Gx, Gy, Gz, Mx,My, Mz;

void setup() {
  Wire.begin();
  Wire.setSCL(19);
  Wire.setSDA(18);
  Serial.begin(38400);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  pinMode(LED_PIN, OUTPUT);

for(int i=0;i<1000;i++){
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  gx_ += gx;
  gy_ += gy;
  gz_ += gz;
}

meangx = gx_/1000;
meangy = gy_/1000;
meangz = gz_/1000;

  Eu <<0,0,0;
}



void loop() {
  int t0 = millis();
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  Ap = atan2(ax, sqrt(ay * ay + az * az)) ;
  Ar = atan2(ay, az) ;

//  mfx = (mx - bx) / Gx;
//  mfy = (my - by) / Gy;

  Gx = (gx-meangx) * 250 / 32768.0*PI/180;
  Gy = (gy-meangy) * 250 / 32768.0*PI/180;
  Gz = (gz-meangz) * 250 / 32768.0*PI/180;
  
Av << Gx,Gy,Gz;
B << 0 , sin(Ar)/cos(Ap) , cos(Ar)/cos(Ap),
     0 ,      cos(Ar)    ,-sin(Ar),
     1 , sin(Ar)*tan(Ap)  ,cos(Ar)*tan(Ap);

Eu = Eu + B * Av * Ts/1000; 

//  Serial.print("pitch&roll:\t");
//  Serial.print(Ap); Serial.print("\t");
//  Serial.print(Ar); Serial.print("\t");

//    Serial.print("Mag:\t");
//    Serial.print(mfx); Serial.print("\t");
//    Serial.println(mfy);

//  Serial.print(mx); Serial.print(",");
//  Serial.println(my); 

//  My = atan2(-mfy , mfx) * 180 / PI;
//  
//  if (My < 0) {
//    My = My + 360;
//  }
//
//  My = range360(My);
//
//  Serial.print("Yow_m:\t");
//  Serial.println(My);

 Serial.print(Eu(0,0)*180/PI); Serial.print(",");
 Serial.print(Eu(1,0)*180/PI);Serial.print(",");
 Serial.println(Eu(2,0)*180/PI);
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  Ts = millis() - t0;
//  Serial.println(t1);
}

float range360(float My){
  if(My >= 360){ return  My - 360;  }    
  if(My < 0)   { return  360 + My;  }
  return My;
}

