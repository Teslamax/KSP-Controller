# 📡 KSP Mod Protocols



---

## 🚀 Kerbal Simpit Integration

This project is compatible with the [Kerbal Simpit Revamped mod](https://github.com/stuart-atm/kerbal-simpit), which allows the microcontroller to receive KSP telemetry and send commands back to the game.

### Supported Features via Arduino Library

| Capability               | Status  |
|--------------------------|---------|
| Receive telemetry (altitude, velocity, etc.) | ✅ |
| Send input (SAS, throttle, stage)           | ✅ |
| USB Serial transport                         | ✅ Recommended |
| Ethernet UDP transport                       | ⚠️ Possible (experimental) |
| Integration with OLED/TFT display            | ✅ Planned |
| Input via buttons, rotary encoders           | ✅ Native |

### Integration Notes

- The ESP32 acts as a USB Serial device (`Serial`)
- The `KerbalSimpit` library is included in `firmware/lib/`
- Example test sketch provided in `simpit_test.cpp`
