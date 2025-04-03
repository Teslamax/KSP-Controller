# ESP32-S3 Reverse TFT Feather (Adafruit PID 5691)

**Link**: https://www.adafruit.com/product/5691  
**MCU**: ESP32-S3 (dual-core 240 MHz, 512KB RAM + 8MB PSRAM)  
**Display**: Built-in 240x135 TFT with SPI ILI9341  
**USB**: USB-C with native USB OTG support (CDC, HID, etc.)

## GPIO Overview

- GPIO0–19, 21, 33–48: Usable for general I/O
- GPIO6: I2C SCL0 (used for QT port)
- GPIO5: I2C SDA0 (used for QT port)
- GPIO10: CS (used for Ethernet or SPI device)
- GPIO36, 35, 37: SPI (MOSI, MISO, SCK)
- GPIO21: SD Card CS (on Adalogger)

## Notes

- GPIO40–47 used for built-in TFT and are not recommended for external use.
- TFT and NeoPixel are pre-wired on board.
- Bootloader supports TinyUSB (CDC + HID).

## Libraries

- `Adafruit_TinyUSB`
- `Adafruit_GFX`, `Adafruit_ILI9341`
