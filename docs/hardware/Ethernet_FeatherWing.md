# Ethernet FeatherWing (WIZ5500-based)

**Link**: https://www.adafruit.com/product/3201  
**Chipset**: WIZnet W5500  
**Interface**: `SPI`

## Pin Usage (suggested)

- `CS`: `GPIO10` (customizable - *changing to `GPIO09`*)
- `SPI`: Shared with SD (`MOSI`, `MISO`, `SCK`)

## Notes

- May require external 3.3V regulator if power is unstable
- Works with standard `Ethernet` or `Ethernet_Generic` libraries

## Libraries

- `Ethernet_Generic`
- `Adafruit_TinyUSB` (for composite USB)

## ❗ Technical Limitations & Notes

- ⚠️ WIZ5500 Ethernet controller uses SPI — must assign a **dedicated CS pin** (suggested: `GPIO10`).
- ⚠️ SD and Ethernet sharing SPI requires careful CS management.
- ⚠️ May require **external 3.3V regulator** for stable operation in high-current scenarios.

---

## 🔧 ESP32-S3 Integration Notes (from Adafruit Learn Guide)

The Adafruit WIZ5500 Ethernet FeatherWing integrates well with the ESP32-S3 Reverse TFT Feather, with the following considerations:

### 🔌 Hardware

- Uses SPI for communication: MISO, MOSI, SCK shared with other SPI devices
- Default CS pin is **GPIO 10**
- CS can be reassigned by cutting the trace and using a jumper (e.g., to **GPIO 9**)
- Requires 3.3V logic (native to Feather)
- Can be powered using Feather’s 3.3V or with external PoE splitters

### 💻 Software

- Best used with the **Arduino Ethernet2 library**
- CircuitPython support is minimal or experimental
- Ensure library version 2.0.0 or later for WIZ5500 support

### ⚠️ Integration Constraints

- Avoid ADC2 pins when Wi-Fi or BLE is active
- Verify shared SPI bus compatibility
- Reassign CS to avoid conflict with other FeatherWings (e.g., Adalogger also defaults to CS = GPIO 10)
- Confirm I2C and analog pins aren’t overcommitted

For full documentation, visit the [Adafruit Ethernet FeatherWing Learn Guide](https://learn.adafruit.com/adafruit-wiz5500-wiznet-ethernet-featherwing?view=all).
