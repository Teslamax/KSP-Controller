# Build Instructions

## Requirements
- ESP32 Arduino Core: 2.0.10
- Board: Adafruit ESP32-S3 Reverse TFT Feather
- USB Mode: TinyUSB-OTG

## Notes
- Use `#include "USB.h"` (not `<USB.h>`) for built-in TinyUSB.
- Do not install Adafruit_TinyUSB; it conflicts with ESP32-S3's built-in stack.
