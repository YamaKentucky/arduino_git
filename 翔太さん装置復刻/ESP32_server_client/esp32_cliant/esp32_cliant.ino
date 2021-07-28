/*クライアント側*/
#include <WiFi.h>

const char *ssid = "yourAP";
const char *pass = "yourPassword";


IPAddress ip(192, 168, 4, 2);           // for fixed IP Address
IPAddress gateway(192,168, 4, 1);        //
IPAddress subnet(255, 255, 255, 0);      //
IPAddress DNS(192, 168, 4, 90);          //

IPAddress host(192, 168, 4, 1);
const int sw_pin = 2;
const int port = 12345;
int flag=0;
int connection_mode=0;
int breakflag=0;

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);      // set the LED pin mode
  // サーバーに接続する
  WiFi.config(ip, gateway, subnet, DNS);   // Set fixed IP address
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(5, LOW); 
  }digitalWrite(5, HIGH); 
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // スイッチを初期化する
  pinMode(sw_pin, INPUT_PULLUP);
}



String comunicate_esp(WiFiClient client){
  String line="";
    while (!client.connect(host, port)) {
      Serial.println("connection failed");
      delay(1000);
//      return;
    }
    while (client.available() == 0) {
//      Serial.println("b");
      delay(10);
        }
    while(client.available()) {
      line = client.readStringUntil('\n');
      Serial.println(line);
    }
    return line;
}

void loop() {
  String line = "";
//  WiFiClient client;
  if(connection_mode==0){
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    WiFi.mode(WIFI_OFF);
    Serial.println("kill wifi");
    digitalWrite(5, LOW); 
    delay(4000);
    WiFi.begin(ssid, pass);
    delay(1000);
    Serial.println("begin wifi");
  }Serial.println("conect");digitalWrite(5, HIGH); 
  
  WiFiClient client;
  while (!client.connect(host, port)) {
      Serial.println("connection failed");
      delay(1000);
      return;
    }
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Timeout!");
        flag+=1;
        if (flag>10){
          client.stop();
          connection_mode=0;
          return;
        }
        
        
      }
    }
    while(client.available()) {
      line = client.readStringUntil('\n');
      Serial.println(line);
    }
    if (line=="OK"){
      delay(10000);
      flag=0;
      connection_mode=1;
    }
//    WiFiClient client;
    
  }else if (connection_mode==1){//////////////////////////////////////////////////////////////
    Serial.println("communication now");
    WiFiClient client;
    
    while (!client.connect(host, port)) {
      Serial.println("connection failed");
      delay(1000);
      return;
    }
    while (client.available() == 0) {
      breakflag+=1;
      Serial.println(breakflag);
      if (breakflag>5000){
        connection_mode=0;
        return;
      }

      delay(10);
        }
    while(client.available()) {
      line = client.readStringUntil('\n');
      Serial.println(line);
    }
//     line=comunicate_esp(client);
      if (line=="A"){
        Serial.println("OKdayo");
        delay(500);
        String row="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        row+="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,";
        
        client.print(row);client.print("\n");
        if (flag==1){
          Serial.println("finish to comunicate");
          client.print("kakunin");client.print("\n");
          connection_mode=2;
        }
        flag=1;
        line="";
        delay(10);
      }
    }else{
      Serial.println("finish");
      WiFi.mode(WIFI_OFF);
      digitalWrite(5, LOW); 
      delay(60000);
      connection_mode=0;
    }
//  while(1);
//  digitalWrite(5, HIGH);
//  
////  WiFiClient client;
//  static bool status = false;
//  static int sw_stat = HIGH;
//
//  // スイッチが押された場合
//  if (digitalRead(sw_pin) == LOW && sw_stat == HIGH) {
//    sw_stat = LOW;
//    // サーバーに接続する
//    if (!client.connect(host, port)) {
//      Serial.println("connection failed");
//      return;
//    }
//    // LEDの点灯／消灯状態を入れ替える
//    status = !status;
//    // 点灯させる場合はサーバーに「On」の文字列を送信する
//    if (status) {
//      Serial.println("Send On");
//      client.print("On\n");
//    }
//    // 消灯させる場合はサーバーに「Off」の文字列を送信する
//    else {
//      Serial.println("Send Off");
//      client.print("Off\n");
//    }
//    //client.print('\n');
//    // サーバーからのレスポンスを待つ
//    unsigned long timeout = millis();
//    while (client.available() == 0) {
//      if (millis() - timeout > 5000) {
//        Serial.println("Timeout!");
//        client.stop();
//        return;
//      }
//    }
//    // サーバーからのレスポンスを受信する
//    while(client.available()) {
//      String line = client.readStringUntil('\n');
//      Serial.print(line);
//    }
//    Serial.print('\n');
//    delay(200);
//  }
//  else {
//    sw_stat = HIGH;
//  }
}
