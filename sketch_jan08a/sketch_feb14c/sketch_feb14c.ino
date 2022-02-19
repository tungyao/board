#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "lx666666"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);


void handleRoot() {
  server.send(200, "text/html",postForms);
}
int addr = 0;
void handlePlain() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    addr = 0;
    server.send(200, "text/plain", "POST body was:\n" + server.arg("plain"));
    String message = "POST form was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      for(int j =0 ;j< server.arg(i).length();j++){  
        EEPROM.write(addr, server.arg(i)[j]);
        addr = addr + 1;
      }
      EEPROM.write(addr,',');
      addr = addr + 1;
    }
    EEPROM.write(addr,'?');
    EEPROM.end();
    server.send(200, "text/plain", message);
  }
}

void setup() {
  delay(1000);
  EEPROM.begin(512);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
   server.on("/postplain/", handlePlain);
  server.begin();
  Serial.println("HTTP server started");
  byte value;
  for(int i =0;i<512 ;i++){
    value =  EEPROM.read(addr);
    Serial.print(addr);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
    addr = addr + 1;
  }
}

void loop() {
  server.handleClient();
}
