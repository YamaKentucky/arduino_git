unsigned long delta_time,pre_time;
void setup() {
  pre_time=millis();
  Serial.begin(9600);
}
void loop(){
 delta_time = millis()-pre_time;
 int val;
 val=analogRead(0);
 pre_time=millis();
 float sample=(float)(delta_time)/1000;
 Serial.print(sample);
 Serial.print('\t');
 Serial.println(val);

}
