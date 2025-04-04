# ESP32-S3 Reverse TFT Feather (Adafruit PID 5691)

**Link**: https://www.adafruit.com/product/5691  
**MCU**: ESP32-S3 (dual-core 240 MHz, 512KB RAM + 8MB PSRAM)  
**Display**: Built-in 240x135 TFT with SPI ILI9341  
**USB**: USB-C with native USB OTG support (CDC, HID, etc.)

## GPIO Overview

| GPIO | Pin # | Notes |
|---|---|---|
| `00`-`19` | | Usable for general I/O|
| `21` | | Usable for general I/O|
| `33`-`48` | | Usable for general I/O|
| `06` | | `SCL0` (used for QT port) |
| `05` | | `SDA0` (used for QT port) |
| `10` | | `CS` (used for Ethernet or `SPI` device) |
| `36` | | `SPI`:`MOSI` |
| `35` | | `SPI`:`MISO`|
| `37` | | `SPI`:`SCK`|
| `21` | | SD Card `CS` (on Adalogger) |
| `40`-`47` | | built-in TFT |

## Notes

- GPIO40–47 used for built-in TFT and are not recommended for external use.
- TFT and NeoPixel are pre-wired on board.
- Bootloader supports TinyUSB (CDC + HID).

## Libraries

- `Adafruit_TinyUSB`
- `Adafruit_GFX`, `Adafruit_ILI9341`

## ❗ Technical Limitations & Notes

- 🚫 Does **not** support Classic Bluetooth — only BLE is available.
- ⚠️ GPIO40–47 are reserved for the built-in TFT display and **should not be used for external peripherals**.
- ⚠️ ESP32-S3 has **fewer ADC channels** than the standard ESP32. Plan analog inputs accordingly.
- ✅ Native USB supports **CDC, HID, and Mass Storage** via TinyUSB.
