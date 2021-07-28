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
String acc_data="";

IPAddress ip(192, 168, 4, 1);
IPAddress target_ip(192, 168, 4, 2);
IPAddress target_ipB(192, 168, 4, 3);
IPAddress target_ipC(192, 168, 4, 4);
WiFiServer server(12345);

WiFiClient client ;

String comunicate(){
  String line="";
  client.print("1222");client.print("\n");
  while (client.available() == 0) {
    delay(1000);
  }flag=0;
  while(client.available()) {
    line = client.readStringUntil('\n');
  }
  return line;
}
  
//  if (line.length()>10 && finish==0){//dataを受け取る
//    acc_data=line;
//    Serial.print("line");Serial.println(line);
//    Serial.print("acc_data");Serial.println(acc_data);
//    Serial.println("finish to comunicate @target1");
//    Serial.print("length=");Serial.println(line.length());
//    finish=1;
//    delay(1000);
// }else if(line.length()>2 && finish==1){//step番号を受け取る
//    stepnumber=line.toInt();
//    Serial.println(line);
//    Serial.println(stepnumber);    
//    Serial.println("acc=");Serial.println(acc_data);Serial.println("\t\tfinish");
//    finish=0;
//    server_mode=2;
// }return acc_data;
//}


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
  String dataC="0";
  while(1){
  if (server_mode==0){//////////////////////////////////////////////////////////////////
    while (setup_esp()!=true){
      Serial.println("waiting");
    }Serial.println("all modules available");
    server_mode=1;
 }else if (server_mode==1){//////////////////////////////////////////////////////////
    client = server.available();
    Serial.println(server_mode);
    if (client.remoteIP()==target_ip){
      line=comunicate();
        if (line.length()>10 && finish==0){//dataを受け取る
          Serial.print("line");Serial.println(line);
          dataA=line;
          Serial.print("acc_data");Serial.println(acc_data);
          Serial.println("finish to comunicate @targetA");
//          Serial.print("length=");Serial.println(line.length());
          finish=1;
          delay(500);
       }else if(line.length()>2 && finish==1){//step番号を受け取る
          stepnumber=line.toInt();
          Serial.println(line);
          Serial.println(stepnumber);    
          Serial.println("acc=");Serial.println(acc_data);Serial.println("\t\tfinish");
          finish=0;
          server_mode=2;
      }else{
        server_mode=1;//やり直し
      }
    }
 }else if(server_mode==2){//////////////////////////////////////////////////////////////////////////
    client = server.available();
    if (client.remoteIP()==target_ipB){
      line=comunicate();
        if (line.length()>10 && finish==0){//dataを受け取る
          Serial.print("line");Serial.println(line);
          dataB=line;
          Serial.print("acc_data");Serial.println(acc_data);
          Serial.println("finish to comunicate @targetB");
//          Serial.print("length=");Serial.println(line.length());
          finish=1;
          delay(500);
       }else if(line.length()>2 && finish==1){//step番号を受け取る
          stepnumber=line.toInt();
          Serial.println(line);
          Serial.println(stepnumber);    
          Serial.println("acc=");Serial.println(acc_data);Serial.println("\t\tfinish");
          finish=0;
          server_mode=3;
      }else{
        server_mode=2;//やり直し
      }
    }
  }else if(server_mode==3){//////////////////////////////////////////////////////////////////////////
    client = server.available();
    if (client.remoteIP()==target_ipC){
      line=comunicate();
        if (line.length()>10 && finish==0){//dataを受け取る
          Serial.print("line");Serial.println(line);
          dataC=line;
          Serial.print("acc_data");Serial.println(acc_data);
          Serial.println("finish to comunicate @targetC");
//          Serial.print("length=");Serial.println(line.length());
          finish=1;
          delay(500);
       }else if(line.length()>2 && finish==1){//step番号を受け取る
          stepnumber=line.toInt();
          Serial.println(line);
          Serial.println(stepnumber);    
          Serial.println("acc=");Serial.println(acc_data);Serial.println("\t\tfinish");
          finish=0;
          server_mode=4;
      }else{
        server_mode=3;//やり直し
      }
    }
  }else{//////////////////////////////////////////////////////////////////////////////
    Serial.println("please");Serial.println(dataA);
    Serial.println(dataB);
    Serial.println(dataC);
    while(1);
  }
}
}


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
    return true;
  }
  Serial.println(target);
  delay(1000);
  return false;
  client.stop();
}




//void comunicate_esp(client){
//    while (!client.connect(host, port)) {
//      Serial.println("connection failed");
//      delay(1000);
//      return;
//    }
//    while (client.available() == 0) {
////      Serial.println("b");
//      delay(10);
//        }
//    while(client.available()) {
//      line = client.readStringUntil('\n');
//      Serial.println(line);
//    }
//    return line
//}


//void loop() {
//  WiFiClient client = server.available();
//
////  if(client.remoteIP()==target_ip){
// while(client >0){
//    Serial.println(client.remoteIP());
//    while(client.connected()){
//      client.println("println");
//      delay(1000);
//      client.println("\n");
//    }
//  }
//  delay(2000);
//  client.stop();
//  Serial.println("client disconnected");
//  }
