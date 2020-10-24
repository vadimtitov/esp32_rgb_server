#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include "config.h"


void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_, PASSWORD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID_);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
}
