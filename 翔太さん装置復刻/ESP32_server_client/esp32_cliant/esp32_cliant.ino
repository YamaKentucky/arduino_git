/*クライアント側*/
//HardwareSerial Serial2(2);
#include <WiFi.h>

uint32_t chipId = 0;
const char *ssid = "yourAP";
const char *pass = "yourPassword";

// for fixed IP Address
//IPAddress ip(192, 168, 4, 2);const int starttime=500;         // IP A COM9
//IPAddress ip(192, 168, 4, 3);const int starttime=1000;        // IP B COM15
//IPAddress ip(192, 168, 4, 4);const int starttime=1500;        // IP C COM16

IPAddress ip;
IPAddress gateway(192,168, 4, 1);        //
IPAddress subnet(255, 255, 255, 0);      //
IPAddress DNS(192, 168, 4, 90);          //
IPAddress host(192, 168, 4, 1);
const int port = 80;


const int sendTeensy=4;//22
const int logTeensy=12;
const int led1=32;
const int led2=23;

const int datasize=3000;//MAX3000
String box[datasize+100];
int starttime=0;
int cnt=0; 

int flag=0;
int connection_mode=0;
int breakflag=0;

int wificount=0;
String line = "";
String lineline = "";

String row="hoge";

int multi=0;
WiFiClient client;


void setup() { 
  Serial2.begin(115200);Serial.begin(115200);
   /* set the LED pin mode*/
  pinMode(sendTeensy, OUTPUT);digitalWrite(sendTeensy,LOW);
  pinMode(logTeensy, OUTPUT);digitalWrite(logTeensy,LOW);
  pinMode(led1, OUTPUT);    digitalWrite(led1,HIGH);
  pinMode(led2, OUTPUT); digitalWrite(led2,HIGH);
  /*==set IP address==*/
    for(int i=0; i<17; i=i+8) {
      chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }  
    if(chipId==14908468){// IP A COM9
      ip=IPAddress(192, 168, 4, 2);const int starttime=500;    
      Serial.println("set IP A");     
    }else if(chipId==14026897){ // IP B COM15
      ip=IPAddress(192, 168, 4, 3);const int starttime=1000;     
      Serial.println("set IP B");   
    }else if(chipId==14018061){ // IP C COM16
      ip=IPAddress(192, 168, 4, 4);const int starttime=1500; 
      Serial.println("set IP C");       
    }
    delay(starttime);
  /*Set fixed IP address*/
    WiFi.config(ip, gateway, subnet, DNS);   
    WiFi.mode(WIFI_STA);WiFi.begin(ssid, pass);
  /*==connecting server==*/
    find_wifi();
  Serial.print("WiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
  xTaskCreatePinnedToCore(task0, "Task0", 4096, NULL, 1, NULL, 1);
  
  digitalWrite(led1,LOW);digitalWrite(led2,LOW);
}
String stamp="";
void loop() {
  Serial.printf("mode:%d\t cnt:%d\n",connection_mode,cnt);
  
  if(connection_mode==0){////////////////////////////////////////////////////////////
    find_wifi();/*wifiが無ければスリープモードに移行する*/
    WiFiClient client;
    line=comunicate();
    if (line=="OK"){//ESP(server)の確認
      client.stop();
      digitalWrite(sendTeensy,HIGH);delay(500);
      flag=0;
      connection_mode=1;
      while(1){//teensyの確認
        if (Serial2.available() > 0) {
           stamp = Serial2.readStringUntil(';');
           if (stamp.toInt()>0){
             break;
           }
          }delay(500);Serial.flush();
      }
        Serial.println(stamp);
//      client.setTimeout(20000);
      delay(1000);
      digitalWrite(sendTeensy,LOW);
    }else if(line=="-2"){
      connection_mode=0;
      sleep_wifi(1);
    }else{
      connection_mode=0;
    }
    row=stamp;
 }else if (connection_mode==1){//////////////////////////////////////////////////////
      multi=1;
      

     if(cnt==0){
        if (sendSocket(row)==true){cnt++;}else{client.stop();delay(5000);}  //5000
     }else if(cnt==1){
      Serial.println(lineline.toInt());
       rcv_data_from_teensy(lineline.toInt());cnt++;//
     }else if(cnt==2){
       if(sendindex()==true){cnt++;}else{client.stop();delay(1500);}  
     }else if(cnt>2){
        row="hoge";       
        lineline = "";
        connection_mode=2;
      }
      delay(500);
 }else if(connection_mode==2){//////////////////////////////////////////////////////
      Serial.println("waiting");
      delay(5000);
      connection_mode=3;
 }else{/////////////////////////////////////////////////////////////////////////////
     Serial.println("finish");
     client.stop();
//     digitalWrite(logTeensy,HIGH);//teensy loggingmode
     cnt=0;
     multi=0;
     sleep_wifi(20);
     connection_mode=1;
     find_wifi();
 }
}
