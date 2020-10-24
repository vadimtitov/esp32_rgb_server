#pragma once

#include <FastLED.h>

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    13  // ESP32 data pin
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    50  // number of LEDs in your strip
#define BRIGHTNESS  255

#define SSID_       "your wifi SSID"
#define PASSWORD    "you wifi password"
