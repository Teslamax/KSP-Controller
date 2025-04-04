# 🛠 ESP32-S3 Reverse TFT Feather – Recovery Files

Factory reset firmware for Adafruit ESP32-S3 Reverse TFT Feather.

## 📄 Files

- `Adafruit_ESP32-S3_Reverse_TFT_Feather_Factory_Reset.uf2`: UF2 bootloader format (drag-and-drop)
- `Adafruit_ESP32-S3_Reverse_TFT_Feather_Factory_Reset.bin`: Raw binary for `esptool.py`

## 🔧 Flash Instructions

### Method 1: UF2 (Recommended)
1. Double-tap the RESET button on the Feather.
2. It will mount as a drive named `FEATHERBOOT`.
3. Drag and drop the `.uf2` file onto the drive.

### Method 2: esptool (Advanced)
```bash
esptool.py --chip esp32s3 --port /dev/ttyUSB0 write_flash 0x0 Adafruit_ESP32-S3_Reverse_TFT_Feather_Factory_Reset.bin
```

## 🔍 Source
From Adafruit Learn Guide:  
https://learn.adafruit.com/esp32-s3-reverse-tft-feather

