
#define SEGMENT 1   // розмір 1 пікселя (якщо 1, то розір пікселя == 1 діод матриці)

// залить все
void fillAll(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}

// функция отрисовки точки по координатам X Y
void drawPixelXY(int8_t x, int8_t y, CRGB color) {
  int realPixel = getPixelNumber(x, y) * SEGMENT;
  for (byte i = 0; i < SEGMENT; i++) {
    leds[realPixel + i] = color;
  }
}

// отрмати колір пікселя
uint32_t getPixColor(int thisPix) {
    uint16_t realPixel = thisPix * SEGMENT;
    return (((long)leds[realPixel].r << 16) | ((long)leds[realPixel].g << 8 ) | (long)leds[realPixel].b);
}

// функция получения цвета пикселя в матрице по его координатам
uint32_t getPixColorXY(int8_t x, int8_t y) {
    return getPixColor(getPixelNumber(x, y));
}


// отимати номер пікселя
uint16_t getPixelNumber(int8_t x, int8_t y) {
    return (y * WIDTH/SEGMENT) + x + 1;
}
