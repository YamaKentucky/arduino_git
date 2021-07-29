/*クライアント側*/
#include <WiFi.h>

const char *ssid = "yourAP";
const char *pass = "yourPassword";

// for fixed IP Address
//IPAddress ip(192, 168, 4, 2);           // IP A COM9
//IPAddress ip(192, 168, 4, 3);           // IP B COM15
IPAddress ip(192, 168, 4, 4);           // IP C COM16

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
String line = "";
String lineline = "";

String row="hoge";
String data_lomg="1,2,3,4,5,6,7,8,9,0,1,2,3";
String timestep="10000";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);      // set the LED pin mode
  pinMode(4, OUTPUT); 
  // サーバーに接続する
  WiFi.config(ip, gateway, subnet, DNS);   // Set fixed IP address
  WiFi.mode(WIFI_STA);
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


void find_wifi(){
  while (WiFi.status() != WL_CONNECTED) {
    
    WiFi.mode(WIFI_OFF);Serial.println("kill wifi");
    digitalWrite(5, LOW); delay(5000);
    
    WiFi.begin(ssid, pass);Serial.println("begin wifi");
    digitalWrite(5, HIGH); delay(5000);
    
  }Serial.println("conect");
  digitalWrite(5, HIGH); 
  return;
}

String comunicate(){
  String line="";
  int breakflag=0;
  Serial.println(client);
    while (!client.connect(host, port)) {
      breakflag+=1;
      Serial.println("connection failed");
      delay(1000);
      return "0";
    }
    while (client.available() == 0) {
      breakflag+=1;
      Serial.println(breakflag);
      if (breakflag>2000){
//        connection_mode=0;
        return "0";
      }
      delay(10);
  }
    while(client.available()) {
      line = client.readStringUntil('\n');
    }
    return line;
}



void sending_data(){
    digitalWrite(4, HIGH);                                                  
    delay(500);                                                             
    if (flag==0){                                                           
      String row="1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,,9,0,1,2,3,4,5,6,7,8,9,0";
      client.print(row);client.print("\n");                                  
      flag=1;     
   }else{                                                                  
      Serial.println("finish to comunicate");                               
      client.print("10000");client.print("\n");                             
      connection_mode=2;                                                    
      flag=0; 
   }                                                                       
      digitalWrite(4, LOW);                                              
      delay(10);   
      return;
}

void sleep_wifi(int sleeptime){
  int i=0;
  Serial.println("sleeping");
  WiFi.mode(WIFI_OFF);
  while (i<sleeptime){
    if(i%2==0){
      digitalWrite(5, LOW); 
    }else{
      digitalWrite(5, HIGH); 
    }
    i++;
    delay(1000);
  }Serial.println("ohayou");
   connection_mode=0;
}


void loop() {
  
  Serial.print("mode\t\t");
    Serial.println(connection_mode);
  if(connection_mode==0){////////////////////////////////////////////////////////////
    find_wifi();
    WiFiClient client;
    line=comunicate();
    if (line=="OK"){
      Serial.println("setup compli");
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
      if(sendSocket(row)==true){
        Serial.print("lineline=");Serial.println(lineline);
        if (lineline=="0"){
          row="0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
        }else if (lineline=="-1"){
          row="10000";
//          timestep=
        }else{
          row=data_lomg;
        }
        cnt+=1;
      }
      if(cnt>2){
        connection_mode=2;
      }
      Serial.print(cnt);
      delay(1000);

 }else{/////////////////////////////////////////////////////////////////////////////
    sleep_wifi(30);
    connection_mode=1;
    cnt=0;
//      WiFi.mode(WIFI_OFF);
//      client.stop();
//      client.setTimeout(10000);delay(10000);
//      digitalWrite(5, LOW);    
//      while(1);
 }
}


bool sendSocket(String str){
  breakflag=0;
  if (client.connect(host, port)){ 
    Serial.print("Connected:");
    Serial.println(host);
    Serial.println("Posting: " + str);
 
    //送信
    client.print(str);

    //応答受信
    client.setTimeout(1000);
    while (client.available() == 0) {
      breakflag+=1;
      Serial.println(breakflag);
      delay(100);
      if (breakflag>30){
        
        Serial.println("TimeOut");
        return false;
      }
    }
    do{
      lineline = client.readStringUntil('\r');
      
      Serial.print("line=");Serial.println(lineline);
    } while (client.available() != 0);  //残りがあるときはさらに受信のためループ
    
    return true;
   } else{
     Serial.println("Connection failed.");
     return false;
  }
}
