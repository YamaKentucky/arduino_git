void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
}

void loop() {
  String str1;
  // put your main code here, to run repeatedly:
  if(Serial.available()){
      str1=Serial.readStringUntil(';');
      Serial.println(str1);
    }
 

}
