#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "net_config.h"

// Optional static IP settings
IPAddress localIP(192, 168, 1, 42);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(1, 1, 1, 1);

// Toggle DHCP usage
#define USE_DHCP true

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Serial.println("🚀 KSP Controller Booting...");
  
  if (!SD.begin()) {
    Serial.println("⚠️ SD card failed or not present");
  } else {
    Serial.println("✅ SD card initialized");
  }

  byte mac[6];
  memcpy(mac, defaultMAC, 6);

  if (loadMACFromSD(mac)) {
    Serial.print("📦 Loaded MAC from SD: ");
    for (int i = 0; i < 6; i++) {
      Serial.print(mac[i], HEX);
      if (i < 5) Serial.print(":");
    }
    Serial.println();
  } else {
    Serial.println("ℹ️ Using default MAC address");
  }

  setupEthernet(USE_DHCP, mac, localIP, gateway, subnet, dns);
}

void loop() {
  // Placeholder loop
}
