#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#define SD_CS    10
#define ETH_CS   5
#define TFT_CS   9
#define TFT_DC   7
#define TFT_RST  6
#define NEOKEY_ADDR 0x30
#define BUTTON_PIN_1 1
#define BUTTON_PIN_2 2

extern uint8_t currentProfile;
extern Adafruit_NeoPixel neopixels;
extern const uint32_t profileColors[4];

#endif
