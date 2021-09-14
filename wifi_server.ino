#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>



//WiFiServer server(80);
ESP8266WebServer server(80);  
WiFiUDP Udp;

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif
#define AP_PORT 8888

#define ESP_MODE 1

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
unsigned int localPort = AP_PORT;

String lampIP = "";


void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup_wifi() {
    if (ESP_MODE == 0) { 
      delay(1000);
      Serial.println();
      Serial.print("Configuring access point...");
      /* You can remove the password parameter if you want the AP to be open. */
      WiFi.softAP(ssid, password);
  
      IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);
      server.on("/", handleRoot);
      server.begin();
    }
    else {
      Serial.print("WiFi manager");
      WiFiManager wifiManager;
      wifiManager.setDebugOutput(false);
  
      wifiManager.autoConnect(ssid, password);
      /*WiFi.config(IPAddress(IP_STA[0], IP_STA[1], IP_STA[2], IP_STA[3]),
                  IPAddress(192, 168, 1, 1),
                  IPAddress(255, 255, 255, 0));*/
      Serial.print("Connected! IP address: ");
      Serial.println(WiFi.localIP());
      lampIP = WiFi.localIP().toString();
    }
    Serial.println("HTTP server started");
    Serial.printf("UDP server on port %d\n", localPort);
    Udp.begin(localPort);
}

void wifi_server_tick() {
//  server.handleClient();
}
