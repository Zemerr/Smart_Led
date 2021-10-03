
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
