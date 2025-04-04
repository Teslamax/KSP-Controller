# Adafruit NeoKey 1x4 QT (Product ID 4980)

**Link**: https://www.adafruit.com/product/4980  
**Interface**: I2C via seesaw  
**Address**: 0x30 (default, configurable via solder jumpers)

## Features

- 4 mechanical key switches with RGB NeoPixels
- STEMMA QT-compatible
- Chainable with other I2C devices

## Notes

- Requires 3.3V or 5V power
- Controlled using `Adafruit_NeoKey` or `Adafruit_seesaw`
- Do not share I2C address with other QT devices

## Libraries

- `Adafruit_NeoKey`
- `Adafruit_seesaw`

## ❗ Technical Limitations & Notes

- ⚠️ Uses I2C at address **0x30 (default)** — reconfigure jumpers to avoid conflicts if needed.
- ⚠️ Operates at 3.3V or 5V — confirm compatibility with Feather board voltage.
- ✅ Fully compatible with STEMMA QT daisy-chaining.
