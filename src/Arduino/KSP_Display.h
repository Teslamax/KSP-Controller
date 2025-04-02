// KSP_Display.h
// Handles display setup and log output for KSP controller

#pragma once

#include <Arduino.h>
#include <Adafruit_ST7789.h>

// External declarations
extern Adafruit_ST7789 tft;
extern bool tftAvailable;

// Log function declaration
void log(String msg);
