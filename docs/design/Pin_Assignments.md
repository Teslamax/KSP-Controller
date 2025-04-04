
# 📌 Pin Assignments
This document lists the pin assignments for the ESP32-S3 Reverse TFT Feather and attached peripherals.

## Hardware Interfaces

| Function                  | Pin        | Notes                      |
|---------------------------|------------|----------------------------|
| SDA / I2C Data            | GPIO 2     | NeoKey 1x4                |
| SCL / I2C Clock           | GPIO 1     | NeoKey 1x4                |
| SPI MOSI                  | GPIO 35    | Shared                     |
| SPI MISO                  | GPIO 37    | Shared                     |
| SPI CLK                   | GPIO 36    | Shared                     |
| SD CS (Adalogger)         | GPIO 10    | Default                    |
| Ethernet CS               | GPIO 14    | Jumper-set                |
| Motor A-1A                | GPIO 5     | PWM                        |
| Motor A-1B                | GPIO 6     | PWM                        |
| Slide Pot Wiper           | GPIO A0    | Analog                     |

---

| Interface | Count | Notes                          |
|-----------|-------|--------------------------------|
| GPIO      | ~30+  | Available after peripherals     |
| I2C       | 2     | I2C0 for NeoKey, RTC            |
| SPI       | 4     | Shared for SD, Ethernet         |
| UART      | 3     | One for USB-CDC, one open       |
| USB       | 1     | Supports HID, CDC, MSC          |
| ADC       | 6+    | Analog for pots/sliders         |

---


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

