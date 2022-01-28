void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void saveConfigCallback () {
#if DEBUG_MODE
  Serial.println("Should save config ********");
  Serial.println(WiFi.status());
#endif
   if (WiFi.status() == WL_CONNECTED) {
#if DEBUG_MODE
      Serial.println("CONNECTED TO WIFI");
#endif
      wifiIndicator = true;
      notConnected = false;
      FastLED.clear();
      delay(1);
      WifiGreen();
      FastLED.show();
   }
   else {
#if DEBUG_MODE
      Serial.println("NOT CONNECTED TO WIFI");
#endif
      wifiIndicator = true;
      notConnected = true;
      wifiManager.resetSettings();
      FastLED.clear();
      delay(1);
      WifiRed();
      FastLED.show();
   }
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
      Serial.println("WiFi manager start");
#endif
#if (USE_BUTTON == 1)
    if (digitalRead(BTN_PIN)) wifiManager.resetSettings();
#endif
      wifiManager.setDebugOutput(true);
      wifiManager.setConnectTimeout(5);

#if DEBUG_MODE
       //wifiManager.setAPCallback(configModeCallback);
#endif
      wifiManager.setSaveConfigCallback(saveConfigCallback);
      wifiManager.setBreakAfterConfig(true);

      wifiManager.setConfigPortalBlocking(false);

      if(!wifiManager.autoConnect(ssid,password)) {
#if DEBUG_MODE
        Serial.println("failed to connect to WIFI network,");
#endif
        notConnected = true;
      }
      else {
#if DEBUG_MODE
          Serial.print("Connected! IP address: ");
          Serial.println(WiFi.localIP());
#endif
      }
      lampIP = WiFi.localIP().toString();
    }
#if DEBUG_MODE
    Serial.println("HTTP server started");
    Serial.printf("UDP server on port %d\n", localPort);
#endif
    Udp.begin(localPort);
}
