#pragma once

#include <FastLED.h>

#include "led_strip.h"
#include "config.h"


class Animatable {
public:
  virtual void animate(CRGB leds[NUM_LEDS]) = 0;
};

class Rainbow : public Animatable {
public:
  void animate(CRGB leds[NUM_LEDS]) override;
};

class Fire : public Animatable {
public:
  void animate(CRGB leds[NUM_LEDS]) override;
};
