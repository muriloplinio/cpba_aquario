#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h> 

const char* ssid = "unifacs";
const char* password = "vivaauniversidade";

ESP8266WebServer server(80);
Servo myservo;

void setup(void){

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", [](){    
    server.send(200, "text/plain", "Hello Campus Party!!");
  });

  server.on("/feeder", [](){
    myservo.write(180);
    delay(1000);
    myservo.write(85);
    server.send(200, "text/plain", "Peixe Feeliiiizzz! :)");
  });
  

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
  myservo.attach(D2);
  
}

void loop(void){
  server.handleClient();
}

void handleNotFound(){
  server.send(200, "text/plain", "Tente /feeder");
}

