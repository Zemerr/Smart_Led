void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup_wifi() {
    if (ESP_MODE == 0) { 
      delay(1000);
#if DEBUG_MODE
      Serial.println();
      Serial.print("Configuring access point...");
#endif
      /* You can remove the password parameter if you want the AP to be open. */
      WiFi.softAP(ssid, password);
  
      IPAddress myIP = WiFi.softAPIP();
#if DEBUG_MODE
      Serial.print("AP IP address: ");
      Serial.println(myIP);
#endif
      server.begin();
    }
    else {
#if DEBUG_MODE
      Serial.println("WiFi manager starter");
#endif
      wifiManager.setDebugOutput(true);
      wifiManager.setConnectTimeout(3);
//      wifiManager.setTimeout(10);
//      wifiManager.resetSettings();
//      wifiManager.setConnectTimeout(60);
//       Serial.println("WiFi connect");
       

//      bool response;
//      response = wifiManager.autoConnect("ssid","password");
//       Serial.println("WiFi res");
       wifiManager.setConfigPortalBlocking(false);
//       wifiManager.setAPCallback(configModeCallback);
      if(!wifiManager.autoConnect(ssid,password)) {
#if DEBUG_MODE
        Serial.println("failed to connect to WIFI network,");
#endif
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
#if DEBUG_MODE
      Serial.print("Connected! IP address: ");
      Serial.println(WiFi.localIP());
#endif
      lampIP = WiFi.localIP().toString();
    }
#if DEBUG_MODE
    Serial.println("HTTP server started");
    Serial.printf("UDP server on port %d\n", localPort);
#endif
    Udp.begin(localPort);
}
