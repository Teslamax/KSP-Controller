# KSP-Controller System Architecture

This document describes the modular architecture of the KSP-Controller firmware project.

## Overview

```text
+----------------------+
| User Interfaces      |  (USB CDC, Telnet, Bluetooth Serial)
+----------------------+
          |
          v
+----------------------+
| CLI Parser/Router    |  (Command dispatch and parsing logic)
+----------------------+
          |
          v
+----------------------+
| High-Level Controllers |
| - NetworkManager      |
| - ConfigManager       |
| - DisplayManager      |
| - HIDManager          |
| - LogManager          |
+----------------------+
          |
          v
+----------------------+
| Hardware Abstraction |
| - Ethernet Wrapper   |
| - TFT Display Driver |
| - Key/Encoder Input  |
| - RTC/NTP Wrapper    |
| - SD/EEPROM Layer    |
| - LED Manager        |
+----------------------+
```

Each layer should fail gracefully and allow optional components to be omitted or simulated in software.


## 🧠 ESP32-S3 Hardware Considerations

- **Wi-Fi and BLE use ADC2 internally**, so analog reads should be limited to **ADC1 pins**.
- **TFT display and buttons** occupy GPIOs D0, D3, D7, D8, D13, and D38.
- **Only BLE is supported**; **Classic Bluetooth is not available**.
- Flash memory is **4MB**; this limits use of some CircuitPython/BLE features.
- Built-in LiPoly charger and fuel gauge use I2C pins D1/D2.
