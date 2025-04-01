
// feather_ksp_stack.ino (complete version)

#include "esp_system.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Ethernet.h>
#include <Adafruit_seesaw.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_BusIO_Register.h>
#include <ESPmDNS.h>
//#include "Adafruit_TinyUSB.h"
//#include "Adafruit_USBHID.h"
//#include "Adafruit_USB_HID.h"
//using namespace arduino;
//#include "Adafruit_TinyUSB_Keyboard.h"
//#include "Adafruit_TinyUSB_ArduinoHID.h"
#include <time.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

#define SD_CS    10
#define ETH_CS   5
#define TFT_CS   9
#define TFT_DC   7
#define TFT_RST  6
#define NEOKEY_ADDR 0x30
#define BUTTON_PIN_1 1 // D1
#define BUTTON_PIN_2 2 // D2

IPAddress STATIC_IP(192, 168, 1, 222);
IPAddress GATEWAY(192, 168, 1, 254);
IPAddress SUBNET(255, 255, 255, 0);
IPAddress DNS_SERVERS[4] = {
  IPAddress(192, 168, 1, 254),
  IPAddress(1, 1, 1, 1),
  IPAddress(8, 8, 8, 8),
  IPAddress(8, 8, 4, 4)
};
byte ETH_MAC[6];
const char* MDNS_HOSTNAME = "ksp-controller";

struct NetConfig {
  uint8_t profile = 0;
  bool useStatic = false;
  bool hasStaticIP = false;
  IPAddress ip = IPAddress(192,168,1,222);
  IPAddress gateway = IPAddress(192,168,1,254);
  IPAddress dns = IPAddress(192,168,1,254);
  byte mac[6] = {0};
  bool forceStatic = false;
} configEEPROM;

RTC_DS3231 rtc;
File logFile;
EthernetClient netClient;
Adafruit_seesaw neokey;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_NeoPixel neopixels(4, NEOKEY_ADDR + 1, NEO_GRB + NEO_KHZ800);

Adafruit_USBD_CDC SerialDebug;
Adafruit_USBD_CDC SerialSimpit;

#if CFG_TUD_HID
Adafruit_USBD_HID usb_hid;

static uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};
#endif

bool rtcAvailable = false;
bool sdAvailable = false;
bool ethAvailable = false;
bool tftAvailable = false;
bool neokeyAvailable = false;

uint8_t keymap[6] = { HID_KEY_1, HID_KEY_2, HID_KEY_3, HID_KEY_4, HID_KEY_5, HID_KEY_6 };
bool buttonState[6] = {false};

uint8_t currentProfile = 0;
const char* profileNames[] = {"Profile 1", "Profile 2", "Profile 3", "Profile 4"};
uint8_t keymaps[][6] = {
  { HID_KEY_1, HID_KEY_2, HID_KEY_3, HID_KEY_4 },
  { HID_KEY_Q, HID_KEY_W, HID_KEY_E, HID_KEY_R },
  { HID_KEY_A, HID_KEY_S, HID_KEY_D, HID_KEY_F },
  { HID_KEY_Z, HID_KEY_X, HID_KEY_C, HID_KEY_V }
};
uint32_t profileColors[] = {
  neopixels.Color(0, 255, 0),
  neopixels.Color(0, 0, 255),
  neopixels.Color(255, 0, 0),
  neopixels.Color(255, 255, 0)
};
const uint8_t totalProfiles = 4;

//extern "C" void esp_read_mac(uint8_t* mac, uint32_t type);

void log(String msg) {
  time_t now = time(nullptr);
  char ts[20] = "NO_TIME";
  if (now > 100000) strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M:%S", localtime(&now));
  String line = "[" + String(ts) + "] " + msg;
  SerialDebug.println(line);
  if (tftAvailable) {
    tft.setCursor(0, 110);
    tft.fillRect(0, 110, 240, 20, ST77XX_BLACK);
    tft.print(line);
  }
}

