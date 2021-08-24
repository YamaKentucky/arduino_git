/*サーバー側*/

#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h> 
#include <Wire.h>
#include "M41T62.h"

RTC_Millis rtc;

const char *ssid = "yourAP";
const char *pass = "yourPassword";
static const int led_pin = 2;
static const int led_pin2 = 0;
static const int led_pin3 = 4;
const int sw1=16;
const int sw2=17;
const int sw_sync=15;


int wifistatus=0;
int target=0;
int server_mode=0;
int flag=0;
int finish=0;
int stepnumber=-1;
int sending=0;
String acc_data="";
int multi=0;
const int datasize=3000;
int number=0;
int action=-1;
String rstr;
String databox[3100];//String databoxB[3100];String databoxC[3100];
String stampbox="";
String ref_stamp="";

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
//      if(server_mode==2){
//        WiFiClient client = server.available();
//        if (client.connected()){
//            client.print(String(wifistatus));client.print(";");
//            Serial.println(client.remoteIP());
//        }else{Serial.println("Noclient");}delay(1000);
//      }
      if (multi==1){
           Serial.println(count);
           count++;
           if (count>50){
            while(multi==0){
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
  Wire.begin();
//  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  
  WiFi.softAP(ssid, pass);// ESP32をアクセスポイントとして動作させる
  WiFi.softAPConfig(ip, WiFi.gatewayIP(), WiFi.subnetMask());
  server.begin();
  Serial.println("Server started");
  // LEDの初期化
  pinMode(led_pin, OUTPUT);digitalWrite(led_pin, HIGH);
  pinMode(led_pin2, OUTPUT);digitalWrite(led_pin2, HIGH);
  pinMode(led_pin3, OUTPUT);digitalWrite(led_pin3, HIGH);
  pinMode(sw_sync, INPUT_PULLDOWN);
  pinMode(sw1, INPUT_PULLDOWN);pinMode(sw2, INPUT_PULLDOWN);
    SPIFFS.begin();
  digitalWrite(led_pin, LOW);digitalWrite(led_pin2, LOW);digitalWrite(led_pin3, LOW);
 if(digitalRead(sw1)==HIGH && digitalRead(sw2)==HIGH){
  action=2;//log取得モード
 }else if(digitalRead(sw1)==HIGH && digitalRead(sw2)==LOW){
  action=4;
 }else if(digitalRead(sw1)==LOW && digitalRead(sw2)==HIGH ){
  action=3;//timeset
 }else if(digitalRead(sw1)==LOW && digitalRead(sw2)==LOW ){
  action=1;//syncモード
 }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("APStarted. myIP Address: ");Serial.println(myIP);
  Serial.print("server Mac Address: ");Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");Serial.println(WiFi.gatewayIP());
//  xTaskCreatePinnedToCore(task0, "Task0", 4096, NULL, 1, NULL, 0);
  delay(500);
}


void loop(){
  Serial.println(action);
  if(action==1){
    Serial.println("sync mode");
//    timeset();
    sync();
  }else if(action==2){
    Serial.println("logging mode");
    logging();
  }else if(action==3){
    timeset();
  }else{
    Serial.println("error");
  }
}
