/*サーバー側*/

#include <WiFi.h>
#include <SPIFFS.h> 

const char *ssid = "yourAP";
const char *pass = "yourPassword";
static const int led_pin = 2;
static const int led_pin2 = 0;
static const int led_pin3 = 4;
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
String rstr;
String databox[3100];//String databoxB[3100];String databoxC[3100];

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
//  static const int led_pin = 2;
//  static const int led_pin2 = 0;
//  static const int led_pin3 = 4;
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
//  xTaskCreatePinnedToCore(task0, "Task0", 4096, NULL, 1, NULL, 0);
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
      
      while(rcvCommand(target_ip,number)!=true);//hoge
      if(number==0){number=rstr.toInt();}
      while(rcv_index(target_ip,"/accdata1.csv")!=true);Serial.println("finish__A");
      while(rcvCommand(target_ipB,number)!=true);
      while(rcv_index(target_ipB,"/accdata2.csv")!=true);Serial.println("finish__B");
      while(rcvCommand(target_ipC,number)!=true);
      while(rcv_index(target_ipC,"/accdata3.csv")!=true);Serial.println("finish__C");
    server_mode=2;
    wifistatus=1;
  }else if(server_mode==2){
    multi=0;
    Serial.println("please");
    if (show()==true){
      number = rcvnumber();
    }
    server_mode=3;
  }else{//////////////////////////////////////////////////////////////////////////////
     server_mode=1;
  }
 }
}

bool rcvCommand(IPAddress target,int CMD){
  while(1){
    WiFiClient client = server.available();
    
    String cmd;
    
    if (client.connected()) {
      if(client.remoteIP()==target){
        Serial.print("\nConnected to client\t");Serial.println(client.remoteIP());
     
        //コマンド文字列受信（文字列が来なければタイムアウトする）
        rstr = client.readStringUntil('\r');
        Serial.print(rstr);
        
        //応答送信
        cmd=String(CMD);
        client.print(cmd);client.print("\r");
        
        //接続をクローズ
        int i=0;
        while (client.available()==0){
          client.print(cmd);client.print("\r");
          Serial.print(">");
          i++;delay(100);
          if(i>10){return false;}}
        //送信確認
          client.stop();
          Serial.println("Closed");
          return true;

      }else{
        Serial.print("x");
        client.stop();
      }
    }else{client.stop();}
  } 
}


bool rcv_index(IPAddress target,char * path){
  int i=0;
  SPIFFS.begin(); // SPIFFS開始
    WiFiClient client = server.available();
      if(client.remoteIP()==target){
        while(client.readStringUntil(';')!="GO"){Serial.print("A");}
        client.print("GO;");Serial.println("GO");
        delay(1);
        Serial.println("\n reading"); 
        while (i<3000) {
           if (client.available()>0) { 
              String c = client.readStringUntil(';');
              databox[i]=c;
              i++;
              if(i%1000==0){
                Serial.print(client.remoteIP());  Serial.print("\t");    Serial.println(i);  
              }
            }//delay(1);
         }
          i=0;          
          Serial.println("Closed");
          writeFile(path);
          client.stop();
         return true;
      }else{
        Serial.print("+");
        delay(300);
        client.stop();
        return false;
      }
}


void writeFile(const char *path){
    
    File file = SPIFFS.open(path, "w");
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    for (int i=0;i<3000;i++){
      file.println(databox[i]);
    }
    file.close();
}
///*################################################################*/
void readcsv(const char *path){
  SPIFFS.begin(); 
  File f = SPIFFS.open(path, "r");
  int start=millis();
  if (!f) {
    Serial.println("file open failed");
  } else {
    Serial.println("====== Reading from SPIFFS file =======");    
    for (int i=0; i<=3000; i++){
      String s=f.readStringUntil('\n');
      Serial.println(s);
    } // end for
    f.close();
  } 
}

bool show(){
      while(1){
       int inByte = Serial.read();
        switch (inByte) {
          case 'a':
            readcsv("/accdata1.csv");
            break;
          case 'b':
            readcsv("/accdata2.csv");
            break;
          case 'c':
            Serial.println("plese enter number");
            Serial.printf("now open data%d.csv \n",number);
            
            return true;
          case 'd':
            Serial.println("exit");
            return false;
          default:
            digitalWrite(led_pin, HIGH);digitalWrite(led_pin2, HIGH);digitalWrite(led_pin3, HIGH);
            }
      }
}

int rcvnumber(){
   String A ="";
  while (1){
    if(Serial.available()){
    A = Serial.readStringUntil(';');
      if (A.toInt()>0){
        return A.toInt();
      }else{
        Serial.println("onemore");
      }
    }
  }
}
