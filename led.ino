#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>

#define _stackSize (5748/4) 

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
boolean sendSettings_flag = false;
boolean settChanged = false;


// -------------------WIFI/UDP---------------------


WiFiServer server(80);
WiFiUDP Udp;

#ifndef APSSID
#define APSSID "LAMP"
#define APPSK  "smartledlamp"
#endif
#define AP_PORT 8888

#define ESP_MODE 1

WiFiManager wifiManager;

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
unsigned int localPort = AP_PORT;

String lampIP = "";

char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet
String inputBuffer;


void setupMatrix()
{
    FastLED.addLeds<CHIPSET, PIN_LED, COLOR_ORDER>(leds, NUM_LEDS)/*.setCorrection(TypicalLEDStrip)*/;
    FastLED.setBrightness(BRIGHTNESS);
    if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.show();
    // FastLED.clear();
}

void proccess()
{
    effectsTick();
    buttonTick();
    server_tick();
     wifiManager.process();
//    Serial.println(" in loop");
    ESP.wdtFeed();   // пнуть собаку
    yield();  // ещё раз пнуть собаку
}


void setup()
{
    ESP.wdtDisable();
    Serial.begin(9600);
    Serial.setTimeout(50);
    memset(matrixValue, 0, sizeof(matrixValue));
    setupMatrix();
    delay(1000);
    setup_wifi();
}


void loop()
{
    proccess();
}
