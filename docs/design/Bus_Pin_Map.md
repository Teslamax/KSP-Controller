
# 🧩 Bus & Pin Assignment Map — KSP Controller

This document provides a comprehensive, verified map of all microcontroller pin assignments, I2C addresses, SPI CS lines, and GPIO roles for the ESP32-S3 Reverse TFT Feather-based KSP controller build.

---

## 📚 Microcontroller Platform

- **MCU**: ESP32-S3 Reverse TFT Feather (Adafruit #5691)
- **Logic Level**: 3.3V
- **Default Buses**:
  - **I2C**: SDA = GPIO 2, SCL = GPIO 1
  - **SPI**: MOSI = GPIO 35, MISO = GPIO 37, SCK = GPIO 36

---

## 🔗 I2C Devices

| Device            | I2C Address | Notes                                |
|------------------|-------------|--------------------------------------|
| NeoKey 1x4 QT    | 0x30 (default) | Address changeable via solder jumpers |
| RTC (Adalogger)  | 0x68        | PCF8523, fixed                       |

---

## 📀 SPI Devices

| Device                 | CS Pin | Notes                                      |
|------------------------|--------|--------------------------------------------|
| Adalogger SD Card      | GPIO 10 | Default, per FeatherWing                   |
| WIZnet Ethernet        | GPIO 14 | Requires cutting jumper & reassigning      |

**Shared SPI Pins (ESP32-S3 Reverse TFT Feather)**:
- MOSI = GPIO 35  
- MISO = GPIO 37  
- CLK = GPIO 36  

---

## 🎮 Analog / GPIO Inputs

| Function                   | GPIO   | Type   | Notes                          |
|----------------------------|--------|--------|--------------------------------|
| Slide Potentiometer (Wiper)| A0     | Analog | Reads throttle position        |
| Joystick Axes              | A1–A3  | Analog | X/Y or other axes              |
| NeoKey Interrupt (opt.)    | Any    | GPIO   | Optional INT if supported      |

---

## ⚙️ Motor Driver (L9110H)

| Function | GPIO  | Notes                     |
|----------|--------|---------------------------|
| Motor A-1A | GPIO 5 | PWM throttle forward     |
| Motor A-1B | GPIO 6 | PWM throttle reverse     |

---

## 💡 NeoPixels

| Device         | Power | Notes                                  |
|----------------|-------|----------------------------------------|
| NeoKey 1x4     | 5V    | RGB under keys, modest current draw     |
| Additional Buttons | 5V | Estimated separately                   |

---

## 🪫 Power Distribution Summary

| Source         | Voltage | Destination                     | Notes                                      |
|----------------|---------|----------------------------------|--------------------------------------------|
| USB-C (PC)     | 5V      | Feather logic + charging         | Required for HID / CDC USB connection      |
| Ext. 5V Supply | 5V      | NeoPixels, motor, Feather USB pin| Through Schottky diode (SS14 recommended)  |
| LiPoly Battery | 3.7V    | Optional buffer power            | Via JST-PH jack                            |

---

## ⚠️ Notes

- Ensure FeatherWing CS conflicts are resolved: Ethernet default is **GPIO 10**, must be **cut and reassigned** (e.g. to GPIO 14)
- Avoid direct 5V into 3.3V-only GPIOs
- All grounds must be tied together
