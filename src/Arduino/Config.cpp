
#include "Config.h"

uint8_t currentProfile = 0;
byte ETH_MAC[6] = {0};
bool ethAvailable = false;

IPAddress STATIC_IP(192,168,1,222);
IPAddress GATEWAY(192,168,1,254);
IPAddress SUBNET(255,255,255,0);
IPAddress DNS_SERVERS[4] = {
  IPAddress(192,168,1,254),
  IPAddress(192,168,1,6),
  IPAddress(192,168,1,53),
  IPAddress(192,168,1,32)
};

const char* MDNS_HOSTNAME = "ksp-controller";

struct NetConfig configEEPROM = {};
