void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int val;
val=analogRead(0);
Serial.print("analog value=");
Serial.println(val);
}
