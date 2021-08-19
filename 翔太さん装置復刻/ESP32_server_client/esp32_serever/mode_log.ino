
void logging() {
  String line = "";
  String dataA="0";
  String dataB="0";
  String dataC="0";String A="0";
  while(1){
  if (server_mode==0){//////////////////////////////////////////////////////////////////
    while (setup_esp()!=true){
      Serial.println("waiting");
    }Serial.println("all modules available");
    server_mode=1;
 }else if (server_mode==1){//////////////////////////////////////////////////////////
  
  multi=1;
  Serial.printf("aaa    %d\n",multi);
      
      while(rcvCommand(target_ip,number)!=true);//hoge
      if(number==0){number=rstr.toInt();}
      while(rcv_index(SPIFFS,target_ip,"/accdata1.csv")!=true);Serial.println("finish__A");
      while(rcvCommand(target_ipB,number)!=true);
      while(rcv_index(SPIFFS,target_ipB,"/accdata2.csv")!=true);Serial.println("finish__B");
      while(rcvCommand(target_ipC,number)!=true);
      while(rcv_index(SPIFFS,target_ipC,"/accdata3.csv")!=true);Serial.println("finish__C");
    server_mode=2;
    wifistatus=1;
  }else if(server_mode==2){
    multi=0;
    Serial.println("please");
    if (show(SPIFFS)==true){
      number = rcvnumber();
    }
    server_mode=3;
  }else{//////////////////////////////////////////////////////////////////////////////
     server_mode=1;
  }
 }
}

bool rcvCommand(IPAddress target,int CMD){
  while(1){
    WiFiClient client = server.available();
    
    String cmd;
    
    if (client.connected()) {
      if(client.remoteIP()==target){
        Serial.print("\nConnected to client\t");Serial.println(client.remoteIP());
     
        //コマンド文字列受信（文字列が来なければタイムアウトする）
        rstr = client.readStringUntil('\r');
        Serial.print(rstr);
        
        //応答送信
        cmd=String(CMD);
        client.print(cmd);client.print("\r");
        
        //接続をクローズ
        int i=0;
        while (client.available()==0){
          client.print(cmd);client.print("\r");
          Serial.print(">");
          i++;delay(100);
          if(i>10){return false;}}
        //送信確認
          client.stop();
          Serial.println("Closed");
          return true;

      }else{
        Serial.print("x");
        client.stop();
      }
    }else{client.stop();}
  } 
}


bool rcv_index(fs::FS &fs,IPAddress target,char * path){
  int i=0;
//  SPIFFS.begin(); // SPIFFS開始
 
    WiFiClient client = server.available();
//     client.setTimeout(2000);
      if(client.remoteIP()==target){
        while(client.readStringUntil(';')!="GO"){Serial.print(client.remoteIP());}
        client.print("GO;");Serial.println("GO");
        delay(10);client.flush();delay(10);
        Serial.print("\n reading"); Serial.print(client.remoteIP()); 
        while (i<3000) {
           if (client.available()>0) { 
              String c = client.readStringUntil(';');
              databox[i]=c;
              i++;
              if(i%500==0){
                 Serial.print("="); 
              }
            }//delay(1);
         }
          i=0;          
          Serial.println(">done");
          writeFile(fs,path);
          client.stop();
         return true;
      }else{
        Serial.print("+");
        delay(300);
        client.stop();
        return false;
      }
}


void writeFile(fs::FS &fs,const char *path){
    
    File file = fs.open(path, "w");
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    for (int i=0;i<3000;i++){
      file.println(databox[i]);
    }
    file.close();
}
///*################################################################*/
void readcsv(fs::FS &fs,const char *path){

  File f = fs.open("/accdata1.csv","r");
  File fB = fs.open("/accdata2.csv","r");
  File fC = fs.open("/accdata3.csv","r");
  int start=millis();
  if (!f) {
    Serial.println("file open failed");
  } else {
    Serial.println("====== Reading from SPIFFS file =======");    
    for (int i=0; i<=3000; i++){
      String s=f.readStringUntil('\n');
      String sB=fB.readStringUntil('\n');
      String sC=fC.readStringUntil('\n');

//      Serial.println(s+';'+sB+';'+sC);
      
      Serial.print(s);Serial.print(';');
      Serial.print(sB);Serial.print(';');
      Serial.println(sC);Serial.println(';');
    } // end for
    f.close();
  }
}

bool show(fs::FS &fs){
      while(1){
       int inByte = Serial.read();
        switch (inByte) {
          case 'a':
            readcsv(fs,"/accdata1.csv");
            break;
          case 'b':
            readcsv(fs,"/accdata2.csv");
            break;
          case 'c':
            Serial.println("plese enter number");
            Serial.printf("now open data%d.csv \n",number);
            
            return true;
          case 'd':
            Serial.println("exit");
            return false;
          default:
            digitalWrite(led_pin, HIGH);digitalWrite(led_pin2, HIGH);digitalWrite(led_pin3, HIGH);
            }
      }
}

int rcvnumber(){
   String A ="";
  while (1){
    if(Serial.available()){
    A = Serial.readStringUntil(';');
      if (A.toInt()>0){
        return A.toInt();
      }else{
        Serial.println("onemore");
      }
    }
  }
}
