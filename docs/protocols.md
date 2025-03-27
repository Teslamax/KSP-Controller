# 🛰 protocols.md

This document outlines the communication protocols and telemetry mappings used for KSP controller integration.

---

## 🎮 USB HID / Input Events

Planned USB HID integration will include:

- Joystick axis mapping (throttle, pitch, yaw, roll)
- Button presses (stage, gear, lights, RCS, SAS)
- Encoder events (camera mode, SAS mode cycling)

Firmware will register as a composite HID device (keyboard + joystick).

---

## 📡 Kerbal Simpit Revamped Integration

Communication Method: **Serial over USB** or **Ethernet (optional)**

Supported telemetry messages to be parsed:

- Altitude
- Orbital velocity
- SAS Mode (numeric ID)
- Surface speed
- Current throttle level
- Action group states (gear, brakes, lights, RCS)
- Apoapsis / Periapsis
- Time to maneuver node

Supported input commands to KSP:

- Button presses (Stage, action groups)
- Mode selection (encoder feedback)
- Throttle override / adjustment (TBD)

---

## 🗺 Mapping Strategy

Mapping from Simpit variables to controller output (displays, LEDs):

```json
{
  "telemetry": {
    "altitude": "tft.zone1",
    "velocity": "tft.zone2",
    "throttle": "tft.zone3",
    "sasMode": "tft.icon.sas",
    "gear": "neokey.0",
    "brakes": "neokey.1",
    "rcs": "neokey.2",
    "lights": "neokey.3"
  }
}
```

This allows dynamic reassignment and lightweight UI changes without recompiling firmware.

---

## 🧩 Notes

- Protocol parsing will be handled with a lightweight message dispatcher
- Configurable I²C and SPI device roles are planned via config file
- Encoders will eventually control SAS/camera mode and send commands *and* display current mode via RGB color

---

More integrations (kRPC, Telemachus) can be added later.

