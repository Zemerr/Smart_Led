

void buttonTick() {
//   touch.tick();
//   if (touch.isSingle()) {
//     if (dawnFlag) {
//       manualOff = true;
//       dawnFlag = false;
//       loadingFlag = true;
//       FastLED.setBrightness(modes[currentMode].brightness);
//       changePower();
//     } else {
//       if (ONflag) {
//         ONflag = false;
//         changePower();
//       } else {
//         ONflag = true;
//         changePower();
//       }
//       sendSettings_flag = true;
//     }

    int buff = -1;
    if (Serial.available()) {       // есть что на вход?
        buff = Serial.parseInt(); // принять в переменную buff

        Serial.println("good");    // ошибка

  }

    if (ONflag && buff != -1) {
        Serial.println("good 2");
        Serial.println(currentMode); 
        currentMode = buff;
        Serial.println(currentMode);
        if (currentMode >= MODE_AMOUNT) currentMode = 0;
            FastLED.setBrightness(modes[currentMode].brightness);
            loadingFlag = true;
            // settChanged = true;
            // eepromTimer = millis();
            buff = -1;
            FastLED.clear();
            delay(1);
            // sendSettings_flag = true;
        }
    }
