

void inputTick() {
    int buff = -1;
    if (Serial.available()) {       // есть что на вход?
        buff = Serial.parseInt(); // принять в переменную buff

        Serial.println("good");    // ошибка

  }

    if (ONflag && buff != -1) {
        Serial.println("good 2");
        if (buff == 3)
        {
            WiFi.disconnect();
            wifiManager.resetSettings();
            ESP.eraseConfig();
            ESP.reset();
            ESP.restart();
        }
    }
}


boolean brightDirection;

void buttonTick() {
  touch.tick();
  if (touch.isSingle()) {
#if DEBUG_MODE
      Serial.println("TOUCH IS SINGLE");
#endif
//    if (dawnFlag) {
//      manualOff = true;
//      dawnFlag = false;
//      loadingFlag = true;
//      FastLED.setBrightness(modes[currentMode].brightness);
//      changePower();
//    } else {
      if (ONflag) {
        ONflag = false;
        changePower();
      } else {
        ONflag = true;
        changePower();
      }
      sendSettings_flag = true;
//    }
  }

  if (ONflag && touch.isDouble()) {
#if DEBUG_MODE
      Serial.println("TOUCH IS DOUBLE");
#endif
    if (++currentMode >= MODE_AMOUNT) currentMode = 0;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();
    FastLED.clear();
    delay(1);
    sendSettings_flag = true;
  }
  if (ONflag && touch.isTriple()) {
#if DEBUG_MODE
      Serial.println("TOUCH IS Triple");
#endif
    if (--currentMode < 0) currentMode = MODE_AMOUNT - 1;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();
    FastLED.clear();
    delay(1);
    sendSettings_flag = true;
  }

//  // вывод IP на лампу
//  if (ONflag && touch.hasClicks()) {
//    if (touch.getClicks() == 5) {
//      resetString();
//      while (!fillString(lampIP, CRGB::Green, true)) {
//        delay(1);
//        ESP.wdtFeed();   // пнуть собаку
//        yield();  // ещё раз пнуть собаку
//      }
//    }
//  }

  if (ONflag && touch.isHolded()) {
 #if DEBUG_MODE
      Serial.println("TOUCH IS HOLDED");
#endif
    brightDirection = !brightDirection;
  }
  if (ONflag && touch.isStep()) {
    #if DEBUG_MODE
      Serial.println("TOUCH IS STEP");
#endif
    if (brightDirection) {
      if (modes[currentMode].brightness < 10) modes[currentMode].brightness += 1;
      else if (modes[currentMode].brightness < 250) modes[currentMode].brightness += 5;
      else modes[currentMode].brightness = 255;
    } else {
      if (modes[currentMode].brightness > 15) modes[currentMode].brightness -= 5;
      else if (modes[currentMode].brightness > 1) modes[currentMode].brightness -= 1;
      else modes[currentMode].brightness = 1;
    }
    FastLED.setBrightness(modes[currentMode].brightness);
    settChanged = true;
    eepromTimer = millis();
    sendSettings_flag = true;
  }
}
