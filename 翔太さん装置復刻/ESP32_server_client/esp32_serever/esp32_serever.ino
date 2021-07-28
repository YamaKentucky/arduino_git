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

IPAddress ip(192, 168, 4, 1);
IPAddress target_ip(192, 168, 4, 2);
IPAddress target_ip2(192, 168, 4, 3);
IPAddress target_ip3(192, 168, 4, 4);
WiFiServer server(12345);

void setup() {
  Serial.begin(115200);
  // ESP32をアクセスポイントとして動作させる
  WiFi.softAP(ssid, pass);
  WiFi.softAPConfig(ip, WiFi.gatewayIP(), WiFi.subnetMask());
  server.begin();
  Serial.println("Server started");
  // LEDの初期化
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  pinMode(led_pin2, OUTPUT);
  digitalWrite(led_pin2, LOW);
  pinMode(led_pin3, OUTPUT);
  digitalWrite(led_pin3, LOW);
 
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("APStarted. myIP Address:");
  Serial.println(myIP);
  Serial.print("server Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
   delay(500);
}

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


void loop() {
  String line = "";
  // クライアントからの通信を待つ
//  WiFiClient client = server.available();
if (server_mode==0){
  while (setup_esp()!=true){
    Serial.println("waiting");
  }
  Serial.println("all modules available");
  server_mode=1;
  }else if (server_mode==1){
    WiFiClient client = server.available();
    if (client.remoteIP()==target_ip){
      client.print("A");
       client.print("\n");
    while (client.available() == 0) {
       
       delay(1000);
       }
    }flag=0;
    while(client.available()) {
      line = client.readStringUntil('\n');
//      Serial.println(line);
    }
    if (line.length()>10 && finish==0){
      Serial.println(line);
      Serial.println("finish to comunicate @target1");
      Serial.println(line.length());
      finish=1;
       delay(500);
    }else if(line=="kakunin"){
      Serial.println("finish");
      finish=0;
//      delay(10000);
      server_mode=2;
    }
  }else{
     while (1);
  }
}
 

  
//  if (client) {
//    // 通信を始める
//    Serial.println("New Client.");
//    String line = "";
//    // データがある間受信する
//    while (client.connected()) {
//      if (client.available()) { 
//        char c = client.read();
//        // LFを受信したら受信を終える
//        if (c == '\n')
//          break;
//        line.concat(c);
//        Serial.print(c);
//      }
//    }
//    // 受信した文字列をシリアルモニタに出力する
//    Serial.print("\nReceived: ");
//    Serial.println(line);
//    // 受信した文字列が「On」なら
//    // LEDを点灯して、クライアントに「On OK」と送信する
//    if (line.equals("On")) {
//      digitalWrite(led_pin, HIGH);
//      client.print("On OK");
//    }else if (line.equals("Off")) {
//      digitalWrite(led_pin, LOW);
//      client.print("Off OK");
//    }else if (line.equals("A")) {
//      digitalWrite(led_pin1, HIGH);
//      client.print("On OK");
//    }else if (line.equals("B")) {
//      digitalWrite(led_pin1, LOW);
//      client.print("On OK");
//    }else{
//      Serial.println("?????");
//    }
//    client.print('\n');
//    delay(10);
//    // 通信を終える
//    client.stop();
//    Serial.println("Client Disconnected.");
//  }
//}


int setup_esp(){
  WiFiClient client = server.available();
  Serial.print(client.remoteIP());
  if(client.remoteIP()==target_ip){
    int client1=client;
    target=1;
    digitalWrite(led_pin, HIGH);
    client.print("OK");
    Serial.println("target");
  }
  if(client.remoteIP()==target_ip2  && target==1){
    int client2=client;
    target=2;
    digitalWrite(led_pin2, HIGH);
    client.print("OK");
    Serial.println("target2");
  }
  if(client.remoteIP()==target_ip3  && target==2){
    int client3=client;
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
