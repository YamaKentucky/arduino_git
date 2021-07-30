/*クライアント側*/
#include <WiFi.h>

const char *ssid = "yourAP";
const char *pass = "yourPassword";

// for fixed IP Address
//IPAddress ip(192, 168, 4, 2);const int starttime=500;           // IP A COM9
//IPAddress ip(192, 168, 4, 3);  const int starttime=1000;         // IP B COM15
IPAddress ip(192, 168, 4, 4); const int starttime=1500;           // IP C COM16

IPAddress gateway(192,168, 4, 1);        //
IPAddress subnet(255, 255, 255, 0);      //
IPAddress DNS(192, 168, 4, 90);          //

IPAddress host(192, 168, 4, 1);
const int sw_pin = 2;
const int port = 80;
int flag=0;
int connection_mode=0;
int breakflag=0;
int cnt=0;
int wificount=0;
String line = "";
String lineline = "";

String row="hoge";
String data_lomg="1,2,3,4,5,6,7,8,9,0,1,2,3";
String timestep="10000";

int multi=0;
WiFiClient client;


void setup() {
  
  Serial.begin(115200);
  pinMode(5, OUTPUT);    pinMode(4, OUTPUT);   // set the LED pin mode
  // サーバーに接続する
  WiFi.config(ip, gateway, subnet, DNS);   // Set fixed IP address
  WiFi.mode(WIFI_STA);WiFi.begin(ssid, pass);
  
  find_wifi();
  delay(starttime);
  Serial.printf("WiFi connected\nIP address: %d",WiFi.localIP());
  xTaskCreatePinnedToCore(task0, "Task0", 4096, NULL, 1, NULL, 1);
  // スイッチを初期化する
  pinMode(sw_pin, INPUT_PULLUP);
}
void loop() {
  Serial.printf("mode\t\t%d\n",connection_mode);
  if(connection_mode==0){////////////////////////////////////////////////////////////
    find_wifi();/*wifiが無ければスリープモードに移行する*/
    WiFiClient client;
    line=comunicate();
    if (line=="OK"){
      Serial.println("setup compleated");
      client.stop();
      client.setTimeout(10000);delay(10000);
      flag=0;
      connection_mode=1;
    }else if(line=="-2"){
      connection_mode=0;
      sleep_wifi(1);
    }else{
      connection_mode=0;
    }
 }else if (connection_mode==1){//////////////////////////////////////////////////////
      multi=1;
      if(sendSocket(row)==true){
        if (lineline=="0"){
          row="0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
        }else if (lineline=="-1"){
          row="10000";
        }else{
          row=data_lomg;
        }
        cnt++;
      }
      if(cnt>2){
        row="hoge";
        cnt=0;
        lineline = "";
        connection_mode=2;
      }
      delay(100);

 }else{/////////////////////////////////////////////////////////////////////////////
    
    multi=0;
    sleep_wifi(5);
    connection_mode=1;
    
    find_wifi();
 }
}
