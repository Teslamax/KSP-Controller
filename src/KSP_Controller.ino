// feather_ksp_stack.ino (clean version - ESP32-S3 native USB with TinyUSB HID + CDC support)
// NOTE: This version uses the ESP32-S3 native TinyUSB stack.
// HID keycodes are defined inline for compatibility (see #define HID_KEY_*). No Adafruit_TinyUSB.h is required.
// Future plans: add joystick/gamepad HID reports + Simpit serial support.

#include <esp_system.h>
#include <esp_mac.h>
#include <esp_wifi.h>
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
#include <time.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
// Removed: #include <Adafruit_TinyUSB.h>  // Not needed with native ESP32-S3 stack

// Basic HID key definitions (USB HID Usage Tables)
#define HID_KEY_A 0x04
#define HID_KEY_B 0x05
#define HID_KEY_C 0x06
#define HID_KEY_D 0x07
#define HID_KEY_E 0x08
#define HID_KEY_F 0x09
#define HID_KEY_G 0x0A
#define HID_KEY_H 0x0B
#define HID_KEY_Q 0x14
#define HID_KEY_R 0x15
#define HID_KEY_S 0x16
#define HID_KEY_T 0x17
#define HID_KEY_W 0x1A
#define HID_KEY_X 0x1B
#define HID_KEY_Y 0x1C
#define HID_KEY_Z 0x1D
#define HID_KEY_1 0x1E
#define HID_KEY_2 0x1F
#define HID_KEY_3 0x20
#define HID_KEY_4 0x21
#define HID_KEY_5 0x22
#define HID_KEY_6 0x23

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
  IPAddress(192, 168, 1, 6),
  IPAddress(192, 168, 1, 53),
  IPAddress(192, 168, 1, 32)
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
Adafruit_USBD_HID usb_hid;

static const uint8_t desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

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

// ... remainder of the code unchanged

// definitions done

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

void setup() {
  SerialDebug.begin(115200);
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
  if (ETH_MAC[0] == 0 && ETH_MAC[1] == 0) esp_read_mac(ETH_MAC, ESP_MAC_ETH);

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
  if (pressed) report[2] = keycode;
  usb_hid.sendReport(0, report, sizeof(report));
}

void loop() {
  if (neokeyAvailable) {
    uint32_t buttons = neokey.digitalReadBulk(0x0F);
    for (int i = 0; i < 4; i++) {
      bool pressed = !(buttons & (1 << i));
      if (pressed != buttonState[i]) {
        buttonState[i] = pressed;
        sendKey(keymap[i], pressed);
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
