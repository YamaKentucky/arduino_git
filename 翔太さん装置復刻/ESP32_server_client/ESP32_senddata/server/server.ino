/*サーバー側*/

#include <WiFi.h>

const char *ssid = "yourAP";
const char *pass = "yourPassword";
IPAddress ip(192, 168, 4, 1);
IPAddress target_ip(192, 168, 4, 2);
IPAddress target_ipB(192, 168, 4, 3);
IPAddress target_ipC(192, 168, 4, 4);
WiFiServer server(80);

WiFiClient client ;

static const int led_pin = 2;

 
void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, pass);// ESP32をアクセスポイントとして動作させる
  WiFi.softAPConfig(ip, WiFi.gatewayIP(), WiFi.subnetMask());
  server.begin();
  // LEDの初期化
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  Serial.println("Server started");
}

void loop() {
  // クライアントからの通信を待つ
  WiFiClient client = server.available();
  if (client) {    // 通信を始める
    String line = "";
    while (client.connected()) {
      if (client.available()) { 
        String c = client.readStringUntil(';');
        Serial.println(c);
      }
    }

    
    client.print('\n');
    // 通信を終える
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
