#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <GyverButton.h>

//#define _stackSize (5748/4) 

#define DEBUG_MODE 1

#define USE_BUTTON 1    // 1 - использовать кнопку, 0 - нет

//-------НАЛАШТУВАННЯ МАТРИЦІ-------

#define BTN_PIN D6
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
// boolean dawnFlag = false;
boolean wifiIndicator = false;
boolean sendSettings_flag = false;
boolean settChanged = false;


// -------------------WIFI/UDP---------------------


WiFiServer server(80);
WiFiUDP Udp;

#ifndef APSSID
#define APSSID "LAMP"
#define APPSK  "smartledlamp"
#define CLIENTANNOUNCE "I WANT FIND SERVERlamp SAM GORDON"
#define SERVERANSWER "You find what you looking for Valera"
#endif
#define AP_PORT 8888

#define ESP_MODE 1

// ---------------- БИБЛИОТЕКИ -----------------
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

WiFiManager wifiManager;

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
unsigned int localPort = AP_PORT;
const String clientSay = CLIENTANNOUNCE;
const String serverAnswer = SERVERANSWER;

String lampIP = "";

char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet
String inputBuffer;
boolean notConnected = false;

GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);
uint32_t eepromTimer;


void setupMatrix()
{
    FastLED.addLeds<CHIPSET, PIN_LED, COLOR_ORDER>(leds, NUM_LEDS)/*.setCorrection(TypicalLEDStrip)*/;
    FastLED.setBrightness(BRIGHTNESS);
    if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.show();
    // FastLED.clear();
}

void setEeprom()
{
 // EEPROM
  EEPROM.begin(202);
  delay(50);
  if (EEPROM.read(198) != 20) {  // первый запуск
    EEPROM.write(198, 20);
    EEPROM.commit();

    for (byte i = 0; i < MODE_AMOUNT; i++) {
      EEPROM.put(3 * i + 40, modes[i]);
      EEPROM.commit();
    }
    // for (byte i = 0; i < 7; i++) {
    //   EEPROM.write(5 * i, alarm[i].state);   // рассвет
    //   eeWriteInt(5 * i + 1, alarm[i].time);
    //   EEPROM.commit();
    // }
    // EEPROM.write(199, 0);   // рассвет
    EEPROM.write(200, 0);   // режим
    EEPROM.commit();
  }
  for (byte i = 0; i < MODE_AMOUNT; i++) {
    EEPROM.get(3 * i + 40, modes[i]);
  }
//   for (byte i = 0; i < 7; i++) {
//     alarm[i].state = EEPROM.read(5 * i);
//     alarm[i].time = eeGetInt(5 * i + 1);
//   }
//   dawnMode = EEPROM.read(199);
  currentMode = (int8_t)EEPROM.read(200);
}

void proccess()
{
    effectsTick();
    buttonTick();
    server_tick();
    if (notConnected) {
     wifiManager.process();
    }
    eepromTick();
#if (USE_BUTTON == 1)
    buttonTick();
#endif
    ESP.wdtFeed();   // пнуть собаку
    yield();  // ещё раз пнуть собаку
}


void setup()
{
    ESP.wdtDisable();
#if DEBUG_MODE
    Serial.begin(9600);
    Serial.setTimeout(50);
#endif
    memset(matrixValue, 0, sizeof(matrixValue));
    setupMatrix();
    delay(1000);
    setup_wifi();
    setEeprom();
    randomSeed(micros());
}


void loop()
{
    proccess();
}

void eeWriteInt(int pos, int val) {
  byte* p = (byte*) &val;
  EEPROM.write(pos, *p);
  EEPROM.write(pos + 1, *(p + 1));
  EEPROM.write(pos + 2, *(p + 2));
  EEPROM.write(pos + 3, *(p + 3));
  EEPROM.commit();
}

int eeGetInt(int pos) {
  int val;
  byte* p = (byte*) &val;
  *p        = EEPROM.read(pos);
  *(p + 1)  = EEPROM.read(pos + 1);
  *(p + 2)  = EEPROM.read(pos + 2);
  *(p + 3)  = EEPROM.read(pos + 3);
  return val;
}
