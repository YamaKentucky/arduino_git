/*サーバー側*/

#include <WiFi.h>

const char *ssid = "yourAP";
const char *pass = "yourPassword";
static const int led_pin = 2;
static const int led_pin2 = 0;
static const int led_pin3 = 4;
int target=0;
int server_mode=0;
int flag=0;
int finish=0;
int stepnumber=-1;
int sending=0;
String acc_data="";
int multi=0;
const int datasize=3000;
String databox[3100];

IPAddress ip(192, 168, 4, 1);
IPAddress target_ip(192, 168, 4, 2);
IPAddress target_ipB(192, 168, 4, 3);
IPAddress target_ipC(192, 168, 4, 4);
WiFiServer server(80);

WiFiClient client ;


int setup_esp(){
  WiFiClient client = server.available();
  if(client.remoteIP()==target_ip && target==0){
    target=1;
    
    digitalWrite(led_pin, HIGH);
    client.print("OK");
    Serial.println("target");
    
  }
  if(client.remoteIP()==target_ipB  && target==1){
    target=2;
    digitalWrite(led_pin2, HIGH);
    client.print("OK");
    Serial.println("target2");
  }
  if(client.remoteIP()==target_ipC  && target==2){
    target=3;
    digitalWrite(led_pin3, HIGH);
    client.print("OK");
    Serial.println("target3");
  }
  if(target==3){
    target=0;
    return true;
  }
  Serial.println(target);
  delay(1000);
  return false;
}

void task0(void* arg)
 {
  static int count = 0;
     while (1){      
      if (multi==1){
//           Serial.println(count);
           count++;
           if (count>50){
            while(1){
              count++;
              if(count%2==0){
              digitalWrite(led_pin, LOW);digitalWrite(led_pin2, LOW);digitalWrite(led_pin3, LOW);
              }else{
              digitalWrite(led_pin, HIGH);digitalWrite(led_pin2, HIGH);digitalWrite(led_pin3, HIGH);
              }
              delay(1000);
            }
           }
     }else{
      count=0;
     }
       delay(1000);
     }
 }

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, pass);// ESP32をアクセスポイントとして動作させる
  WiFi.softAPConfig(ip, WiFi.gatewayIP(), WiFi.subnetMask());
  server.begin();
  Serial.println("Server started");
  // LEDの初期化
  pinMode(led_pin, OUTPUT);digitalWrite(led_pin, LOW);
  pinMode(led_pin2, OUTPUT);digitalWrite(led_pin2, LOW);
  pinMode(led_pin3, OUTPUT);digitalWrite(led_pin3, LOW);
  
 
  IPAddress myIP = WiFi.softAPIP();
  Serial.printf("APStarted. myIP Address: %d\n",myIP);//Serial.println(myIP);
  Serial.printf("server Mac Address: %d\n",WiFi.macAddress());//Serial.println(WiFi.macAddress());
  Serial.printf("Subnet Mask: %d\n",WiFi.subnetMask());//Serial.println(WiFi.subnetMask());
  Serial.printf("Gateway IP: %d\n",WiFi.gatewayIP());//Serial.println(WiFi.gatewayIP());
  xTaskCreatePinnedToCore(task0, "Task0", 4096, NULL, 1, NULL, 1);
  delay(500);
}

void loop() {
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
      for (int i=0;i<2;i++){  
        if(i==0){
          dataA=rcvCommand(target_ip,0);//hoge
        }else if (i==1){ 
//          dataA=rcvCommand(target_ip,dataA.toInt());//ここで配列が送られてくる
          if(rcv_index(target_ip)!=true){i=0;}else{
            Serial.println("DONE");
          }
          
        }else{
          A=rcvCommand(target_ip,-1);//最初は0,stepnumber=-1
        }
      }Serial.println("finish__A");
//      for (int i=0;i<3;i++){  
//        if (i==0){ 
//           dataB=rcvCommand_forESP2(target_ipB,-1);
//        }else{
////          if(rcv_index(target_ip)!=true){i=0;}else{Serial.println("DONE"); }
//          rcvCommand_forESP2(target_ipB,A.toInt());//hoge
//        }
//      }Serial.println("finish__B");
//      for (int i=0;i<3;i++){   
//        if (i==1){ 
//          dataC=rcvCommand(target_ipC,-1);
//        }else{
//          rcvCommand(target_ipC,A.toInt());//いらｎ
//        }
//      }Serial.println("finish__C");
    server_mode=2;
    
  }else{//////////////////////////////////////////////////////////////////////////////
    multi=0;
    Serial.println("please");
    for (int i=0;i<3100;i++){
      Serial.println(databox[i]);
      delay(1);
    }
//    Serial.println(A);
//    Serial.println(dataA);
//    Serial.println(dataB);
//    Serial.println(dataC);
Serial.println("");
Serial.println(databox[2999]);
    while(1);//作業停止//////////////////////
    for(int i=0;i<2;i++){
       delay(1000);
       Serial.print(i);   
    }
   
    server_mode=1;
//    while(1);
  }
}
}

