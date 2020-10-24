#pragma once

#include <string>
#include <WebServer.h>

#include "rgb_server.h"
#include "led_strip.h"


void handleRoot(WebServer* server) {
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,

           "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP32 RGB Server</title>\
    <style>\
      body { background-color: #000000; font-family: Arial, Helvetica, Sans-Serif; Color: #ffffff; }\
    </style>\
  </head>\
  <body>\
    <h1>ESP32 RGB Control Server</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
  </body>\
</html>",

           hr, min % 60, sec % 60
          );
  server->send(200, "text/html", temp);
}

void handleNotFound(WebServer* server) {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";

  for (uint8_t i = 0; i < server->args(); i++) {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }
  server->send(404, "text/plain", message);

}

RGBServer::RGBServer(int port = 80) : WebServer(port) {
  on("/", [this]() { handleRoot(this); });
  onNotFound([this]() { handleNotFound(this); });
}

void RGBServer::setLedStrip(LedStrip* ledStripPtr) {
  ledStrip = ledStripPtr;
}

void RGBServer::onAnimation(const String &uri, Animatable *animationPtr) {
  on(uri, [this, animationPtr]() {
    this->ledStrip->setCurrentAnimation(animationPtr);
    this->ledStrip->turnOn();
    this->send(200, "text/plain", "OK");
  });
}
