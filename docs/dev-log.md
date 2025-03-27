# 📓 Development Log

This file tracks updates and internal planning for the KSP Controller project.

## 📁 Recommended Directory Structure

```
KSP-Controller/
├── README.md                ← Project overview + firmware build instructions
├── Proposal.md              ← Project vision + detailed spec
├── firmware/                ← PlatformIO project
│   ├── platformio.ini
│   ├── src/
│   │   └── main.cpp
│   └── lib/                 ← Custom libraries/modules go here
├── hardware/                ← All physical layout, schematics, and enclosure files
│   ├── pinout.md            ← GPIO map (OLED, buttons, encoders, etc.)
│   ├── wiring-diagrams/     ← PNGs, Fritzing, or KiCad schematics
│   ├── 3d-models/           ← STL/DXF files for case, brackets
│   └── BOM.md               ← Component list w/ links and quantities
├── docs/                    ← Internal notes, user guide, dev notes
│   ├── display-ui-notes.md  ← Layout plans for TFT/OLED menus
│   ├── modes.md             ← SAS, camera, throttle profiles
│   ├── protocols.md         ← HID & Ethernet-based API notes
│   └── dev-log.md           ← Personal changelog / diary
├── software/                ← Host-side utilities or KSP integration tools
│   ├── mods/                ← Configs or custom KSP mod integrations
│   └── telemetry-scripts/   ← Optional Python or web-based viewers
└── assets/                  ← Images, screenshots, diagrams for docs/README
```

You can evolve this structure over time as firmware, UI, and hardware designs mature.

---

## 💾 SD Card Storage Options for Configuration and Logging

### ✅ Option 1: SPI microSD Breakout (Flexible Breadboarding)
- Interface: SPI (MOSI, MISO, SCK, CS)
- Cost: ~$7–$10
- Good for: Breadboard prototyping, log file access, FAT32 `config.json`
- USB Mass Storage: Supported via TinyUSB MSC

### ✅ Option 2: FeatherWing Data Logger (Stackable + RTC)
- Interface: SPI via FeatherWing
- Cost: ~$13
- Good for: Stackable design with Feather ecosystem
- USB Mass Storage: Supported
- Bonus: Built-in real-time clock for log timestamps

### 🚫 Option 3: I²C SD Cards — Not Recommended
- Too slow and rare, not compatible with USB MSC

### 🧠 Advanced Option: Custom QSPI Flash Chip
- Cost: ~$2–$5 (plus PCB fabrication)
- Complex and only suitable for custom boards

---

## 🎛 I²C Rotary Encoder Options

### ✅ Adafruit QT Rotary Encoder (PID: 4991)
- Interface: I²C via Seesaw
- RGB LED built-in
- Integrated pushbutton switch (shaft press)
- STEMMA QT / Qwiic compatible (chainable)
- Breadboard-friendly
- Cost: ~$6.95 (knob sold separately)
- Shaft: **6mm D-shaft** (standard knobs supported)
- Ideal for experimenting on breadboard, later mountable through a panel

### ⚠️ SparkFun Qwiic Twist
- Similar feature set (I²C, RGB, pushbutton)
- Higher price (~$24.95)
- No knob included
- Also 6mm D-shaft

➡️ **Recommended for prototyping and expansion:** Adafruit 4991 (better value, easier stacking)

---

### 🧠 Additional Notes, Illumination Options & Best Practices

- 💡 **Illumination Options**:
  - Both Adafruit 4991 and 5880 include an RGB LED underneath the encoder shaft.
  - For visible lighting, use **translucent or skirted knobs** that allow light to diffuse upward from the PCB.
  - You can 3D print or source knobs with a **clear rim**, **light pipe base**, or a **glow-through diffuser**.
  - There are no encoders with built-in illuminated shafts, so knob-based lighting is the practical solution.

- 🔁 **Encoder Resolution**: These are incremental (relative) encoders with detents. Best for scrolling, mode switching, or throttle trims.

- 🎯 **Flexible Roles**: Assign encoder functions in firmware via named roles (`encoder_menu`, `encoder_sas`, etc.) so physical swaps don't require firmware rewrites.

