#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>

#define LED_STRIP_PIN   4
#define LED_COUNT 37
#define LED_INFO_PIN 2
#define SERIAL_ON false

Ticker ticker_server;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int duration = 100;
int brightness = 25;
int red = 0;
int green = 0;
int blue = 0;

//// Animation variables

enum animation_modes {
  OFF = 0,
  COLORWIPE = 1,
  CURTAINS = 2 ,
  DIAMONDS = 3 ,
  RANDOM_DIAMONDS = 4,
  THEATER = 5
};

typedef enum animation_modes animation_modes;
animation_modes animation_mode = OFF;
uint8_t number_of_modes = 6; // plus off mode

//// Palletes variables

enum palettes_modes {
  RETROWAVE = 0,
  RAINBOW   = 1,
  PINK      = 2,
  RED       = 3,
  ORANGE    = 4,
  YELLOW    = 5,
  BROWN     = 6,
  GREEN     = 7,
  CYAN      = 8,
  BLUE      = 9,
  PURPLE    = 10,
  WHITE     = 11,
  BLACK     = 12
};

typedef enum palettes_modes palettes_modes;
palettes_modes palettes_mode = RETROWAVE;
uint8_t number_of_palettes = 13; // plus off mode
int line = 0;  // Pallete line global counter

volatile bool led_info_pin = true;        //LED indicator
