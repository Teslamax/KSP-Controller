# Feather KSP Controller

## Overview
This project implements a custom USB-based input controller for Kerbal Space Program (KSP) using an ESP32-S3 and Adafruit Feather-compatible stack. It currently supports USB HID (keyboard) and USB CDC (serial) over the ESP32-S3 native TinyUSB stack. Hardware includes display, buttons, neopixels, SD card, and Ethernet.

## Current Features
- ✅ USB HID Keyboard output (configurable keymaps and profiles)
- ✅ USB CDC Serial for debug logging via `Serial`
- ✅ Native USB mode using ESP32-S3 `USB-OTG (TinyUSB)`
- ✅ I2C-based Adafruit NeoKey input + NeoPixels for feedback
- ✅ ST7789 TFT display for UI / debugging
- ✅ SD card support for network config
- ✅ RTC for time-based log entries
- ✅ Ethernet support with fallback/static IP
- ✅ EEPROM storage for active profile persistence
- ✅ mDNS support

## Planned Features (Future)
- 🔜 USB HID Gamepad / Joystick:
  - 6-axis flight stick (roll, pitch, yaw, translation)
  - Throttle axis (7 total axes)
  - 16+ buttons (likely through multiplexing or GPIO expanders)

- 🔜 Dual USB CDC Interfaces:
  - `Serial` (already working): for debugging/logging
  - `SerialSimpit` (planned): for Kerbal Simpit Revamped protocol

- 🔜 Optional Non-USB Logging Interfaces:
  - Bluetooth SPP (Serial over Bluetooth Classic)
  - TCP-based log streaming via Ethernet

## Setup Notes
- Must select **USB-OTG (TinyUSB)** in board menu to enable USB HID + CDC
- ESP32 Board package version: **2.0.10** recommended
- HID keycodes moved to: `HID_Keycodes.h`

## File Structure
- `feather_ksp_stack.ino` — main logic for controller
- `HID_Keycodes.h` — USB HID key definitions for keyboard

## Known Issues
- Only one CDC port currently supported (limitation of USB descriptor config)
- No joystick HID descriptors active yet (stub planned)
- Adafruit_TinyUSB_Library not used — ESP32-S3 uses built-in TinyUSB stack

## Notes for Developers
When modifying USB descriptors (e.g., to add gamepad or dual CDC), review `usb_desc.c` behavior or leverage `USBHIDDevice` and `USBCDC` directly. Make sure to adjust `USBMode` and confirm with device enumeration.

## Credits
- Uses Adafruit hardware and libraries
- Based on Kerbal Simpit and general USB HID documentation

---

# KSP Controller on Adafruit ESP32-S3 Reverse TFT Feather

This project is a custom controller for *Kerbal Space Program* (KSP), designed around the **Adafruit ESP32-S3 Reverse TFT Feather**. It combines:

- USB HID input (keyboard and gamepad-style joystick)
- Dual USB CDC ports (debug console + KSP Simpit)
- Rotary encoders, mechanical switches, RGB backlit keys
- SD logging, Ethernet, RTC, and TFT display

## Current Status (as of April 1, 2025)

✅ Keyboard HID is implemented with basic support for 4 NeoKey inputs.  
⚠️ Joystick HID descriptor stub present, not active yet.  
⚠️ CDC Simpit interface not yet implemented.  
⚠️ Auto-calibration & motorized throttle support planned, not implemented.  

## HID Plan

- **Keyboard HID**: Custom keymaps with profile switching
- **Joystick HID** (planned):
  - 6 analog axes: Pitch, Roll, Yaw, Translate X/Y/Z
  - 1 analog throttle slider (motorized)
  - 1 hat switch (POV)
  - Up to 32 digital buttons

## CDC Plan

- `SerialDebug`: USB CDC port for log/debug output
- `SerialSimpit`: USB CDC port for Simpit mod in KSP *(future)*

## I/O & Peripherals

| Feature         | Module               |
|----------------|----------------------|
| Display        | ST7789 TFT           |
| SD Card        | microSD on SPI       |
| Ethernet       | W5500 (SPI)          |
| RTC            | DS3231               |
| Buttons        | GPIO + NeoKey (I2C)  |
| LEDs           | NeoPixel RGB (I2C)   |
| Storage        | EEPROM for profile   |
| USB HID        | Native TinyUSB API   |

## Requirements

- Arduino IDE or PlatformIO
- ESP32 board support (>= 2.0.10)
- Libraries:
  - Adafruit GFX, ST7789, BusIO, NeoPixel, Seesaw
  - ArduinoJson, Ethernet, SD
  - RTClib, EEPROM, ESPmDNS

## Building

Select the board: `Adafruit ESP32-S3 Reverse TFT Feather`  
USB Mode: `USB-OTG (TinyUSB)`

**Note on USB Header:**
Use `#include "USB.h"` (with quotes) instead of angle brackets. This ensures the correct ESP32-S3 core internal USB header is used and avoids conflicts with external TinyUSB libraries.

Then compile and upload normally via Arduino IDE or PlatformIO.

---

> For more information or future updates, check the `checklist.md` for test status or development tracking.

