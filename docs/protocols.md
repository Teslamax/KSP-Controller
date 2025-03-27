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



---

## 🧭 MAC Address Convention & Override

The Ethernet FeatherWing (WIZnet W5500) requires that a MAC address be defined in firmware. To avoid conflicts with real network hardware, this project uses a **Locally Administered Address (LAA)** scheme.

### ⚙️ Default MAC Address Format

```
0x02, 0x42, 0xAC, 0x00, 0x00, 0x01
```

- `0x02` → Declares it as a Locally Administered Address (LAA)
- `0x42`, `0xAC` → Reserved for this project
- Last 3 bytes are configurable

### 🔁 Runtime Override via SD Card

If the file `/config/mac.txt` exists on the SD card, the firmware will attempt to load the MAC address at runtime.

Expected format (colon-separated hex or comma-separated values):

```
02:42:AC:00:00:01
```

or

```
0x02, 0x42, 0xAC, 0x00, 0x00, 0x01
```

If the file is malformed or missing, the firmware will fall back to the default.

