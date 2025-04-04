# KSP-Controller Capabilities Matrix

## Hardware Interfaces

| Interface | Count | Notes                          |
|-----------|-------|--------------------------------|
| GPIO      | ~30+  | Available after peripherals     |
| I2C       | 2     | I2C0 for NeoKey, RTC            |
| SPI       | 4     | Shared for SD, Ethernet         |
| UART      | 3     | One for USB-CDC, one open       |
| USB       | 1     | Supports HID, CDC, MSC          |
| ADC       | 6+    | Analog for pots/sliders         |

## Software Features

| Feature          | Library Used            | Notes                                |
|------------------|--------------------------|--------------------------------------|
| USB HID          | Adafruit TinyUSB         | Joystick/Keyboard/Gamepad            |
| CLI              | Custom Parser            | Shared across CDC, Telnet, BT Serial |
| Logging          | ArduinoLog (or custom)   | Timestamped, leveled logs            |
| Display          | Adafruit GFX + ILI9341   | Built-in TFT                         |
| SD Card          | SD or SdFat              | SPI interface                        |
| RTC              | RTClib                   | Optional battery backup              |
| NTP              | sntp.h (ESP32 native)    | Fallback from RTC                    |
| NeoPixels        | Adafruit NeoPixel        | Status or ambient feedback           |
| Bluetooth        | BluetoothSerial / NimBLE | Optional debug interface             |

---

## ❗ Design Constraints & Warnings

- **ESP32-S3 Feather Reverse TFT**: GPIO40–47 reserved for TFT. Classic Bluetooth not supported.
- **Ethernet FeatherWing** and **Adalogger FeatherWing** both use SPI — assign unique CS lines.
- **NeoKey 1x4** and **RTC** share I2C — check for address conflicts (default 0x30 for NeoKey).
- **Power Caution**: Ethernet + SD + motorized components may require power filtering and voltage regulation.
