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

#define PI 3.14159265
//#define Ts 0.023;
float Ap, Ar;
int Ts;
float Ax, Ay, Az, Gx, Gy, Gz, Mx, My, Mz;
float ax1, ay1, az1, ac;
int gx_, gy_, gz_, meangx, meangy, meangz, ax_, ay_, az_, meanax, meanay, meanaz;
Matrix3f A, A_, B, P, Q, R, S, K;
Matrix<float, 3, 1> Av, Eu, u, y;


//Gyro_offset
//float mfx, mfy;
//float Gx = 60;
//float Gy = 60;
//float bx = -92;
//float by = 13;

void setup() {
  Wire.begin();
  //Wire.setSCL(19);
  //Wire.setSDA(18);
  Serial.begin(38400);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  pinMode(LED_PIN, OUTPUT);

  for (int i = 0; i < 1000; i++) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    gx_ += gx;
    gy_ += gy;
    gz_ += gz;
    ax_ += ax;
    ay_ += ay;
    az_ += az;
  }

  meangx = gx_ / 1000.0;
  meangy = gy_ / 1000.0;
  meangz = gz_ / 1000.0;
  meanax = ax_ / 1000.0;
  meanay = ay_ / 1000.0;
  meanaz = az_ / 1000.0;

  ac = sqrt(meanax * meanax + meanay * meanay + meanaz * meanaz);
  meanax /= ac;
  meanay /= ac;
  meanaz /= ac;

  Ap = atan2(-meanax, sqrt(meanay * meanay + meanaz * meanaz)) ;
  Ar = atan2(meanay, meanaz) ;
  Eu << 0, Ap, Ar;

  A = Matrix3f::Identity();
  A_ = A.inverse();
  P << 1 * A;
  Q <<   0.005,    0,   0,
  0,    0.005,   0,
  0,    0,      0.005;

  R <<   1,  0,  0,
  0,  1,  0,
  0,    0,  1;
}



void loop() {
  int t0 = millis();
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

  ac = sqrt(ax * ax + ay * ay + az * az);

  ax1 = ax / ac;
  ay1 = ay / ac;
  az1 = az / ac;

  Ap = atan2(-ax1, sqrt(ay1 * ay1 + az1 * az1)) ;
  Ar = atan2(ay1, az1) ;

  //  mfx = (mx - bx) / Gx;
  //  mfy = (my - by) / Gy;
  Gx = (gx - meangx) * 250 / 32768.0 * PI / 180;
  Gy = (gy - meangy) * 250 / 32768.0 * PI / 180;
  Gz = (gz - meangz) * 250 / 32768.0 * PI / 180;

  //Av << gx,gy,gz;
  B << 0 , sin(Ar) / cos(Ap) , cos(Ar) / cos(Ap),
  0 ,      cos(Ar)    , -sin(Ar),
  1 , sin(Ar)*tan(Ap)  , cos(Ar)*tan(Ap);

  u << Gx, Gy, Gz;
  y << Eu(0, 0), Ap, Ar;

  //kalman
  Eu = A * Eu + B * u * (Ts / 1000.0);
  P = A * P * A_ + Q;
  S = A * P * A_ + R;
  K = P * A_ * S.inverse();
  Eu = Eu + K * (y - A * Eu);
  P = (A - K * A) * P;


      Serial.print(Eu(0, 0) * 180 / PI); Serial.print(",");
      Serial.print(Eu(1, 0) * 180 / PI); Serial.print(",");
      Serial.println(Eu(2, 0) * 180 / PI); Serial.print(",");

//  int P = Eu(1, 0) * 180 / PI;
//  int R = Eu(2, 0) * 180 / PI;
//  int Y = Eu(0, 0) * 180 / PI;
//  
//  Serial.write('H');
//  Serial.write(highByte(P));
//  Serial.write(lowByte(P));
//  Serial.write(highByte(R));
//  Serial.write(lowByte(R));
//  Serial.write(highByte(Y));
//  Serial.write(lowByte(Y));


  //  Serial.print(highByte(A),BIN);
  //  Serial.print(",");
  //  Serial.println(lowByte(A),BIN);

  // Serial.print(ax1); Serial.print(",");
  // Serial.print(ay1);Serial.print(",");
  // Serial.println(az1);Serial.print(",");
  //Serial.println(ac);

  //Serial.println(ac);
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
  Ts = millis() - t0;
}



