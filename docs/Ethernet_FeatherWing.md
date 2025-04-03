# Ethernet FeatherWing (WIZ5500-based)

**Link**: https://www.adafruit.com/product/3201  
**Chipset**: WIZnet W5500  
**Interface**: SPI

## Pin Usage (suggested)

- CS: GPIO10 (customizable)
- SPI: Shared with SD (MOSI, MISO, SCK)

## Notes

- May require external 3.3V regulator if power is unstable
- Works with standard `Ethernet` or `Ethernet_Generic` libraries

## Libraries

- `Ethernet_Generic`
- `Adafruit_TinyUSB` (for composite USB)
