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