String rcvCommand(IPAddress target,int CMD){
  while(1){
    WiFiClient client = server.available();
    String rstr;
    String cmd;

    if (client.connected()) {
      if(client.remoteIP()==target){
        Serial.println("Connected to client");
     
        //コマンド文字列受信（文字列が来なければタイムアウトする）
        rstr = client.readStringUntil('\r');
        Serial.print("[");
        Serial.print(rstr);
        Serial.println("]");

        //応答送信
        cmd=String(CMD);
        client.print(cmd);client.print("\r");
        client.print("0");client.print("\r");
        //接続をクローズ
        if (client.available()>=0){//送信確認
          client.stop();
          Serial.println("Closed");
           return rstr;
        }
      }else{
        Serial.print("target not found");
        client.stop();
      }
    }else{client.stop();}
  } 
}
String rcvCommand_forESP2(IPAddress target,int CMD){
  while(1){
    WiFiClient client = server.available();
    String rstr;
    String cmd;

    if (client.connected()) {
      if(client.remoteIP()==target){
        Serial.println("Connected to client");
     
        //コマンド文字列受信（文字列が来なければタイムアウトする）
        rstr = client.readStringUntil('\r');
        Serial.print("[");
        Serial.print(rstr);
        Serial.println("]");

        //応答送信
        
        while (client.readStringUntil(';')=="0"){//送信確認
          cmd=String(CMD);
          client.print(cmd);client.print(";");

        }client.stop();
          Serial.println("Closed");
           return rstr;
      }else{
        Serial.print("target not found");
        client.stop();
      }
    }else{client.stop();}
  } 
}
int i=0;
bool rcv_index(IPAddress target){
    WiFiClient client = server.available();
      if(client.remoteIP()==target){
        while(client.readStringUntil(';')=="GO");
        delay(1);
        while (i<3000) {
           if (client.available()>0) { 
              String c = client.readStringUntil(';');
              databox[i]=c;
              i++;
            }delay(1);Serial.println(i);  
         }
          client.stop();
          Serial.println("Closed");
         return true;
      }else{
        Serial.println("target not found");
//        delay(500);
        client.stop();
        return false;
      }
}
    
///*################################################################*/

//String comunicate(){
//  String line="";
////  client.print("1222");client.print("\n");
//  while (client.available() == 0) {
//    client.print("1222");client.print("\n");
//    Serial.println("..");
//    delay(1000);
//  }flag=0;
//  while(client.available()) {
//    line = client.readStringUntil('\n');
//  }
//  return line;
//}


//int recv_data(){
//  WiFiClient client = server.available();
//  if(client.remoteIP()==target_ip && target==0){
////    target=1;
//    if(sending==0){
//      String line="";
//      client.print("1212");
//      while (client.available() == 0) {
//        
//        delay(1000);
//      }
//      while(client.available()) {
//        line = client.readStringUntil('\n');
//      }Serial.print(line);sending=1;
//    }else{
//      String line="";
//      client.print("1212");
//      while (client.available() == 0) {
//        
//        delay(1000);
//      }
//      while(client.available()) {
//        line = client.readStringUntil('\n');
//      }Serial.print(line);
//      target=1;sending=0;
//      
//      Serial.println("finish");
//    }
//  }
//  if(client.remoteIP()==target_ipB  && target==1){
//    if(sending==0){
//      String line="";
//      client.print("1212");
//      while (client.available() == 0) {
//        delay(1000);
//      }
//      while(client.available()) {
//        line = client.readStringUntil('\n');
//      }Serial.print(line);sending=1;
//    }else{
//      String line="";
//      client.print("1212");
//      while (client.available() == 0) {
//        delay(1000);
//      }
//      while(client.available()) {
//        line = client.readStringUntil('\n');
//      }Serial.print(line);
//      target=2;sending=0;
//      
//      Serial.println("finish");
//    }
//  }
//  if(client.remoteIP()==target_ipC  && target==2){
//    if(sending==0){
//      String line="";
//      client.print("1212");
//      while (client.available() == 0) {
//        delay(1000);
//      }
//      while(client.available()) {
//        line = client.readStringUntil('\n');
//      }Serial.print(line);sending=1;
//    }else{
//      String line="";
//      client.print("1212");
//      while (client.available() == 0) {
//        delay(1000);
//      }
//      while(client.available()) {
//        line = client.readStringUntil('\n');
//      }Serial.print(line);
//      target=3;sending=0;
//      
//      Serial.println("finish");
//    }
//  }
//  if(target==3){
//    target=0;
//    return true;
//  }
//  Serial.println(target);
//  delay(1000);
//  return false;
//}
//
//
////void comunicate_esp(client){
////    while (!client.connect(host, port)) {
////      Serial.println("connection failed");
////      delay(1000);
////      return;
////    }
////    while (client.available() == 0) {
//////      Serial.println("b");
////      delay(10);
////        }
////    while(client.available()) {
////      line = client.readStringUntil('\n');
////      Serial.println(line);
////    }
////    return line
////}
//
//
////void loop() {
////  WiFiClient client = server.available();
////
//////  if(client.remoteIP()==target_ip){
//// while(client >0){
////    Serial.println(client.remoteIP());
////    while(client.connected()){
////      client.println("println");
////      delay(1000);
////      client.println("\n");
////    }
////  }
////  delay(2000);
////  client.stop();
////  Serial.println("client disconnected");
////  }
