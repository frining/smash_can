#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "index.h" 
int counter = 0;
#define HUMAN_TRIGGER D1
#define HUMAN_ECHO    D3

#define LEVEL_TRIGGER D4
#define LEVEL_ECHO    D7

#define IN1 D2
#define IN2 D5
#define IN3 D6
#define IN4 D8

#define MAXV 946
#define MINV 791

#define PWM 250

const char* ssid = "ASUS";
const char* password = "freedom50";

ESP8266WebServer server(80); 

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleADC() {
 long duration, distance;
  digitalWrite(HUMAN_TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(HUMAN_TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(HUMAN_TRIGGER, LOW);
  duration = pulseIn(HUMAN_ECHO, HIGH);
  distance = (duration/2) / 29.1;
  delay(20);
 String adcValue = String(distance);
 Serial.println(adcValue);
 server.send(200, "text/plane", adcValue); 
}


void levelValue() {
 long duration, distance;
  digitalWrite(LEVEL_TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(LEVEL_TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(LEVEL_TRIGGER, LOW);
  duration = pulseIn(LEVEL_ECHO, HIGH);
  distance = (duration/2) / 29.1;
  delay(20);
 String Level = String(distance);
 server.send(200, "text/plane", Level); 
}

void battery() {
 int bat = analogRead(A0);
 bat = map(bat, MINV, MAXV,0, 100); 
 if(bat>100){bat = 100;}
  
 String batValue = String(bat);
 server.send(200, "text/plane", batValue); 
}

void setup(void){
  Serial.begin(115200);
  
 WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
 
  server.on("/", handleRoot);     
  server.on("/readADC", handleADC);
  server.on("/batLevel", battery);
  server.on("/rubLevel", levelValue);

  server.begin();     
  Serial.println("HTTP server started");

  ArduinoOTA.setHostname("SmashCan");
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  
  pinMode(HUMAN_TRIGGER, OUTPUT);
  pinMode(HUMAN_ECHO, INPUT);
  
  pinMode(LEVEL_TRIGGER, OUTPUT);
  pinMode(LEVEL_ECHO, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop(void){
  ArduinoOTA.handle();
  server.handleClient();        
}
