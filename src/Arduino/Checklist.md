# KSP Controller – Feature Checklist

## USB Interfaces

| Interface       | Type     | Status      | Notes                                |
|----------------|----------|-------------|--------------------------------------|
| SerialDebug     | CDC      | ✅ Working  | Logging/debug via USB                |
| SerialSimpit    | CDC      | 🔲 Planned  | To be used with Kerbal Simpit Mod    |
| Keyboard HID    | HID      | ✅ Working  | NeoKey 1x4 tested + custom keymap    |
| Joystick HID    | HID      | 🔲 Stub     | Descriptor ready, not yet active     |

## HID Devices (Planned)

| Feature          | Type     | Status    | Notes                                           |
|------------------|----------|-----------|-------------------------------------------------|
| 6 Axis Joystick  | Analog   | 🔲 Planned | Pitch, Roll, Yaw, Translate X/Y/Z              |
| Throttle Slider  | Analog   | 🔲 Planned | Motorized for auto-calibration + reflect state |
| POV Hat Switch   | Digital  | 🔲 Planned | 8-way or 4-way directional control             |
| 32 Buttons       | Digital  | 🔲 Planned | Matrix scanning or I2C GPIO                    |

## Hardware Modules

| Component       | Status      | Notes                                  |
|----------------|-------------|----------------------------------------|
| ST7789 TFT      | ✅ Working  | Used for status/log display            |
| RTC DS3231      | ✅ Working  | Auto-adjusts if clock lost power       |
| SD Logging      | ✅ Working  | Reads network config + logs (planned) |
| Ethernet (W5500)| ✅ Working  | DHCP/Static IP + mDNS                  |
| EEPROM          | ✅ Working  | Stores profile number                  |
| NeoKey 1x4      | ✅ Working  | Interrupt-driven input + NeoPixel RGB  |
| 2x GPIO Buttons | ✅ Working  | Used for profile change                |

---

## Next Steps

- [ ] Add USB HID Gamepad report descriptor
- [ ] Build joystick input system for analog axes
- [ ] Implement motorized throttle test driver
- [ ] Add Simpit CDC handler + message parser
- [ ] Add profile save/load to SD config

