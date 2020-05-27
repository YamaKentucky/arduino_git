int inPin = 7;
int val = 0;
unsigned long duration;
String str_send_data;
unsigned long sTime = 0;
unsigned long rTime = 0;
unsigned long cTime = 0;
 
void setup() {                
  Serial.begin(9600);
  sTime = millis();
  pinMode(inPin, INPUT);
}
 
void loop() {
  cTime = millis() - sTime;
  rTime = millis();
  duration = pulseIn(inPin, HIGH, 100000);
  str_send_data = String(cTime) + "," + String(duration);
  Serial.println(str_send_data);
  while(millis() - rTime < 100){
    delay(1);
  }
}
