#pragma once

#include <string>
#include <WebServer.h>

#include "led_strip.h"

void handleRoot(WebServer* server);
void handleNotFound(WebServer* server);

class RGBServer : public WebServer {
private:
  LedStrip* ledStrip;

public:
  RGBServer(int port);
  void setLedStrip(LedStrip* ledStripPtr);
  void onAnimation(const String &uri, Animatable *animationPtr);
};
