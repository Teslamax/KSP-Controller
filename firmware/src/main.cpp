// PlatformIO project: KSP Controller Starter
// Target Board: Adafruit ESP32-S3 Reverse TFT Feather (PID: 5691)

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_NeoKey_1x4.h>
#include <Ethernet.h>
#include <MDNS.h>
#include <HID-Project.h>  // Arduino HID Project (via PlatformIO registry or local lib)

// TFT display
#define TFT_CS    5
#define TFT_DC    6
#define TFT_RST   7
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// NeoKey I2C keypad
Adafruit_NeoKey_1x4 neokey(0x30);

// Ethernet (W5500)
#define ETH_CS 10
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);

// Rotary encoder pins (mock support)
#define ENCODER_PIN_A 8
#define ENCODER_PIN_B 9
volatile int encoderPos = 0;

// Menu state
int menuIndex = 0;
const char* menuItems[] = {
  "Throttle: 50%",
  "SAS: Stability",
  "Gear: Up",
  "RCS: Off"
};
const int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

void drawMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  for (int i = 0; i < menuCount; i++) {
    if (i == menuIndex) {
      tft.setTextColor(ST77XX_YELLOW);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.setCursor(10, 10 + i * 15);
    tft.print(menuItems[i]);
  }
}

void IRAM_ATTR onEncoderChange() {
  // Simple encoder logic placeholder
  encoderPos++;
  menuIndex = (menuIndex + 1) % menuCount;
  drawMenu();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("KSP Controller: Booting...");

  // Display setup
  tft.init(135, 240);
  tft.setRotation(3);
  drawMenu();

  // NeoKey
  if (!neokey.begin()) {
    Serial.println("NeoKey not found!");
  } else {
    Serial.println("NeoKey ready.");
    neokey.pixels.setBrightness(40);
    neokey.pixels.fill(0x0000FF);
    neokey.pixels.show();
  }

  // Ethernet
  Ethernet.init(ETH_CS);
  Ethernet.begin(mac, ip);
  delay(1000);
  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());

  // mDNS setup
  if (MDNS.begin("ksp-controller")) {
    Serial.println("mDNS responder started: http://ksp-controller.local/");
  }

  // Rotary encoder (mock support)
  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), onEncoderChange, CHANGE);

  // USB HID (placeholder)
  // Keyboard.begin(); // Enable when using HID Project
}

void loop() {
  MDNS.update();

  // NeoKey input check
  static uint32_t lastPoll = 0;
  if (millis() - lastPoll > 100) {
    lastPoll = millis();
    for (uint8_t i = 0; i < 4; i++) {
      if (neokey.isPressed(i)) {
        Serial.print("Key "); Serial.print(i); Serial.println(" pressed");
        neokey.pixels.setPixelColor(i, 0x00FF00);
        neokey.pixels.show();
        tft.setCursor(10, 90);
        tft.setTextColor(ST77XX_GREEN);
        tft.print("Key ");
        tft.print(i);
        tft.println(" pressed");
      } else {
        neokey.pixels.setPixelColor(i, 0x0000FF);
        neokey.pixels.show();
      }
    }
  }
}
