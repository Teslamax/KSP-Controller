# KSP Controller Functional Test Checklist

This checklist helps validate individual hardware and software features of the KSP Controller project based on the ESP32-S3 Reverse TFT Feather board.

## General Instructions
- Flash the current build to the device
- Confirm each function in isolation where possible
- Mark the tested result with ✅ (working), ⚠️ (partially working), ❌ (not working)
- Add notes as needed for troubleshooting or retesting

---

## USB Interfaces
- [ ] **CDC Debug Serial (SerialDebug)** — Confirm appearance as USB serial device and output during boot
- [ ] **USB Keyboard HID** — Verify keypresses from NeoKey result in input on host system
- [ ] **USB Gamepad HID (stub only)** — Confirm enumeration (no test needed yet)
- [ ] **(Planned) CDC Simpit Serial** — Not implemented yet

## Input Devices
- [ ] **NeoKey 4-key detection** — Press each key and verify feedback (USB or visual)
- [ ] **Button D1 (Profile +)** — Confirm profile increment and color change
- [ ] **Button D2 (Profile -)** — Confirm profile decrement and color change

## Output Devices
- [ ] **NeoPixel RGB Feedback** — Check colors match profiles
- [ ] **ST7789 TFT Screen** — Confirm display initializes and text is visible
  - [ ] Profile Name
  - [ ] MAC Address
  - [ ] Log messages

## Storage & Logging
- [ ] **microSD Card Mount** — Card is detected, files can be opened
- [ ] **Read /network.json** — Confirm MAC address override from SD
- [ ] **Logging to SerialDebug** — Ensure log messages appear

## Networking
- [ ] **Ethernet Init with MAC** — MAC comes from EEPROM, SD, or fallback
- [ ] **DHCP Works** — IP obtained from router
- [ ] **Static IP Fallback** — Used when DHCP fails
- [ ] **mDNS Hostname** — Accessible via `ksp-controller.local`
- [ ] **NTP Sync** — Log timestamp matches network time

## EEPROM
- [ ] **MAC Storage** — Written and read correctly
- [ ] **Profile Restore on Boot** — Profile persists across resets

## Notes
_(Add any test-related issues, reboots, freezes, or debug print anomalies here)_

---
*This checklist is synced with the README and development goals.*
