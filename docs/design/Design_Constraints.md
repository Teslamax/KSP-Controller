# 🚧 Design Constraints Summary

This document outlines technical limitations and required precautions when integrating components in the KSP Controller project.

---

## ESP32-S3 Reverse TFT Feather
- ❌ Does not support Classic Bluetooth (BLE only)
- ⚠️ GPIO40–47 are reserved for the TFT display
- ⚠️ Limited ADC channels compared to ESP32
- ✅ Native USB supports HID, CDC, Mass Storage via TinyUSB
- Internal flash storage has supports varying wear-leveling options

## Ethernet FeatherWing
- ⚠️ Uses SPI — requires dedicated CS (e.g. GPIO10)
- ⚠️ Shared SPI bus with SD card must be coordinated
- ⚠️ May require external 3.3V regulator for stable Ethernet operation

## Adalogger FeatherWing
- ✅ RTC uses I2C (DS3231)
- ⚠️ Shares I2C bus — ensure address compatibility with other peripherals
- ⚠️ SD card also uses SPI — must not share CS with Ethernet

## NeoKey 1x4
- ⚠️ I2C default address: 0x30
- ⚠️ 3.3V or 5V power required
- ✅ Fully compatible with STEMMA QT chain

## Cross-Component Considerations
- ⚠️ SPI bus shared by multiple devices (SD, Ethernet, TFT)
- ⚠️ I2C bus shared by RTC and NeoKey (check addressing)
- ⚠️ Voltage drops and current draw may require capacitors or regulators