void setProfile(uint8_t profile) {
  for (int i = 0; i < 4; i++) neopixels.setPixelColor(i, profileColors[profile]);
  neopixels.show();
  for (int i = 0; i < 6; i++) keymap[i] = keymaps[profile][i];
  EEPROM.write(0, profile);
  EEPROM.commit();
  if (tftAvailable) {
    char macStr[18];
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", ETH_MAC[0], ETH_MAC[1], ETH_MAC[2], ETH_MAC[3], ETH_MAC[4], ETH_MAC[5]);
    tft.fillRect(0, 60, 240, 40, ST77XX_BLACK);
    tft.setCursor(0, 60);
    tft.print(profileNames[profile]);
    tft.setCursor(0, 75);
    tft.print("MAC: ");
    tft.print(macStr);
  }
}

/*
Compilation Errors Breakdown 

These functions are only available if you manually create descriptors with TinyUSB.
The Adafruit_USBD_CDC class does not expose these by default in current stable Adafruit board packages.
*/

void setup() {
//  SerialDebug.setManufacturerDescriptor("Feather USB Logger");
//  SerialDebug.setProductDescriptor("Feather Debug Port");
  SerialDebug.begin(115200);
//  SerialSimpit.setManufacturerDescriptor("Feather Simpit USB");
//  SerialSimpit.setProductDescriptor("Feather Simpit Port");
  SerialSimpit.begin(115200);
  while (!SerialDebug) delay(10);

  EEPROM.begin(sizeof(NetConfig));
  EEPROM.get(0, configEEPROM);
  currentProfile = (configEEPROM.profile < totalProfiles) ? configEEPROM.profile : 0;

  log("Booting Feather KSP Stack...");

  tft.init(240, 135);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Display OK");
  tftAvailable = true;

  if (rtc.begin()) {
    if (rtc.lostPower()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    rtcAvailable = true;
    log("RTC OK");
  }

  if (SD.begin(SD_CS)) {
    sdAvailable = true;
    File netFile = SD.open("/network.json");
    if (netFile) {
      StaticJsonDocument<512> netCfg;
      if (!deserializeJson(netCfg, netFile)) {
        if (netCfg.containsKey("mac")) {
          sscanf(netCfg["mac"], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
            &ETH_MAC[0], &ETH_MAC[1], &ETH_MAC[2],
            &ETH_MAC[3], &ETH_MAC[4], &ETH_MAC[5]);
          log("MAC from SD");
        }
      }
      netFile.close();
    }
  } else {
    log("SD missing");
  }

  Ethernet.init(ETH_CS);
  if (ETH_MAC[0] == 0 && ETH_MAC[1] == 0) memcpy(ETH_MAC, configEEPROM.mac, 6);
  if (ETH_MAC[0] == 0 && ETH_MAC[1] == 0) esp_read_mac(ETH_MAC, ESP_MAC_ETH);  // ✅ Correct!

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

  if (neokey.begin(NEOKEY_ADDR)) {
    neokeyAvailable = true;
    neokey.setGPIOInterrupts(0x0F, true);
    neopixels.begin();
    setProfile(currentProfile);
    log("NeoKey OK");
  }

  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);

 

  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.setPollInterval(2);
  usb_hid.setBootProtocol(true);
  usb_hid.begin();
 
  TinyUSBDevice.begin();

}

void sendKey(uint8_t keycode, bool pressed) {
  uint8_t report[8] = { 0 };  // HID report: modifier, reserved, key[6]

  if (pressed) {
    report[2] = keycode;
  }

  usb_hid.sendReport(0, report, sizeof(report));
}


void loop() {
  if (neokeyAvailable) {
    uint32_t buttons = neokey.digitalReadBulk(0x0F);
    for (int i = 0; i < 4; i++) {
      bool pressed = !(buttons & (1 << i));
      if (pressed != buttonState[i]) {
        buttonState[i] = pressed;
        //#if CFG_TUD_HID
        if (pressed) sendKey(keymap[i], true);
        else sendKey(keymap[i], false);
        //#endif
      }
    }
  }
  bool d1 = !digitalRead(BUTTON_PIN_1);
  bool d2 = !digitalRead(BUTTON_PIN_2);
  if (d1 != buttonState[4]) {
    buttonState[4] = d1;
    if (d1) {
      currentProfile = (currentProfile + 1) % totalProfiles;
      setProfile(currentProfile);
    }
  }
  if (d2 != buttonState[5]) {
    buttonState[5] = d2;
    if (d2) {
      currentProfile = (currentProfile + totalProfiles - 1) % totalProfiles;
      setProfile(currentProfile);
    }
  }
  delay(10);
}
