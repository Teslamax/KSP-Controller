# Adalogger FeatherWing (PID 2922)

**Link**: https://www.adafruit.com/product/2922  
**Features**:
- MicroSD slot (SPI)
- DS3231 RTC (I2C)

## Pin Usage

- SD SPI: MOSI (GPIO36), MISO (GPIO35), SCK (GPIO37), CS (GPIO21)
- RTC I2C: SDA/SCL (shared with NeoKey if using QT port)

## Notes

- Battery backup for RTC (CR1220)
- Uses `RTClib` and `SD` or `SdFat` libraries

## Libraries

- `RTClib`
- `SdFat` or `SD`

## ❗ Technical Limitations & Notes

- ⚠️ RTC (DS3231) uses I2C — ensure no address conflicts with NeoKey or other I2C devices.
- ⚠️ SD Card uses SPI — must use a **dedicated CS pin** if Ethernet is also used on SPI.
---

## 📘 Technical Summary from Datasheet (Adafruit Adalogger FeatherWing)

- **Main Features**:
  - MicroSD slot for FAT32-formatted cards
  - DS3231 Precision Real-Time Clock (RTC) with temperature compensation
  - Coin cell battery backup support (for RTC)
  - 32KHz output pin (optional)
  - Works with all Feather boards via stackable headers

- **Pin Assignments**:
  - **RTC (DS3231)**: communicates over I2C
    - I2C SDA: shared (typically GPIO 2)
    - I2C SCL: shared (typically GPIO 1)
  - **microSD card**: communicates over SPI
    - Default Chip Select (CS) pin: **GPIO 10**
    - Can be rerouted via jumper and trace cut
  - Additional RTC Pins:
    - **SQW**: Square wave output (optional)
    - **32K**: Optional clock output pin

- **Battery**:
  - Supports CR1220 coin cell for RTC backup
  - Not rechargeable—just a backup for RTC during power loss

- **Libraries**:
  - Arduino: `RTClib`, `SD`
  - CircuitPython: `adafruit_ds3231`, `adafruit_sdcard`

- **Power Considerations**:
  - Powered via Feather 3.3V rail
  - Keep in mind cumulative draw if using multiple FeatherWings

- **Physical Notes**:
  - Designed to fit the FeatherWing form factor
  - Stackable, but must ensure CS/I2C conflicts are avoided

