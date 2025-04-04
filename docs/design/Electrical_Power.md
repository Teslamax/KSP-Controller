# Electrical Power
---

## 🧠 Wiring & Power Overview

This document summarizes the wiring and power distribution plan based on the ESP32-S3 Reverse Feather, Adalogger and Ethernet FeatherWings, NeoKey 1x4, motorized slide potentiometer, and an external 5V power supply.

### 🔌 Power Distribution Summary

| Source                | Voltage | Feeds                                | Notes |
|-----------------------|---------|--------------------------------------|-------|
| USB-C (PC)            | 5V      | Feather for USB CDC + HID + Charging | Connected always |
| External 5V (via diode) | 5V    | NeoPixels, H-Bridge, FeatherWings     | Use Schottky diode (SS14) to isolate |
| LiPoly Battery (optional) | 3.7V | Backup power                         | Buffers voltage dips, optional |

### 🔗 Key Connections

- `USB` pin on Feather: Connect external 5V via diode
- `NeoKey 1x4`: I2C (`SDA`, `SCL`, `5V`, `GND`)
- `Motorized Potentiometer`: Controlled via H-Bridge on GPIO 5/6
- `Slide Pot Wiper`: Connect to A0 (analog read)
- `Ethernet FeatherWing`: SPI + CS on GPIO 14
- `Adalogger FeatherWing`: SPI + CS on GPIO 10

---

## ⚡ Estimated Power Draw

| Component                 | Est. Current (mA) |
|---------------------------|-------------------|
| ESP32-S3 Feather + TFT    | ~120              |
| Ethernet FeatherWing      | ~150              |
| Adalogger FeatherWing     | ~20               |
| NeoKey 1x4 RGB (max)      | ~60               |
| Motor driver + pot        | 100–300 (peak)    |
| Joysticks / Encoders      | ~10–20            |
| **Estimated Total**       | **~400–650 mA**   |

Recommend 5V @ 1.5–2A external power source.
