// KSP_Network.cpp
// Handles network config, Ethernet, mDNS, and NTP

#include "KSP_Network.h"
#include "KSP_Display.h"
#include <EEPROM.h>
#include <ESPmDNS.h>
#include <Ethernet.h>
#include <time.h>

extern File logFile;
extern EthernetClient netClient;
extern const char* MDNS_HOSTNAME;
extern IPAddress STATIC_IP, GATEWAY, SUBNET;
extern IPAddress DNS_SERVERS[4];
extern byte ETH_MAC[6];
extern RTC_DS3231 rtc;
extern bool sdAvailable, ethAvailable, rtcAvailable;
extern struct NetConfig configEEPROM;

void initNetwork() {
  if (ETH_MAC[0] == 0 && ETH_MAC[1] == 0) {
    memcpy(ETH_MAC, configEEPROM.mac, 6);
  }
  if (ETH_MAC[0] == 0 && ETH_MAC[1] == 0) {
    esp_read_mac(ETH_MAC, ESP_MAC_ETH);
  }

  Ethernet.init(5); // ETH_CS
  if (configEEPROM.forceStatic) {
    Ethernet.begin(ETH_MAC, configEEPROM.ip, configEEPROM.dns, configEEPROM.gateway, SUBNET);
    ethAvailable = true;
    log("Static IP from EEPROM");
  } else if (Ethernet.begin(ETH_MAC, 5000)) {
    ethAvailable = true;
    log("DHCP OK");
  } else {
    Ethernet.begin(ETH_MAC, STATIC_IP, DNS_SERVERS[0], GATEWAY, SUBNET);
    ethAvailable = true;
    log("DHCP fail, fallback");
  }

  if (ethAvailable && MDNS.begin(MDNS_HOSTNAME)) {
    log("mDNS OK");
  }

  configTime(0, 0, "pool.ntp.org", "time.nist.gov", "time.google.com");
  log("NTP OK");
}

void loadEEPROMConfig() {
  EEPROM.begin(sizeof(NetConfig));
  EEPROM.get(0, configEEPROM);
}

void saveEEPROMConfig() {
  EEPROM.put(0, configEEPROM);
  EEPROM.commit();
}
