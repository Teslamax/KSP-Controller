
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
#include <Ethernet.h>

extern uint8_t currentProfile;
extern byte ETH_MAC[6];
extern bool ethAvailable;

extern IPAddress STATIC_IP;
extern IPAddress GATEWAY;
extern IPAddress SUBNET;
extern IPAddress DNS_SERVERS[4];

extern const char* MDNS_HOSTNAME;

struct NetConfig {
  uint8_t profile;
  bool useStatic;
  bool hasStaticIP;
  IPAddress ip;
  IPAddress gateway;
  IPAddress dns;
  byte mac[6];
  bool forceStatic;
};

extern struct NetConfig configEEPROM;

#endif
