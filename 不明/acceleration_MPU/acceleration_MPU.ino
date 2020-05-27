#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;
#define LED_PIN 13
bool blinkState = false;

#include <Eigen.h>     // Calls main Eigen matrix class library
#include <Eigen/LU>             // Calls inverse, determinant, LU decomp., etc.
using namespace Eigen;  

#define PI 3.141592653589793
float Ap, Ar, My;
IntervalTimer myTimer;

//Gyro_offset
float mfx, mfy;
float Gx = 60;
float Gy = 60;
float bx = -92;
float by = 13;

Matrix3f MM;
Matrix<float,3,1> Av,Eu;

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
  //myTimer.begin(keisoku,5000);
}



void loop() {
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  //  Serial.print("acceleration:\t");
  //  Serial.print(ax); Serial.print("\t");
  //  Serial.print(ay); Serial.print("\t");
  //  Serial.println(az);

  Ap = atan2(ax, sqrt(ay * ay + az * az)) * 180 / PI;
  Ar = atan2(ay, az) * 180 / PI;

  mfx = (mx - bx) / Gx;
  mfy = (my - by) / Gy;


  Serial.print("pitch&roll:\t");
  Serial.print(Ap); Serial.print("\t");
  Serial.print(Ar); Serial.println("\t");

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

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

float range360(float My){
  if(My >= 360){ return  My - 360;  }    
  if(My < 0)   { return  360 + My;  }
  return My;
}

