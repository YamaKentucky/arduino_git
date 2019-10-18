#include <Wire.h>
#include <VL53L0X.h>
#include "PX4Flow.h"
#define PARAM_FOCAL_LENGTH_MM 16

PX4Flow sensor = PX4Flow();
long last_check = 0;
int px = 0;
int py = 0;
int flow_x_b = 0;
int a = 0.99;
float focal_length_px = (PARAM_FOCAL_LENGTH_MM) / (4.0f * 6.0f) * 1000.0f;


VL53L0X sensor_d;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  sensor_d.init();
  sensor_d.setTimeout(500);
  sensor_d.startContinuous();
}

void loop() {
  long loop_start = millis();

  if (loop_start - last_check > 10) {
    sensor.update_integral();
    int ground_distance = sensor_d.readRangeContinuousMillimeters();
    int x_rate = sensor.gyro_x_rate_integral();       // 10 * mrad
    int y_rate = sensor.gyro_y_rate_integral();       // 10 * mrad
    int flow_x = sensor.pixel_flow_x_integral();      // 10 * mrad
    int flow_y = sensor.pixel_flow_y_integral();      // 10 * mrad
    int timespan = sensor.integration_timespan(); // microseconds
    int quality = sensor.quality_integral();
    int flow_x_t = a * flow_x_b + (1 - a) * flow_x;
    //float pixel_x = flow_x + x_rate; // mrad
    float pixel_x = flow_x_t * 0.8 + x_rate * 0.2; // mrad
    float velocity_x = pixel_x * ground_distance / timespan;     // m/s
    px = px + velocity_x;


    //Serial.print(ground_distance); Serial.print(",");
    //Serial.print(x_rate); Serial.print(",");
    ////Serial.print(y_rate); Serial.print(",");
    //Serial.print(flow_x_t); Serial.print(",");
    ////Serial.print(flow_y); Serial.print(",");
    Serial.print(velocity_x); Serial.print(",");
    Serial.print(px);
    flow_x_b = flow_x_t;
    last_check = loop_start;
  }


  if (sensor_d.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }


  Serial.println();
}
