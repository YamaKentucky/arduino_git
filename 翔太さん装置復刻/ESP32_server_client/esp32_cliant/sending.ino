
void find_wifi(){
  while (WiFi.status() != WL_CONNECTED) {
    
    WiFi.mode(WIFI_OFF);Serial.println("kill wifi");
    digitalWrite(5, LOW); delay(5000);
    
    WiFi.begin(ssid, pass);Serial.println("begin wifi");
    digitalWrite(5, HIGH); delay(5000);
    wificount++;
    if (wificount==3){
      multi=1;
      wificount=0;
    }
  }Serial.println("conect");
  digitalWrite(5, HIGH); 
  return;
}

String comunicate(){
  String line="";
  int breakflag=0;
  Serial.println(client);
    while (!client.connect(host, port)) {
      breakflag+=1;
      Serial.println("connection failed");
      delay(1000);
      return "0";
    }
    while (client.available() == 0) {
      breakflag+=1;
      Serial.println(breakflag);
      if (breakflag>2000){
//        connection_mode=0;
        return "0";
      }
      delay(10);
  }
    while(client.available()) {
      line = client.readStringUntil('\n');
    }
    return line;
}



void sending_data(){
    digitalWrite(4, HIGH);                                                  
    delay(500);                                                             
    if (flag==0){                                                           
      String row="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,,9,0,1,2,3,4,5,6,7,8,9,0";
      client.print(row);client.print("\n");                                  
      flag=1;     
   }else{                                                                  
      Serial.println("finish to comunicate");                               
      client.print("10000");client.print("\n");                             
      connection_mode=2;                                                    
      flag=0; 
   }                                                                       
      digitalWrite(4, LOW);                                              
      delay(10);   
      return;
}

void sleep_wifi(int sleeptime){
  int i=0;
  Serial.println("sleeping");
  WiFi.mode(WIFI_OFF);
  while (i<sleeptime){
    if(i%2==0){
      digitalWrite(5, LOW); 
    }else{
      digitalWrite(5, HIGH); 
    }
    i++;
    delay(1000);
  }Serial.println("wake up");
   connection_mode=0;
}


void task0(void* arg){
     while (1){
         if(WiFi.status() != WL_CONNECTED && connection_mode!=0){
          if (multi==1){
           static int count = 0;
           Serial.print("task 0 : \t\t\t\t\t\t\t\t2222222");
           ESP.restart();
           Serial.println(count++);
           delay(1000);
         }
         }
     }
 }


 
bool sendSocket(String str){
  breakflag=0;
  if (client.connect(host, port)){ 
//    Serial.print("Connected:");
//    Serial.println(host);
    Serial.println("Posting: " + str);
 
    //送信
    client.print(str);

    //応答受信
    client.setTimeout(1000);
    while (client.available() == 0) {
      breakflag+=1;
      Serial.print(".");
      delay(100);
      if (breakflag>30){
        
        Serial.println("TimeOut");
        return false;
      }
    }
    do{
      lineline = client.readStringUntil('\r');
    } while (client.available() != 0);  //残りがあるときはさらに受信のためループ
    
    return true;
   } else{
     Serial.println("Connection failed.");
     return false;
  }
}
