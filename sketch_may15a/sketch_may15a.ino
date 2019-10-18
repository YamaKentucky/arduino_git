int Z;
IntervalTimer myTimer;

void setup() {
  Serial.begin(115200);
  analogReadResolution(16);
  myTimer.begin(ReadAnalog,10000);
}

void loop() {
 
}

void ReadAnalog(){
  Z = analogRead(A0);
  Serial.println(Z);
}

