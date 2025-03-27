# 📌 GPIO Pinout & BOM for KSP Controller

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

---

## 🧾 Bill of Materials (Phase 1 Dev Setup)

| **Component**                                | **Qty** | **Product ID / Link**                             | **Notes**                                |
|---------------------------------------------|--------|--------------------------------------------------|------------------------------------------|
| ESP32-S3 Reverse TFT Feather                 | 1      | [Adafruit 5691](https://www.adafruit.com/product/5691) | Main MCU with display                     |
| Ethernet FeatherWing (W5500)                | 1      | [Adafruit 3201](https://www.adafruit.com/product/3201) | Optional wired networking                 |
| NeoKey 1x4 QT I2C Mechanical Keypad         | 1      | [Adafruit 4980](https://www.adafruit.com/product/4980) | Input + RGB feedback                      |
| FeatherWing Doubler                         | 1      | [Adafruit 2890](https://www.adafruit.com/product/2890) | Side-by-side stacking                     |
| Feather Stacking Headers                    | 1      | [Adafruit 2830](https://www.adafruit.com/product/2830) | For stacking Feather and Wings           |
| Breadboard Kit                              | 1      | Bojack (Amazon, X002TQ7ITZ)                      | Jumper wires, breadboard, accessories     |
| USB-C Cable                                 | 1      | Any USB-C cable supporting data                 | For programming and power                 |

> 💡 Add tactile buttons, rotary encoder, or OLED later as needed.
