# Development Log

## Notes
- USB.h must be included as `#include "USB.h"` on ESP32-S3.
- Adafruit_TinyUSB library should NOT be installed. Conflicts with built-in TinyUSB stack.
- Descriptor stub for HID gamepad defined in code.
- Current compile errors relate to `Adafruit_USBD_CDC` being undefined, pending stack verification.

## USB Testing Plan
- [ ] Verify keyboard descriptor functionality
- [ ] Add gamepad descriptor (stub OK)
- [ ] Confirm Simpit CDC second channel possible

## Hardware Integration Plan
- [ ] Confirm NeoKey logic
- [ ] Profile storage via EEPROM
- [ ] SD config fallback (MAC, IP, etc)
