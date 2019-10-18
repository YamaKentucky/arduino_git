#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;
#define LED_PIN 13
bool blinkState = false;

#define PI 3.141592653589793
float Ap, Ar;

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
}

void loop() {
  accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
  //  Serial.print("acceleration:\t");
  //  Serial.print(ax); Serial.print("\t");
  //  Serial.print(ay); Serial.print("\t");
  //  Serial.println(az);


  Ap = atan2(ax, sqrt(ay * ay + az * az)) * 180 / PI;
  Ar = atan2(ay, az) * 180 / PI;
  Serial.print("pitch&roll:\t");
  Serial.print(Ap); Serial.print("\t");
  Serial.println(Ar);
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
