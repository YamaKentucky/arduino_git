void sync() {
  WiFi.mode(WIFI_OFF);Serial.println("kill wifi");
  int i=0;
  while(digitalRead(sw_sync)!=HIGH){
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
  writeTime(SPIFFS);
  Serial.print("finish");
  digitalWrite(led_pin, LOW);digitalWrite(led_pin2, LOW);digitalWrite(led_pin3, LOW);
   delay(5000);
  readtime(SPIFFS);
  delay(1000);
//  write_csv_to_SD(SD,"/hello.txt", "Hello ");/*OK*/
  while(1);
  
}

void writeTime(fs::FS &fs){
    DateTime now = rtc.now();
    File file = fs.open("/time.csv", "w");
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    String row=String(now.year())+','+String(now.month())+','+String(now.day())+','+String(now.hour())+','+String(now.minute())+';';
    file.println(row);
      
    file.close();
}
void readtime(fs::FS &fs){
  File f = fs.open("/time.csv","r");
  if (!f) {
    Serial.println("file open failed");
  } else {
    Serial.println("set up time==>");   
      String s=f.readStringUntil('\n');
      Serial.print(s);Serial.println(';');
    f.close();
  }
}
