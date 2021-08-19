void sync() {
  WiFi.mode(WIFI_OFF);Serial.println("kill wifi");
  int i=0;
  while(digitalRead(19)!=HIGH){
    if(i==0){
      digitalWrite(led_pin, LOW);digitalWrite(led_pin2, LOW);digitalWrite(led_pin3, LOW);
    }else if(i==1){
      digitalWrite(led_pin, LOW);digitalWrite(led_pin2, LOW);digitalWrite(led_pin3, HIGH);      
    }else if(i==2){
      digitalWrite(led_pin, LOW);digitalWrite(led_pin2, HIGH);digitalWrite(led_pin3, LOW);      
    }else if(i==3){
      digitalWrite(led_pin, HIGH);digitalWrite(led_pin2, LOW);digitalWrite(led_pin3, LOW);      
      i=0;
    }
    i++;
    delay(100);
  }
  Wire.requestFrom(0x68, 12);    // request 6 bytes from slave device #2//0x68
    
    while(Wire.available())    // slave may send less than requested
    { 
    char c = Wire.read();    // receive a byte as character
    Serial.print(c);         // print the character
    }
  Serial.print("finish");
  digitalWrite(led_pin, LOW);digitalWrite(led_pin2, LOW);digitalWrite(led_pin3, LOW);
   delay(5000);
  
}
