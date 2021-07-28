
//CA;22;CC;33;NCA;55;
/*-------------------------------------------------
EPM事態の操作，
EPM動作基板上のArduinoから値を受け取り表示するプログラム
--------------------------------------------------*/
//#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>

#include <Wire.h>
#include <WiFi.h> 
#include <WiFiClient.h> 
#include <WebServer.h>
#include <WiFiAP.h> 
const char *ssid = "esp";
const char *password = "12345678";
int ledStatus = LOW;
const int Button=4;
const int n=100;
const int reset=23;
int act=0;
int i=4;
WebServer server(80);


void setup() {
  pinMode(Button,OUTPUT);//2pinと相性悪し
  pinMode(reset,OUTPUT);
  
    delay(1000);
    digitalWrite(reset, HIGH);
    Serial.begin(9600);
    Wire.begin();
    Serial.println();
    Serial.print("Configuring access point...");
    WiFi.softAP(ssid,password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin();
    server.onNotFound(connection);
    server.on("/standby", HTTP_GET, standby);
    server.on("/condition", HTTP_GET, condition_EPM);
    server.on("/test", HTTP_GET, test);

    server.on("/react", HTTP_GET, reactivate);
    server.on("/fake", HTTP_GET, Fake);
    server.on("/fake_react", HTTP_GET,Fake_react);

    server.on("/fake_log", HTTP_GET, Fake_log);
    server.on("/log", HTTP_GET, logging);
    
    server.on("/emergency", HTTP_GET, emergency);
    Serial.println("HTTP server started");
        

}

void loop() {
    server.handleClient();
}
