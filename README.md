# KSP-Controller

Custom-built space simulation controller for **Kerbal Space Program** (KSP) and related spaceflight games. Features USB-HID inputs, telemetry displays, and full hardware integration via microcontroller.

This project is structured to support both **experimentation** and **final build development**. The firmware and hardware architecture are being prototyped with ESP32-S3 Feather components, while the final controller may transition to a Teensy 4.1-based solution.

---

## 📌 Project Documents

- 📄 [Comprehensive Proposal](Proposal.md)
- 📄 [ESP32-S3 vs Teensy 4.1 Comparison](docs/comparison-esp32s3-teensy41.md)
- 📄 [Pinout & Bill of Materials](docs/hardware/pinout.md)
- 📄 [Recommended Directory Structure](docs/dev-log.md)

---

## 🧪 Firmware Source

The PlatformIO-based firmware project lives in the [`firmware/`](firmware/) folder.
The hybrid PlatformIO/Arduino IDE firmware project is inside `/src/`.

**Current Features:**
- Built-in TFT menu UI (ESP32-S3 Reverse TFT Feather)
- NeoKey 1x4 keypad with RGB feedback (I²C)
- Rotary encoder (mocked, with menu cycling)
- Ethernet support (W5500 FeatherWing)
- mDNS responder (`ksp-controller.local`)
- USB HID boilerplate (future expansion)

➡ To build + flash the firmware:
```bash
cd firmware
pio run -t upload
```

---

## ⚙️ Hardware Components (Phase 1 Experimentation)

- ESP32-S3 Reverse TFT Feather (Adafruit 5691)
- Ethernet FeatherWing (Adafruit 3201)
- NeoKey 1x4 I2C Keypad (Adafruit 4980)
- Feather Doubler + stacking headers
- BOJACK breadboard kit (Amazon)

See [`docs/hardware/BOM.md`](docs/hardware/BOM.md) for full list.

---

## 💡 Development Goals

### 🧪 Experimental Phase (ESP32-S3-Based)
- Test TFT display UI and menu interactions
- Experiment with I²C input devices (NeoKey, encoders)
- Simulate USB HID controls (keyboard/gamepad)
- Ethernet-based diagnostics (optional HTTP config)
- Validate GPIO/power constraints

### 🚀 Final Phase (Teensy 4.1 Target)
- Full GPIO matrix for buttons, encoders, and sensors
- HID + Ethernet telemetry for KSP mods (e.g. Kerbal Simpit)
- Custom PCB and enclosed controller design

---

## 🔗 Inspiration

- [Kerbal Controller - The Basics](https://www.instructables.com/Kerbal-Controller-the-Basics/)
