#pragma once

#include <FastLED.h>

#include "animations.h"
#include "config.h"


class LedStrip {
private:
  Animatable* currentAnimation;
  CRGB leds[NUM_LEDS];
  bool active = false;

public:
  LedStrip();
  void setCurrentAnimation(Animatable *animationPtr);
  void turnOn();
  void turnOff();
  void handleAnimation();
};
