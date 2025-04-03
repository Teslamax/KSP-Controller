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
