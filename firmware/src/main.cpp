#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include <EthernetBonjour.h>  // You can use MDNSResponder or EthernetBonjour
#include "net_config.h"

// IP configuration fallback values
IPAddress localIP(192, 168, 1, 42);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(1, 1, 1, 1);

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
  bool useDHCP = USE_DHCP;

  // Load config.json and possibly override MAC and DHCP
  loadNetworkConfig(useDHCP, mac, localIP, gateway, subnet, dns);

  // Check for MAC override from SD file
  loadMACFromSD(mac);

  // Set up Ethernet using values from config
  setupEthernet(useDHCP, mac, localIP, gateway, subnet, dns);

  // Get hostname for mDNS
  String hostname = getHostnameFromConfig();
  Serial.print("🌐 Hostname: ");
  Serial.println(hostname);

  if (EthernetBonjour.begin(hostname.c_str())) {
    Serial.println("✅ mDNS responder started");
  } else {
    Serial.println("⚠️ Failed to start mDNS");
  }
}

void loop() {
  EthernetBonjour.run(); // Keeps mDNS active
}
