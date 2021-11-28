uint32_t effTimer;


void effectsTick() {
  if (!dawnFlag) {
    if (ONflag && millis() - effTimer >= ((currentMode < 5 || currentMode > 13) ? modes[currentMode].speed : 50) ) {
      effTimer = millis();
      switch (currentMode) {
        case 0: standart();
          break;
        case 1: sparklesRoutine();
          break;
        case 2: fireRoutine();
          break;
        case 3: rainbowVertical();
          break;
        case 4: rainbowHorizontal();
          break;
        case 5: colorsRoutine();
          break;
        case 6: madnessNoise();
          break;
        case 7: cloudNoise();
          break;
        case 8: lavaNoise();
          break;
        case 9: plasmaNoise();
          break;
        case 10: rainbowNoise();
          break;
        case 11: rainbowStripeNoise();
          break;
        case 12: zebraNoise();
          break;
        case 13: forestNoise();
          break;
        case 14: oceanNoise();
          break;
        case 15: colorRoutine();
          break;
        case 16: snowRoutine();
          break;
        case 17: matrixRoutine();
          break;
        case 18: lightersRoutine();
          break;
      }
      FastLED.show();
    }
  }
}


void changePower() {
  if (ONflag) {
    effectsTick();
    for (int i = 0; i < modes[currentMode].brightness; i += 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    FastLED.setBrightness(modes[currentMode].brightness);
    delay(2);
    FastLED.show();
  } else {
    effectsTick();
    for (int i = modes[currentMode].brightness; i > 8; i -= 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    FastLED.clear();
    delay(2);
    FastLED.show();
  }
}
