# KSP-Controller Pin Map

This document lists the pin assignments for the ESP32-S3 Reverse TFT Feather and attached peripherals.

| Function            | Pin         | Notes                              |
|---------------------|-------------|------------------------------------|
| TFT Display (built-in) | GPIO40-47 | Managed by board definition        |
| NeoKey I2C (QT)     | GPIO6 (SCL), GPIO5 (SDA) | Uses I2C0                        |
| Adalogger (RTC + SD)| SPI (GPIO36/35/37), GPIO21 | SPI interface + optional I2C   |
| Ethernet FeatherWing| SPI Shared, CS=GPIO10     | SPI w/ separate CS               |
| NeoPixel            | GPIO48      | Can be re-assigned if needed       |
| D0, D1, D2 Buttons  | GPIO0, GPIO1, GPIO2       | Digital inputs w/ pullups        |
| Encoder A/B/SW      | TBD         | Will require 3 GPIOs               |
| Analog Inputs       | TBD         | For sliders/pots                   |

---

## 📋 Annotated Pinout Notes (from pinout.md)

# 📌 GPIO Pinout

## 🧠 ESP32-S3 Feather (Adafruit 5691) — GPIO Pin Usage

| **Function**         | **GPIO Pin** | **Notes**                          |
|----------------------|--------------|------------------------------------|
| Built-in TFT CS      | GPIO 5       | ST7789 SPI Chip Select             |
| TFT DC               | GPIO 6       | Data/Command                       |
| TFT RST              | GPIO 7       | Reset                              |
| SPI MOSI             | GPIO 35      | Shared with display & Ethernet     |
| SPI SCK              | GPIO 36      | Shared with display & Ethernet     |
| SPI MISO             | GPIO 37      | Used by Ethernet only              |
| Ethernet CS          | GPIO 10      | W5500 SPI Chip Select              |
| I2C SDA              | GPIO 3       | Used by NeoKey QT                  |
| I2C SCL              | GPIO 4       | Used by NeoKey QT                  |
| NeoKey INT (optional)| -            | Not needed unless interrupts used  |
| Available GPIOs      | GPIO 8–20+   | For buttons, encoders, LEDs        |