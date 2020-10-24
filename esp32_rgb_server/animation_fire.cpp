#pragma once

#include <FastLED.h>

#include "led_strip.h"
#include "animations.h"
#include "config.h"

#define FRAMES_PER_SECOND_FIRE 60
#define COLLING_FIRE  55
#define SPARKING_FIRE 120

bool gReverseDirection = false;
CRGBPalette16 gPal = HeatColors_p;


void Fire::animate(CRGB leds[NUM_LEDS]) {
  random16_add_entropy( random(0, 1) );

  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COLLING_FIRE * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if( random8() < SPARKING_FIRE ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160,255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette( gPal, colorindex);
    int pixelnumber;
    if( gReverseDirection ) {
      pixelnumber = (NUM_LEDS-1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND_FIRE);
}
