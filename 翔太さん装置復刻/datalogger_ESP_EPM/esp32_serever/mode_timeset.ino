void timeset() {
//  WiFi.mode(WIFI_OFF);Serial.println("kill wifi");
  Serial.println("please set time Y,M,D,H,m,");
  Serial.println("\t ex) 2021,08,23,13,00,");
  
   while(1){
    if (Serial.available() > 0) {
       String y= Serial.readStringUntil(','); 
       String M=Serial.readStringUntil(','); 
       String D=Serial.readStringUntil(','); 
       String H=Serial.readStringUntil(','); 
       String m=Serial.readStringUntil(',');      
       rtc.adjust(DateTime(y.toInt(), M.toInt(), D.toInt(), H.toInt(), m.toInt(), 0));/*time*/
       DateTime now = rtc.now();
       Serial.print(now.year(), DEC);Serial.print('/');Serial.print(now.month(), DEC);Serial.print('/');Serial.print(now.day(), DEC);Serial.print(' ');
       Serial.print(now.hour(), DEC);Serial.print(':');Serial.print(now.minute(), DEC);Serial.print(':');Serial.println(now.second(), DEC);
       break;
    }}
    Serial.println("Are you sure? (yes; or no;)");
    while(1){
      if (Serial.available() > 0) {
        String S=Serial.readStringUntil(';');
        if (S=="no") {
           timeset();
            break;
        }else if (S=="yes") {
            break;
        }else{
          Serial.println("plese again (yes; or no;)");
        }
      }
    }Serial.print("OK");
  while (set_time("time")!=true){
    Serial.println("settime");
  }
  Serial.println("all modules available");
  WiFi.mode(WIFI_OFF);Serial.println("kill wifi");
  action=1;
}


int set_time(String cmd){
  WiFiClient client = server.available();
  if(client.remoteIP()==target_ip && target==0){
    target=1;
    digitalWrite(led_pin, HIGH);
    client.print("time");
    Serial.println("target");
   
    
  }else if(client.remoteIP()==target_ip && target==1){
    target=2;
    DateTime now = rtc.now();
    String row=String(now.year())+','+String(now.month())+','+String(now.day())+','+String(now.hour())+','+String(now.minute())+';';
    client.print(row);
    Serial.println(row);
     delay(500);
    }
  if(client.remoteIP()==target_ipB  && target==2){
    target=3;
    digitalWrite(led_pin2, HIGH);
    client.print("time");
    Serial.println("target2");
  }else if(client.remoteIP()==target_ipB && target==3){
    target=4;
    DateTime now = rtc.now();
    String row=String(now.year())+','+String(now.month())+','+String(now.day())+','+String(now.hour())+','+String(now.minute())+';';
    client.print(row);
    Serial.println(row);
    delay(500);
    }
  if(client.remoteIP()==target_ipC  && target==4){
    target=5;
    digitalWrite(led_pin3, HIGH);
    client.print("time");
    Serial.println("target3");
  }else if(client.remoteIP()==target_ipC && target==5){
    target=6;
    DateTime now = rtc.now();
    String row=String(now.year())+','+String(now.month())+','+String(now.day())+','+String(now.hour())+','+String(now.minute())+';';
    client.print(row);
    Serial.println(row);
    delay(500);
    }
  if(target==6){
    target=0;
    return true;
  }
  Serial.println(target);
  delay(1000);
  return false;
}
