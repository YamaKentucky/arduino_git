//#include <MsTimer2.h>
#include <Servo.h>
Servo mServo;

void setup() {
  Serial.begin(9600);
  mServo.attach(9);
//  MsTimer2::set(5, loop);
 // MsTimer2::start();

}

void loop() {

  float samplerate = 500;
  float freq = 20;
  float q = 1 / pow(2, 1 / 2);
  float omega = 2.0f * 3.14159265f * freq / samplerate;
  float alpha = sin(omega) / (2.0f * q);

  float a0 =  1.0f + alpha;
  float a1 = -2.0f * cos(omega);
  float a2 =  1.0f - alpha;
  float b0 = (1.0f - cos(omega)) / 2.0f;
  float b1 =  1.0f - cos(omega);
  float b2 = (1.0f - cos(omega)) / 2.0f;

  int size =10;
  int input[size];
  input[size] = analogRead(0);
  float output[size];
  float val;
  for (int i = 0; i < size; i++)
  {
    float in1, in2, out1, out2 = 0;
    output[i] = b0 / a0 * analogRead(0) + b1 / a0 * in1  + b2 / a0 * in2
                - a1 / a0 * out1 - a2 / a0 * out2;

    in2  = in1;       // 2つ前の入力信号を更新
    in1  = input[i];  // 1つ前の入力信号を更新

    out2 = out1;      // 2つ前の出力信号を更新
    out1 = output[i]; // 1つ前の出力信号を更新
    val = output[i];
  }
  Serial.println(val);
  mServo.write((60 * val) - 1050 );
}
