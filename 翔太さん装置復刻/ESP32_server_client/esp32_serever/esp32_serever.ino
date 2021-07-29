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
  Serial.print("APStarted. myIP Address:\t");Serial.println(myIP);
  Serial.print("server Mac Address:\t");Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask:\t");Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: \t");Serial.println(WiFi.gatewayIP());
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
  Serial.print("aaaaaaaaa");
      for (int i=0;i<3;i++){     
        if(i==0){
          rcvCommand(target_ip,0);//hoge
        }else if (i==1){ 
          dataA=rcvCommand(target_ip,-1);
        }else if(i==2){
          A=rcvCommand(target_ip,-1);//最初は0,stepnumber=-1
        }else{
          rcvCommand(target_ip,-1);
        }
      }Serial.println("finish__A");
      for (int i=0;i<3;i++){  
        if (i==1){ 
           dataB=rcvCommand(target_ipB,-1);
        }else{
          rcvCommand(target_ipB,A.toInt());//hoge
        }
      }Serial.println("finish__B");
      for (int i=0;i<3;i++){   
        if (i==1){ 
          dataC=rcvCommand(target_ipC,-1);
        }else{
          rcvCommand(target_ipC,A.toInt());//いらｎ
        }
      }Serial.println("finish__C");
    server_mode=2;
  }else{//////////////////////////////////////////////////////////////////////////////
    Serial.println("please");
    Serial.println(A);
    Serial.println(dataA);
    Serial.println(dataB);
    Serial.println(dataC);
    for(int i=0;i<20;i++){
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
     
        //接続をクローズ
        client.stop();
        Serial.println("Closed");
         return rstr;
      }else{
        Serial.print("target not found");
        client.stop();
      }
    }
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
