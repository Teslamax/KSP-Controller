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