- 🧷 **Panel Mounting**:
  - Shaft fits in standard 6mm D-shaft holes.
  - Secure PCB using adhesive standoffs, panel brackets, or 3D-printed guides.
  - Consider cutouts for cables or strain relief behind the front panel.
  - The PEC11-4215F-S24 (used in 5880) is ideal for panel-mounting and can be used in final enclosures.

- 🔌 **Cable Management**:
  - Use STEMMA QT or Qwiic extension cables to simplify daisy chaining.
  - Clip or route cables in the enclosure to prevent stress on connectors.

- 📡 **I²C Addressing**:
  - Each encoder supports address configuration via solder jumpers.
  - Track addresses in `config.json` or `pinout.md` for maintainability.

- 🎛 **Custom Knobs**:
  - Compatible with most 6mm D-shaft knobs (knurled, aluminum, or rubber).
  - Consider larger knobs for vertical or flat-panel usability.
  - Optional: 3D-print labeled or translucent knobs for mode indication or RGB glow.

- 🧩 **Final Build Compatibility**:
  - Both Adafruit 4991 and 5880 are fully compatible with final designs.
  - 5880 is preferred if you want pre-soldered convenience.
  - 4991 is better for flexible sourcing or if you want to choose/swap the encoder later. These are incremental (relative) encoders with detents. Best for scrolling, mode switching, or throttle trims.

- 🧷 **Panel Mounting**:
  - Shaft fits in standard 6mm D-shaft holes.
  - Secure PCB using adhesive standoffs, panel brackets, or 3D-printed guides.
  - Consider cutouts for cables or strain relief behind the front panel.

- 🔌 **Cable Management**:
  - Use STEMMA QT or Qwiic extension cables to simplify daisy chaining.
  - Clip or route cables in the enclosure to prevent stress on connectors.

- 📡 **I²C Addressing**:
  - Each encoder supports address configuration via solder jumpers.
  - Track addresses in `config.json` or `pinout.md` for maintainability.

- 🎛 **Custom Knobs**:
  - Compatible with most 6mm D-shaft knobs (knurled, aluminum, or rubber).
  - Consider larger knobs for vertical or flat-panel usability.
  - Optional: 3D-print labeled or tactile knobs for game modes.

---

## 🆕 Additional Component Considerations

### 🧲 Rotary Encoders
- **Adafruit 4991** – I²C STEMMA QT rotary encoder breakout. Includes RGB LED and pushbutton support, but requires soldering on a compatible encoder (not preinstalled).
- **Adafruit 5880** – Same as 4991 but includes the encoder pre-soldered. STEMMA QT compatible, ready to plug and use immediately.

### 🎚️ Motorized Throttle / Sliders
- **Adafruit 5741** – Conductive plastic slide potentiometer with STEMMA QT interface. Motor disengages automatically when touched.
- **Adafruit 4489** – L9110H H-Bridge motor driver (8-DIP), ideal for driving motorized potentiometers (2.5V–12V, 800mA max).
- **Adafruit 5466** – 10KΩ motorized slide potentiometer with 75mm linear travel and 5V DC motor. Analog output for position feedback.

> Consider adding one for auto-throttle or throttle sync display. Requires H-bridge for control.

### 🧩 FeatherWing Tripler
- **Adafruit 3471** – Allows clean stacking of 3 Feather/FeatherWing boards side-by-side
- Recommended if using ESP32-S3 Feather + Ethernet Wing + Logger Wing simultaneously

---

## 🔧 Planned Integration Features

- Add `config.json` support to firmware
  - Read settings from `/config/config.json` on SD at boot
  - Use for keybindings, display mode, default HID layout

- Enable optional **USB Mass Storage mode**
  - Mount SD card as USB drive when toggle pin or menu option selected
  - Allow drag-drop file transfer of config/logs

- Update `pinout.md` and `BOM.md` to include SD-related wiring

- Create wiring diagram showing:
  - ESP32-S3 Feather
  - Ethernet FeatherWing
  - NeoKey 1x4 (I2C)
  - microSD via SPI (CS managed)
  - QT Rotary Encoder(s) on I²C
  - Optional motorized throttle (slide pot + H-bridge)

---

ℹ️ These upgrades allow the controller to be reconfigurable via SD card, easier to debug/log, and modular for adding rotary encoders, motorized input devices, and more flexible I²C/GPIO input chains.
