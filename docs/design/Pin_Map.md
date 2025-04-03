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

