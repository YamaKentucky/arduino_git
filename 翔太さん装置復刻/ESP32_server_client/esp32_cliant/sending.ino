
void find_wifi(){
  while (WiFi.status() != WL_CONNECTED) {
    
    WiFi.mode(WIFI_OFF);Serial.println("kill wifi");
    digitalWrite(5, LOW); delay(5000);
    
    WiFi.begin(ssid, pass);Serial.println("begin wifi");
    digitalWrite(5, HIGH); delay(5000);
    wificount++;
    if (wificount==6){
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
    while (!client.connect(host, port)) {
      breakflag+=1;
      Serial.println("connection failed");
      delay(1000);
      return "0";
    }
    while (client.available() == 0) {
      breakflag+=1;
      if(breakflag%50==0){Serial.print("=");}
      if (breakflag>=500){
        Serial.println("");
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
//      WiFiClient client;
         if(WiFi.status() != WL_CONNECTED && connection_mode!=0){
          if (multi==1){
           Serial.println("###########################################");
           Serial.println("\t\t\tForced reset\t\t\t");
           Serial.println("###########################################");
           digitalWrite(23,HIGH);//teensy loggingmode
           delay(1000);
           ESP.restart();
          }
         }
//         if(connection_mode==2){
////          WiFiClient client;
////           if(client.connect(host, port)){
//            if (client.available() >= 0){
//              String A=client.readStringUntil(';');
//              Serial.println(A);
//              if(A.toInt()==0){
//                connection_mode=2;//ESP待機
//              }else{
//                connection_mode=3;//ESP始動
//              }
////            }
//         }Serial.println("serch");delay(500);}
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
      if (breakflag>30){//30        
        Serial.println("TimeOut");
        return false;
      }
    }client.print(str);
    do{
      lineline = client.readStringUntil('\r');
    } while (client.available() != 0);  //残りがあるときはさらに受信のためループ
    if(lineline.toInt()==0){lineline=str;}
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
    delay(500);
    Serial.print("\tsending\t");
    for (i=0;i<datasize;i++){
      client.print(box[i]);client.print(";");//Serial.println(box[i]);
      if(i%200==0){Serial.print("=");}
    }//end for 
    Serial.println(">OK");
    return true;
}



bool rcv_data_from_teensy(int stepnumber){
  int i=0;
  Serial2.print(stepnumber);Serial2.print(";");//欲しいデータのステップ番号
  Serial.printf("\treading\t %d \t",stepnumber);
  while(i<datasize){
   if (Serial2.available() > 0) { // 受信したデータが存在する
          String A = Serial2.readStringUntil('\n'); // 受信データを読み込む
          box[i]=A;
          if(i%200==0){Serial.print("=");}
          i++;          
    }  
  }//Serial.println(box[2999]);
  Serial.println(">OK");
  return true;
}
