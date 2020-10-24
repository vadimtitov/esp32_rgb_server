/*
ESP32 web server that allows to control individually addressable
LED strip with different FastLED library based animations.
*/

#include "wifi.h"
#include "rgb_server.h"
#include "led_strip.h"
#include "animations.h"
#include "config.h"

RGBServer server(80);
LedStrip ledStrip;

// animations
Rainbow rainbow;
Fire fire;


void setup(void) {
  Serial.begin(115200);
  connectWiFi();
  server.setLedStrip(&ledStrip);

  // set animations
  server.onAnimation("/rainbow", &rainbow);
  server.onAnimation("/fire", &fire);

  // set on/off functions
  server.on("/on", []() {
    ledStrip.turnOn();
    server.send(200, "text/plain", "ok");
  });
  server.on("/off", []() {
    ledStrip.turnOff();
    server.send(200, "text/plain", "ok");
  });

  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
  ledStrip.handleAnimation();
}
