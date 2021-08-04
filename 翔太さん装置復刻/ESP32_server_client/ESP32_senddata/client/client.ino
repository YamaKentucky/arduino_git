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

void setup() {
  Serial.begin(115200);
  // サーバーに接続す
  WiFi.config(ip, gateway, subnet, DNS);   // Set fixed IP address
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // スイッチを初期化する
  pinMode(sw_pin, INPUT_PULLUP);
}

void loop() {
  WiFiClient client;
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      return;
    }
    int start=millis();
       for (int i=0;i<3500;i++){
        String s=String(i);
        client.print(s);client.print(";");
        Serial.println(s);
      delay(1);
}Serial.println(millis()-start);
while(1);}
    
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
