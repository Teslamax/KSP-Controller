#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

// Default MAC Address (Locally Administered Address)
byte defaultMAC[6] = { 0x02, 0x42, 0xAC, 0x00, 0x00, 0x01 };

// Parse config.json and fill network settings
bool loadNetworkConfig(bool &useDHCP, byte* mac, IPAddress &localIP, IPAddress &gateway, IPAddress &subnet, IPAddress &dns) {
  File configFile = SD.open("/config/config.json");
  if (!configFile) {
    Serial.println("⚠️ config.json not found, using defaults");
    memcpy(mac, defaultMAC, 6);
    useDHCP = true;
    return false;
  }

  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, configFile);
  configFile.close();

  if (error) {
    Serial.println("⚠️ Failed to parse config.json");
    return false;
  }

  // Load MAC
  bool overrideMAC = doc["device"]["mac_override"] | false;
  useDHCP = doc["device"]["use_dhcp"] | true;

  if (overrideMAC && doc["device"]["default_mac"].is<JsonArray>()) {
    JsonArray macArray = doc["device"]["default_mac"];
    for (int i = 0; i < 6; i++) {
      mac[i] = macArray[i] | defaultMAC[i];
    }
  } else {
    memcpy(mac, defaultMAC, 6);
  }

  // Load Static IP (if DHCP disabled)
  if (!useDHCP) {
    localIP.fromString(doc["network"]["static_ip"] | "192.168.1.42");
    gateway.fromString(doc["network"]["gateway"] | "192.168.1.1");
    subnet.fromString(doc["network"]["subnet"] | "255.255.255.0");
    dns.fromString(doc["network"]["dns"] | "1.1.1.1");
  }

  return true;
}

// Attempt to load MAC from mac.txt, otherwise save default MAC to SD
bool loadMACFromSD(byte* mac) {
  File file = SD.open("/config/mac.txt");
  if (!file) {
    Serial.println("ℹ️ mac.txt not found. Writing default.");
    SD.mkdir("/config");
    file = SD.open("/config/mac.txt", FILE_WRITE);
    if (file) {
      for (int i = 0; i < 6; i++) {
        file.print(mac[i], HEX);
        if (i < 5) file.print(":");
      }
      file.println();
      file.close();
    }
    return false;
  }

  String macString = file.readStringUntil('\n');
  file.close();

  macString.replace("0x", "");
  macString.replace(":", ",");
  macString.trim();

  int idx = 0;
  for (int i = 0; i < 6; i++) {
    int comma = macString.indexOf(",", idx);
    String hexByte = (comma == -1) ? macString.substring(idx) : macString.substring(idx, comma);
    mac[i] = strtoul(hexByte.c_str(), NULL, 16);
    idx = comma + 1;
  }

  return true;
}

// Initialize Ethernet with DHCP or Static IP
void setupEthernet(bool useDHCP, byte* mac, IPAddress localIP, IPAddress gateway, IPAddress subnet, IPAddress dns) {
  Serial.print(F("🔌 Initializing Ethernet... "));
  if (useDHCP) {
    Ethernet.begin(mac);
    Serial.println(F("using DHCP"));
  } else {
    Ethernet.begin(mac, localIP, dns, gateway, subnet);
    Serial.println(F("using static IP"));
  }

  Serial.print(F("🟢 Device IP: "));
  Serial.println(Ethernet.localIP());
}


// Returns a hostname string from config or default
String getHostnameFromConfig() {
  File configFile = SD.open("/config/config.json");
  if (!configFile) {
    return "ksp-controller";
  }

  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, configFile);
  configFile.close();

  if (error || !doc["device"]["hostname"]) {
    return "ksp-controller";
  }

  return String((const char*)doc["device"]["hostname"]);
}
