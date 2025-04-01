# KSP Controller Project (ESP32-S3 Reverse TFT Feather)

## Overview
This project implements a USB-HID and network-connected controller for Kerbal Space Program (KSP), built on the Adafruit ESP32-S3 Reverse TFT Feather board. It is designed to support:

- USB HID keyboard emulation
- Multiple button profiles and LED indicators
- Real-time clock logging
- Ethernet (wired) networking
- SD logging and configuration
- OLED/TFT display output (optional)
- Future plans for joystick/gamepad HID and Simpit serial integration

## Hardware Platform
- **Board:** Adafruit ESP32-S3 Reverse TFT Feather
- **Display:** 240x135 ST7789 TFT
- **Input Devices:** Adafruit NeoKey (seesaw-based), GPIO buttons (D1, D2)
- **Output Devices:** NeoPixel RGB LEDs (4), TFT screen
- **Storage:** microSD (via SD_CS)
- **Networking:** Ethernet with MAC from EEPROM/SD/ESP
- **Timekeeping:** RTC (DS3231)

## USB Device Capabilities
**Status: Incomplete / Not Yet Tested**
- CDC: USB serial logging/debugging (`SerialDebug`)
- HID: USB Keyboard HID with selectable profile support
- HID: (Planned) USB Gamepad/Joystick HID with 6DOF + throttle
- CDC: (Planned) Simpit serial interface for KSP Simpit mod

## Networking Capabilities
**Status: Incomplete / Not Yet Tested**
- DHCP + static IP fallback from SD/EEPROM
- DNS server list set from local network
- mDNS advertisement
- NTP-based clock synchronization

## Storage and Logging
**Status: Incomplete / Not Yet Tested**
- SD read support for network configuration
- Logging via serial and optionally to SD

## Display Output
**Status: Incomplete / Not Yet Tested**
- ST7789 240x135 TFT output
- Boot info, IP address, and MAC display

## Button/Keypad Input
**Status: Incomplete / Not Yet Tested**
- 4-key NeoKey matrix (seesaw)
- 2 dedicated GPIO buttons for profile switching
- RGB feedback based on current profile

## EEPROM
**Status: Incomplete / Not Yet Tested**
- Profile saved/restored across reboots
- MAC address fallback

## Compilation Environment
- **ESP32 board package:** 2.0.10 (Arduino-esp32 core)
- **TinyUSB:** Built-in (TinyUSB-OTG mode selected)
- **Arduino IDE:** Currently used, open to PlatformIO/CLI

### Important USB Header Note
- On ESP32-S3, **you must use** `#include "USB.h"` (with double quotes) instead of `<USB.h>`. This ensures the correct built-in TinyUSB support from the ESP32 Arduino core is used and avoids conflicts with external TinyUSB libraries like Adafruit_TinyUSB.

## Future Plans
- [ ] Dual CDC (Simultaneous debug + Simpit Serial)
- [ ] USB Gamepad HID descriptor with 6-axis + throttle support
- [ ] Bluetooth Serial Logging fallback
- [ ] TCP/IP logging stream over Ethernet
- [ ] USB MIDI support for alternate input interface
- [ ] OLED fallback for reduced builds

---
*This README is automatically synced with ChatGPT memory. Changes can be made manually, but ChatGPT can also update it upon request.*
