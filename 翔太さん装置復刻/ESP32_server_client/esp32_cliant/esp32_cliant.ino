/*クライアント側*/
//HardwareSerial Serial2(2);
#include <WiFi.h>


const char *ssid = "yourAP";
const char *pass = "yourPassword";

// for fixed IP Address
IPAddress ip(192, 168, 4, 2);const int starttime=500;         // IP A COM9
//IPAddress ip(192, 168, 4, 3);const int starttime=1000;        // IP B COM15
//IPAddress ip(192, 168, 4, 4);const int starttime=1500;        // IP C COM16


IPAddress gateway(192,168, 4, 1);        //
IPAddress subnet(255, 255, 255, 0);      //
IPAddress DNS(192, 168, 4, 90);          //

IPAddress host(192, 168, 4, 1);
const int datasize=3000;//MAX3000
String box[datasize+100];

int cnt=0; 
const int sw_pin = 2;
const int port = 80;
const int sendTeensy=22;
int flag=0;
int connection_mode=0;
int breakflag=0;

int wificount=0;
String line = "";
String lineline = "";

//String row[3]={"hoge0","hoge1","hoge2"};

String row="hoge";

String data_lomg="1,2,3,4,5,6,7,8,9,0,1,2,3";
String timestep="10000";

int multi=0;
WiFiClient client;


void setup() {
  
  Serial2.begin(115200);
  Serial.begin(115200);
  
  pinMode(sendTeensy, OUTPUT);
  digitalWrite(sendTeensy,LOW);
  pinMode(5, OUTPUT);    pinMode(4, OUTPUT);   // set the LED pin mode
  pinMode(23, OUTPUT);
  digitalWrite(23,LOW);
//  for (int i=0;i<datasize;i++){
//    box[i]="";
//  }
  // サーバーに接続する
  WiFi.config(ip, gateway, subnet, DNS);   // Set fixed IP address
  WiFi.mode(WIFI_STA);WiFi.begin(ssid, pass);
  
  find_wifi();
  delay(starttime);
  Serial.print("WiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
  xTaskCreatePinnedToCore(task0, "Task0", 4096, NULL, 1, NULL, 1);
  
  
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
//        client.setTimeout(20000);
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
       if(sendindex()==true){cnt++;}else{client.stop();delay(500);}  
     }else if(cnt>2){
        row="hoge";       
        lineline = "";
        connection_mode=2;
      }
//      Serial.print("cnt\t");Serial.print(cnt);
//      Serial.print("\t mode \t");Serial.println(connection_mode);
      delay(500);
//      WiFiClient client;
 }else if(connection_mode==2){
      Serial.println("waiting");
      delay(5000);
      connection_mode=3;
 }else{/////////////////////////////////////////////////////////////////////////////
   
   client.stop();
   cnt=0;
    Serial.println("finish");
    multi=0;
    sleep_wifi(20);
    connection_mode=1;
    
    find_wifi();
 }
}


//＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃
//      if(sendSocket(row)==true){
//        Serial.print("lineline");Serial.println(lineline);
//        if (lineline.toInt()>0){
//          Serial2.print("1;");//Serial2.print(";");
//          Serial.print(lineline);Serial.print(";");
//          while(1);
////          row=box;
//          row="0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
//        }else if (lineline=="0"){//"what number of datastep??"
//          
//          row="10000";
//        }else{
//          row=data_lomg;
//        }
//        cnt++;
//      }
