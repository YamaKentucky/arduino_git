
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

void task1(void* arg){
     while (1){
      WiFiClient client;
      if(client.connect(host, port)){
      if (client.available() >= 0){
        String A=client.readStringUntil(';');
        Serial.print("A======");Serial.println(A);
        if(A.toInt()==0){
          while(1){
            Serial.print("aaa=");Serial.println(A);
            digitalWrite(4,HIGH);
          }
        }
      }
 }Serial.println("NO");delay(1000);
 }
}
 
bool sendSocket(String str){
  breakflag=0;
  if (client.connect(host, port)){ 
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

int i=0;
bool sendindex(){
   if (!client.connect(host, port)) {
      Serial.println("connection failed");
      return false;
    }
    client.print("GO;");Serial.println("GO;");
    delay(1);
    Serial.print("\tsending\t");
    for (i=0;i<3000;i++){
     
      client.print(box[i]);client.print(";");Serial.println(box[i]);
//      client.print(i);client.print(";");Serial.println(i);
      delay(3);
    }//end for 
    
   Serial.println(box[2999]);
    
    return true;
}



bool rcv_data_from_teensy(){
  int i=0;
  Serial2.print(1);//欲しいデータのステップ番号
  Serial.print("\treading\t");
  while(i<datasize){
   if (Serial2.available() > 0) { // 受信したデータが存在する
          String A = Serial2.readStringUntil('\n'); // 受信データを読み込む
          box[i]=A;
          i++;
          
    }delay(1);
          
  }Serial.println(box[2999]);
  return true;
}
