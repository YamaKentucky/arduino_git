#include <Wire.h>
#include "PX4Flow.h"

#define PARAM_FOCAL_LENGTH_MM 16
#define LED 13

long last_check = 0;
int px = 0;
int py = 0;
float focal_length_px = (PARAM_FOCAL_LENGTH_MM) / (4.0f * 6.0f) * 1000.0f;
  
// Initialize PX4Flow library
PX4Flow sensor = PX4Flow(); 

void setup()
{
  // Initialize the digital pin as an output.
  pinMode(LED, OUTPUT);   
  
  // Initialize the I2C bus
  Wire.begin();       
  
  // Initialize the serial connection
  Serial.begin(115200);  
}

void loop()
{
  long loop_start = millis();
  
  while (Serial.available() > 0) {
    if (Serial.read() == 'r') {
      Serial.println("Reset");
      px = 0;
      py = 0;
    }
  }
  
  if (loop_start - last_check > 100) {
    // Fetch I2C data  
    sensor.update_integral();
    int x_rate = sensor.gyro_x_rate_integral() / 10.0f;       // mrad
    int y_rate = sensor.gyro_y_rate_integral() / 10.0f;       // mrad
    int flow_x = sensor.pixel_flow_x_integral() / 10.0f;      // mrad
    int flow_y = sensor.pixel_flow_y_integral() / 10.0f;      // mrad  
    int timespan = sensor.integration_timespan();               // microseconds
    int ground_distance = 600;    // mm
    int quality = sensor.quality_integral();
    
    if (quality > 100)
    {
      // Update flow rate with gyro rate
      float pixel_x = flow_x + x_rate; // mrad
      float pixel_y = flow_y + y_rate; // mrad
      
      // Scale based on ground distance and compute speed
      // (flow/1000) * (ground_distance/1000) / (timespan/1000000)
      float velocity_x = pixel_x * ground_distance / timespan;     // m/s
      float velocity_y = pixel_y * ground_distance / timespan;     // m/s 
      
      // Integrate velocity to get pose estimate
      px = px + velocity_x * 100;
      py = py + velocity_y * 100;
          
      // Output some data
      //Serial.print(millis());Serial.print(",");  
//      Serial.print(px);Serial.print("\t");
//      Serial.println(py);Serial.print("\t");    
      //Serial.println(ground_distance);
      Serial.print(flow_x);Serial.print(',');
      Serial.println(flow_y);    
      
    }
    else {
      Serial.println(".");
    }
    
    last_check = loop_start;
  }
}

