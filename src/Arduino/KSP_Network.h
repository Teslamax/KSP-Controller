// KSP_Network.h
// Handles Ethernet, mDNS, and NTP setup for the KSP controller

#pragma once

#include <Arduino.h>
#include <Ethernet.h>
#include <RTClib.h>
#include <SD.h>

// External EEPROM config struct
struct NetConfig {
  uint8_t profile = 0;
  bool useStatic = false;
  bool hasStaticIP = false;
  IPAddress ip = IPAddress(192, 168, 1, 222);
  IPAddress gateway = IPAddress(192, 168, 1, 254);
  IPAddress dns = IPAddress(192, 168, 1, 254);
  byte mac[6] = {0};
  bool forceStatic = false;
};

// Function declarations
void initNetwork();
void loadEEPROMConfig();
void saveEEPROMConfig();
