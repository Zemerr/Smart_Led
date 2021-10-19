void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  Serial.println(myWiFiManager->getConfigPortalSSID());
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
      server.begin();
    }
    else {
      Serial.println("WiFi manager start");
      wifiManager.setDebugOutput(true);
//      wifiManager.resetSettings();
//      wifiManager.setConnectTimeout(60);
//       Serial.println("WiFi connect");
       

//      bool response;
//      response = wifiManager.autoConnect("ssid","password");
//       Serial.println("WiFi res");
       wifiManager.setConfigPortalBlocking(false);
//       wifiManager.setAPCallback(configModeCallback);
      if(!wifiManager.autoConnect(ssid,password)) {
        Serial.println("failed to connect to WIFI network,");
        notConnected = true;
        //reset and try again, or maybe put it to deep sleep
//        ESP.reset();
//        delay(1000);
      } 
    
      //if you get here you have connected to the WiFi
//      Serial.println("connected...yeey :)");
  
//      wifiManager.autoConnect(ssid, password);
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
