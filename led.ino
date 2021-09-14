#include <FastLED.h>

//-------НАЛАШТУВАННЯ МАТРИЦІ-------

#define PIN_LED D2
#define CHIPSET WS2812B
#define COLOR_ORDER
#define COLOR_ORDER GRB
#define BRIGHTNESS 40
#define CURRENT_LIMIT 2000    // ліміт по струму в міліампер, автоматично управляє яскравістю, 0 - вимкнути ліміт


#define WIDTH 16
#define HEIGHT 16
#define NUM_LEDS WIDTH * HEIGHT
#define MODE_AMOUNT 18

CRGB leds[NUM_LEDS];
int8_t currentMode = 0;
boolean loadingFlag = true;
unsigned char matrixValue[11][16];
struct {
  byte brightness = 50;
  byte speed = 100;
  byte scale = 7;
} modes[MODE_AMOUNT];

boolean ONflag = true;
boolean dawnFlag = false;

void setupMatrix()
{
    FastLED.addLeds<CHIPSET, PIN_LED, COLOR_ORDER>(leds, NUM_LEDS)/*.setCorrection(TypicalLEDStrip)*/;
    FastLED.setBrightness(BRIGHTNESS);
    if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.show();
    FastLED.clear();
}

void proccess()
{
    effectsTick();
    buttonTick();
    wifi_server_tick();
}


void setup()
{
    Serial.begin(9600);
    Serial.setTimeout(50);
    memset(matrixValue, 0, sizeof(matrixValue));
    setupMatrix();
    setup_wifi();
}


void loop()
{
    proccess();
}
