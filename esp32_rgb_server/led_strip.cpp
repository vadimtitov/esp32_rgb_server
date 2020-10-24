#include "led_strip.h"
#include "config.h"


LedStrip::LedStrip() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
}

void LedStrip::setCurrentAnimation(Animatable *animationPtr) {
  currentAnimation = animationPtr;
}

void LedStrip::turnOn(){
  active = true;
}

void LedStrip::turnOff() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  active = false;
}

void LedStrip::handleAnimation() {
  if (active) {
    currentAnimation->animate(leds);
  } else {}
}
