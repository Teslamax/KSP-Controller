# 🧩 Combined Project Docs
Generated on Tue Apr 29 20:08:03 UTC 2025\n

# --- docs/README.md ---

# 📘 KSP Controller Docs

Welcome to the documentation hub for the KSP Controller project.
This collection includes hardware details, command references, firmware architecture, and more.

---

# --- docs/comparison-esp32s3-teensy41.md ---

# ⚖️ ESP32-S3 vs Teensy 4.1 — KSP Controller Platform Comparison

## Overview
This document outlines the strengths and limitations of the **Adafruit ESP32-S3 Reverse TFT Feather** (5691) currently used for prototyping, compared to the **Teensy 4.1**, which may serve as the final platform for the KSP controller.

---

## 📊 Feature Comparison

| Feature                        | ESP32-S3 (Adafruit 5691)            | Teensy 4.1                              |
|-------------------------------|-------------------------------------|----------------------------------------|
| **Core Architecture**         | Dual-core Xtensa LX7 @ 240MHz       | ARM Cortex-M7 @ 600MHz                 |
| **RAM**                       | ~512KB SRAM + 2MB PSRAM              | 1024KB SRAM + up to 8MB PSRAM (add-on) |
| **Flash**                     | 4MB (5691) or 8MB (other variants)   | 8MB onboard, expandable via MicroSD    |
| **USB Support**               | USB 2.0 native, HID capable          | USB 2.0 native, HID, MIDI, Serial, etc.|
| **GPIO Count**                | ~20-24 usable                        | 40+ GPIOs                               |
| **Built-in Display**          | Yes (1.14" ST7789)                   | No (add via SPI or I2C)                |
| **Built-in Wi-Fi / BLE**      | ✅ Yes                               | ❌ No                                   |
| **Ethernet Support**          | Via W5500 FeatherWing                | ✅ Native via add-on PHY                |
| **Power Consumption**         | Low (suitable for USB/PoE projects)  | Higher, especially at full clock speed |
| **Dev Board Ecosystem**       | Adafruit Feather                    | PJRC (Teensy) ecosystem                |
| **Prototyping Support**       | STEMMA QT, FeatherWing ecosystem     | Breadboard or custom PCB               |

---

## ✅ What Can You Do with the ESP32-S3 (5691)?

- ✔️ Build the **TFT interface and UI framework**
- ✔️ Integrate **NeoKey 1x4 QT** keypad with RGB
- ✔️ Connect and test **W5500 Ethernet Wing**
- ✔️ Implement **USB HID (keyboard/gamepad)**
- ✔️ Add tactile buttons, encoders, or I2C OLEDs

---

## 🔒 ESP32-S3 Limitations vs Teensy 4.1

- ❌ Fewer **available GPIOs** (might require I/O expanders for large builds)
- ⚠️ **Limited performance headroom** (slower for heavy USB + Ethernet + graphics loads)
- ❌ No **native Ethernet or USB host** capabilities
- ⚠️ Feather form factor may restrict enclosure designs for large control panels
- ⚠️ No true **hardware-level real-time scheduling** like Teensy’s Cortex-M7 offers

---

## 🧠 When to Pivot to Teensy 4.1

Consider switching to Teensy when:
- You need **dozens of buttons, LEDs, analog axes**
- You're using **multiple rotary encoders, RGB controls**, or complex I/O
- You want native **Ethernet or MIDI support**
- You want to build a **custom PCB** with maximum I/O flexibility
- You plan to push USB + HID + display + networking at high refresh rates

---

## 🚧 Suggested Workflow
1. Develop and test on ESP32-S3 Feather (5691)
2. Build UI, controller logic, and test hardware interactions
3. If needed, migrate firmware logic to Teensy 4.1 once design stabilizes
4. Design a Teensy-compatible PCB or wiring harness with final I/O layout

# --- docs/design/Analog_Input_Strategy.md ---

# 🧪 Analog Input Strategy for ESP32-S3 Reverse TFT Feather

This document summarizes how to handle analog inputs for your custom controller using the ESP32-S3 Reverse TFT Feather (Adafruit #5691), especially in scenarios where Wi-Fi or BLE is in use.

---

## 📈 Native ADC Capabilities

| Feature            | Description |
|-------------------|-------------|
| **Total ADC Pins** | Up to 20 on-chip, but only ~6 exposed on Feather |
| **Resolution**     | 12-bit (0–4095), ~11-bit effective due to noise |
| **Sampling Rate**  | Up to ~18,000 samples/sec |
| **ADC1 vs ADC2**   | **ADC1** can be used alongside Wi-Fi/BLE; **ADC2** cannot |

> ⚠️ **Use only ADC1 pins when Wi-Fi or BLE is active.**

---

## 🧩 External ADC Options

### ✅ Recommended Chips

| Chip        | Interface | Channels | Resolution | Speed       | Notes |
|-------------|-----------|----------|------------|-------------|-------|
| **ADS1115** | I²C       | 4        | 16-bit     | ~860 SPS    | High precision |
| **ADS1015** | I²C       | 4        | 12-bit     | ~3300 SPS   | Faster, less precise |
| **MCP3008** | SPI       | 8        | 10-bit     | Fast        | Simple & inexpensive |
| **ADS7830** | I²C       | 8        | 8-bit      | Very Fast   | Small resolution, compact |

---

## 🎮 Input Type Recommendations

| Input Device       | Priority      | Suggested Resolution |
|--------------------|---------------|-----------------------|
| **Analog Joystick** | Smooth motion | 10–12 bits |
| **Throttle (manual)** | Precise scaling | 12–14 bits |
| **Motorized Pot (feedback)** | PID-friendly | 12–16 bits |
| **Sliders / knobs** | Mode changes | 8–10 bits |

---

## 🧠 Recommended Strategy

- Use **1–2 native ADC1 pins** for latency-sensitive inputs
- Use **external I²C ADC (e.g. ADS1115)** for 4+ other analog devices
- Consider using **2 ADCs** (e.g. two ADS1015s) if you need >4 channels with I²C

---

## 🧮 ESP32-S3 Feather Pin Usage Estimate (WIP)

| Purpose               | GPIOs Used | Notes |
|------------------------|------------|-------|
| I²C ADC (ADS1115)      | 2 (SDA/SCL) | Shared with display/sensors |
| SPI devices (e.g. SD)  | 3 + 1 per device | Shared SPI, unique CS |
| USB / CDC              | Built-in   | USB stack uses internal GPIOs |
| Native Analog Pins     | 2–4        | ADC1 only if Wi-Fi active |

> 📌 Refer to `docs/Pin_Map.md` for exact GPIO availability.

---

## 🔚 Conclusion

For your 7+ analog input needs:

- Reserve **ADC1 GPIOs** for throttle or joystick axes
- Add **ADS1115 or ADS1015** via I²C for the remainder
- Keep SPI pins for SD, Ethernet, etc.
- Avoid ADC2 pins entirely when Wi-Fi or BLE is active


# --- docs/design/Architecture.md ---

# KSP-Controller System Architecture

This document describes the modular architecture of the KSP-Controller firmware project.

## Overview

```text
+----------------------+
| User Interfaces      |  (USB CDC, Telnet, Bluetooth Serial)
+----------------------+
          |
          v
+----------------------+
| CLI Parser/Router    |  (Command dispatch and parsing logic)
+----------------------+
          |
          v
+----------------------+
| High-Level Controllers |
| - NetworkManager      |
| - ConfigManager       |
| - DisplayManager      |
| - HIDManager          |
| - LogManager          |
+----------------------+
          |
          v
+----------------------+
| Hardware Abstraction |
| - Ethernet Wrapper   |
| - TFT Display Driver |
| - Key/Encoder Input  |
| - RTC/NTP Wrapper    |
| - SD/EEPROM Layer    |
| - LED Manager        |
+----------------------+
```

Each layer should fail gracefully and allow optional components to be omitted or simulated in software.


## 🧠 ESP32-S3 Hardware Considerations

- **Wi-Fi and BLE use ADC2 internally**, so analog reads should be limited to **ADC1 pins**.
- **TFT display and buttons** occupy GPIOs D0, D3, D7, D8, D13, and D38.
- **Only BLE is supported**; **Classic Bluetooth is not available**.
- Flash memory is **4MB**; this limits use of some CircuitPython/BLE features.
- Built-in LiPoly charger and fuel gauge use I2C pins D1/D2.

# --- docs/design/CLI_Spec.md ---

# 💻 CLI System Specification – KSP Controller

This document outlines the command-line interface (CLI) and logging system architecture for the KSP & Space Simulation Controller.

---

## 🧩 Purpose

Provide a consistent, extensible, and fault-tolerant command interface for debugging, configuration, status display, and manual control.

---

## 🖧 Supported Interfaces

The CLI system is accessible over the following interfaces:

| Interface     | Purpose                      | Notes                        |
|---------------|------------------------------|------------------------------|
| USB CDC       | Primary debug interface      | Always active (if available) |
| Telnet (Ethernet/Wi-Fi) | Remote debugging     | CLI over IP stack            |
| BLE UART      | Wireless, limited platforms  | macOS/iOS BLE serial may be limited |
| TFT Display   | Output-only log/status view  | Button-controlled navigation |

---

## 🧠 Command Routing & Operator Model

A single shared command handler services all input interfaces. Interfaces pass commands to a **common parser**, and output is routed back to the correct origin or to all relevant outputs (e.g., logs).

### Operator Model

```
[ Input Interface ] --> [ Command Parser ] --> [ Operator Dispatcher ] --> [ Output & Log Streams ]
```

All interfaces feed into the same parser and handler, sharing:

- History buffer
- Log buffer (with timestamping)
- CLI grammar
- Command registry

---

## 🔤 CLI Grammar

```plaintext
<command> [arguments...] [flags]

Examples:
  status
  status json
  config save
  log level debug
  reboot
```

Supports:
- Command aliases
- Flags and switches (e.g., `--verbose`)
- Subcommands
- JSON output for machine-readable results

---

## 🧾 Command Categories

| Category        | Examples                        |
|----------------|----------------------------------|
| System Status   | `status`, `uptime`, `version`   |
| Config/Profile  | `config save`, `profile load`   |
| Network         | `ip`, `wifi status`, `dns`      |
| HID Mode        | `hid test`, `hid profile`       |
| Simpit Control  | `sim status`, `sim reset`       |
| Logging         | `log level`, `log clear`, `log tail` |
| Debug/Utility   | `i2c scan`, `pinmap`, `reboot`  |

---

## 📝 Logging System

Supports multi-channel log distribution:

| Channel     | Purpose                     | Notes                        |
|-------------|-----------------------------|------------------------------|
| USB CDC     | Verbose logs, errors        | Console output to host       |
| BLE UART    | Optional serial over BLE    | May require mobile viewer    |
| Telnet      | IP remote logs + CLI        | Can log to session or broadcast |
| TFT Display | Color-coded log viewer      | Scrollable via buttons       |
| SD Card     | Persistent log storage      | Log rotation + timestamping  |

### Log Levels
- DEBUG
- INFO
- WARNING
- ERROR
- CRITICAL

Logs include:
- Timestamps (from RTC/NTP)
- Source interface
- Severity level
- Optional emojis/symbols

---

## 🧮 Command History

- Shared across interfaces (except display)
- Recall via arrow keys (USB CDC / Telnet)
- Configurable max buffer length
- May be saved to SD or EEPROM optionally

---

## 🔒 Fallbacks and Graceful Degradation

| Feature     | Behavior When Unavailable               |
|-------------|------------------------------------------|
| TFT         | Logs redirected to USB/Telnet           |
| BLE UART    | Disabled without affecting others        |
| Network     | Falls back to USB if Ethernet/Wi-Fi down |
| Clock       | RTC → NTP → millis() fallback sequence  |

---

## 💾 Persistent Features

- Configuration & profiles saved as JSON to SD
- On boot: loads config from SD, then EEPROM fallback
- Command: `config save`, `config load`, `config reset`

---

## 📅 Future Enhancements

- Web interface for log viewing and CLI
- Command auto-completion
- Secure command authorization for critical commands
- Interactive TFT command mode

---

Let me know if you'd like to add commands, rework the grammar, or link this with architecture or pinout files.

# --- docs/design/Capabilities.md ---

# KSP-Controller Capabilities Matrix



## Software Features

| Feature          | Library Used            | Notes                                |
|------------------|--------------------------|--------------------------------------|
| USB HID          | Adafruit TinyUSB         | Joystick/Keyboard/Gamepad            |
| CLI              | Custom Parser            | Shared across CDC, Telnet, BT Serial |
| Logging          | ArduinoLog (or custom)   | Timestamped, leveled logs            |
| Display          | Adafruit GFX + ILI9341   | Built-in TFT                         |
| SD Card          | SD or SdFat              | SPI interface                        |
| RTC              | RTClib                   | Optional battery backup              |
| NTP              | sntp.h (ESP32 native)    | Fallback from RTC                    |
| NeoPixels        | Adafruit NeoPixel        | Status or ambient feedback           |
| Bluetooth        | BluetoothSerial / NimBLE | Optional debug interface             |

---

## ❗ Design Constraints & Warnings

- **ESP32-S3 Feather Reverse TFT**: GPIO40–47 reserved for TFT. Classic Bluetooth not supported.
- **Ethernet FeatherWing** and **Adalogger FeatherWing** both use SPI — assign unique CS lines.
- **NeoKey 1x4** and **RTC** share I2C — check for address conflicts (default 0x30 for NeoKey).
- **Power Caution**: Ethernet + SD + motorized components may require power filtering and voltage regulation.

# --- docs/design/Config_Structure.md ---

# KSP-Controller Configuration Structure

This document defines the format and logic for system configuration, which can be loaded from JSON on SD card or EEPROM.

## JSON Config Structure (Example)

```json
{
  "hostname": "ksp-controller",
  "net": {
    "mode": "dhcp",
    "ip": "192.168.1.42",
    "mask": "255.255.255.0",
    "gw": "192.168.1.1"
  },
  "log": {
    "level": "info",
    "enabled": true
  },
  "profile": "hid"
}
```

## Fallback Priority

1. JSON on SD card
2. EEPROM backup
3. Hardcoded defaults

Each section should have a version field to allow future migrations.

# --- docs/design/Controller_Design_Spec.md ---

# KSP & Space Simulation Controller — System Design Specification

## **📌 Project Overview**
This document outlines the design, features, and integration of a **custom-built space simulation controller** for **Kerbal Space Program (KSP)** and other space-based games. It includes UI/UX design, power considerations, microcontroller selection, feature implementation, and software integration with KSP mods.

---

## **📜 Current Status**
The project is in the design and planning phase. **Hardware and software considerations have been mostly outlined**, with remaining decisions focused on finalizing integration details and optimizing component choices.

---

## **🎛 UI/UX Design**
### **Displays & Feedback System**
| **Display Type** | **Purpose** | **Notes** |
|-----------------|------------|----------|
| **TFT Display** | Main status display (altitude, velocity, SAS mode, camera mode, etc.) | Chosen for high-resolution graphical feedback |
| **OLED Display (Throttle)** | Shows throttle mode, current throttle percentage, and in-game throttle level | Compact & high-contrast |
| **OLED Display (Menu)** | Used for profile selection, calibration, settings | Menu navigation via rotary encoder |
| **RGB-Lit Buttons** | Indicate status of landing gear, brakes, RCS, SAS, stage lock | Provides immediate visual feedback |
| **RGB-Lit Rotary Encoders** | Used for SAS mode and camera mode selection | Blinks briefly when a mode is switched |

### **Controls**
| **Control** | **Function** | **Notes** |
|-----------|------------|----------|
| **2x Joysticks (JH-D400X-R4)** | **Translation (X, Y, Z) & Rotation (Pitch, Yaw, Roll)** | One for translation, one for rotation |
| **Linear Potentiometer (Throttle)** | **Primary throttle control** | Motorized for self-calibration & auto-throttle |
| **Spring-Loaded Slider (Fore/Aft Translation)** | **Allows forward/backward movement in space** | Returns to center when released |
| **Rotary Encoder (Camera Mode)** | Cycles through camera views | Click toggles Free Camera |
| **Rotary Encoder (SAS Mode)** | Changes SAS mode | RGB-lit for mode indication |
| **20x Action Group Buttons** | Used for custom game functions | Split into 2x10 layout |
| **Precision Control Mode Button** | Enables fine-tuned movement (Caps Lock in KSP) | LED-lit for status indication |
| **Stage Button & Stage Lock Button (LED-lit)** | Executes staging and prevents accidental staging | Stage lock LED indicates status |

---

## **⚡ Power System**
### **Primary Power: USB-C PD (5V, up to 3A)**
- Powers **Teensy 4.1, displays, joysticks, buttons, encoders**
- Uses **a high-efficiency voltage regulator** to prevent power fluctuations

### **Secondary Power Options:**
| **Power Source** | **Implementation Method** | **Status** |
|---------------|----------------------|----------|
| **Second USB-C (Power Only)** | Dedicated power input via USB-PD | **Optional footprint on PCB** |
| **PoE (Power over Ethernet)** | UCTRONICS PoE Splitter (5V 4A) | **Planned, splitter mounted internally** |
| **AC-DC PSU (IEC C7/C8)** | Internal power supply conversion | **Rejected (too complex for current build)** |

### **Power Stabilization Measures:**
- **Large capacitor (470µF - 1000µF) to smooth out motor power spikes**
- **Power monitoring circuit with menu-based logging**

---

## **🖥 Microcontroller & Hardware Integration**
### **Main Microcontroller: Teensy 4.1**
- **Chosen for its high-speed processing & USB-HID support**
- Supports **Ethernet connectivity for mod integration**
- Handles all **sensor inputs, controls, display updates**

### **Additional Components:**
| **Component** | **Purpose** |
|-------------|-------------|
| **Motorized Potentiometer** | Allows automatic throttle calibration & autothrottle |
| **H-Bridge Motor Driver** | Controls motorized throttle |
| **Ethernet Kit for Teensy 4.1** | Adds network support for integration with KSP mods |
| **RGB Controllers** | For LED feedback systems |
| **Custom PCB (Planned)** | Houses main connections for switches, encoders, LEDs |

---

## **📌 Appendix: SAS Mode Selection Considerations**
### **Debating Between RGB Buttons vs. Rotary Encoder for SAS Mode**
Currently undecided between two options:
- **8 RGB-Lit Buttons (2x4 Layout)** for direct SAS mode switching.
- **RGB-Lit Rotary Encoder** for cycling through SAS modes sequentially.

---

## **📌 Appendix: Open-Source API for Display Integration**
Exploring the possibility of integrating open-source APIs for external displays, particularly for compatibility with multiple games beyond KSP.

---

## **📌 Appendix: LED Control Options**
Evaluating different control methods for RGB LEDs, including I2C controllers or direct PWM control from the microcontroller.

---

## **📌 Appendix: KSP Mod Integration for External Hardware**
### **Comparison of KSP Mods Supporting External Hardware**
| **Mod Name**                 | **Communication Method** | **Input Capabilities** | **Output Capabilities** | **Maintenance Status** |
|------------------------------|--------------------------|------------------------|------------------------|------------------------|
| **Kerbal Simpit Revamped**   | USB Serial               | SAS, RCS, gear, lights, brakes, action groups, throttle, camera, timewarp | Altitude, velocity, resources, SAS mode, orbit data, target data | Actively maintained |
| **kRPC**                     | Ethernet (TCP/IP)        | Full vessel control via scripts | Full telemetry, orbital data, automation | Actively maintained |
| **Telemachus**               | Ethernet (HTTP/WebSocket)| Limited control via web UI | Telemetry, resource monitoring, environment data | Maintenance varies |
| **Kerbal Telemetry**         | Ethernet (HTTP/WebSocket)| Limited control (future updates planned) | Real-time telemetry, target tracking, 3D positioning | Maintenance varies |
| **KAPCOM**                   | Ethernet (TCP/IP)        | Mission control-style commands | Real-time telemetry, mission monitoring | Maintenance varies |
| **SerialIO**                 | USB Serial               | Basic vessel control | Telemetry output | Maintenance varies |
| **EthernetIO**               | Ethernet (TCP/IP)        | Basic vessel control | Telemetry output | Maintenance varies |

---

## **📌 Appendix: Defining the Project Scope**
### Philosophical Approach
- Avoid unnecessary complexity; only add controls that improve gameplay or immersion
- Don't replace the keyboard/mouse unless there's clear benefit
- Prioritize controls that provide physical or contextual feedback better than screen-only UI

- Respect emotional connection to KSP1 and the anticipation of building
- Embrace anticipation and gradual build progress as part of the joy

### **What Really Needs to Be in This Project?**
- Essential **flight controls, throttle, and key spacecraft toggles** (SAS, RCS, lights, landing gear, brakes)
- Enable mode-switching functionality with RGB and/or OLED/TFT displays
- **Navigation displays** that enhance real-time decision-making without cluttering in-game UI.

### **What Could Be Handled with a Keyboard/Mouse?**
- **Map navigation and maneuver planning**
- **Menu navigation and advanced autopilot settings**
- **Fine-tuning of non-essential parameters**

### **What Data Display Could Be Offloaded to External Devices?**
- **Telemetry information on a separate screen (iPad, PC, smartphone) using Telemachus/Kerbal Telemetry**
- **Docking camera feeds on an external monitor**
- **Resource tracking and mission planning on a browser window**

---

## **📌 Appendix: Cost Estimation & Fabrication**
### **Estimated Cost of Components**
| **Component** | **Estimated Cost** |
|--------------|----------------|
| **Teensy 4.1** | ~$30 |
| **Joysticks (JH-D400X-R4)** | $20-$50 each |
| **Buttons & Switches** | $1-$5 per unit |
| **Motorized Potentiometer** | $40-$80 |
| **OLED Displays** | $15-$40 each |
| **Miscellaneous Wiring & Components** | $50-$100 |

### **Speculated Total Project Cost**
- **Basic Build:** ~$200-$300
- **Advanced Features (more displays, premium materials):** ~$500+

### **Case Fabrication**
- **Material Options:** Laser-cut acrylic, polycarbonate, or machined metal.
- **Fabrication Service:** Likely through **SendCutSend** or similar.
- **Estimated Cost:** Dependent on material thickness and size, starting at ~$100-$200.

---

## 📌 Appendix: Microcontroller Platform Evolution

As the project evolves, different microcontroller platforms are being evaluated. While the **Teensy 4.1** was initially selected for its strong USB-HID and Ethernet support, recent experimentation with other boards (such as the **ESP32-S3 Reverse TFT Feather**) may influence the final design.

| Stage           | Microcontroller              | Reasoning / Notes |
|-----------------|------------------------------|-------------------|
| **Initial Plan**    | **Teensy 4.1**                  | Chosen for native USB-HID, Ethernet support, high-speed processing, and strong Arduino library compatibility. |
| **Current Testing** | **ESP32-S3 Reverse TFT Feather** | Being used for prototyping. Offers native USB, built-in TFT, wireless, and excellent library support. Evaluating its suitability as the final platform. |
| **Final Decision**  | *To Be Determined*             | Will be based on performance, integration complexity, and I/O requirements. Trade-offs between Teensy and ESP32 will be documented. |

> **Note:** Firmware development is proceeding on the ESP32-S3 board for now, but abstraction layers will help preserve compatibility with alternate hardware if needed.

---

## **📌 Next Steps**
- **Refine internal wiring design (keystone vs. panel-mount connectors).**
- **Design a PCB layout for switch & encoder connections.**
- **Begin prototype assembly with Teensy 4.1 & PoE splitter.**

# --- docs/design/Design_Constraints.md ---

# 🚧 Design Constraints Summary

This document outlines technical limitations and required precautions when integrating components in the KSP Controller project.

---

## ESP32-S3 Reverse TFT Feather
- ❌ Does not support Classic Bluetooth (BLE only)
- ⚠️ GPIO40–47 are reserved for the TFT display
- ⚠️ Limited ADC channels compared to ESP32
- ✅ Native USB supports HID, CDC, Mass Storage via TinyUSB
- Internal flash storage has supports varying wear-leveling options

## Ethernet FeatherWing
- ⚠️ Uses SPI — requires dedicated CS (e.g. GPIO10)
- ⚠️ Shared SPI bus with SD card must be coordinated
- ⚠️ May require external 3.3V regulator for stable Ethernet operation

## Adalogger FeatherWing
- ✅ RTC uses I2C (DS3231)
- ⚠️ Shares I2C bus — ensure address compatibility with other peripherals
- ⚠️ SD card also uses SPI — must not share CS with Ethernet

## NeoKey 1x4
- ⚠️ I2C default address: 0x30
- ⚠️ 3.3V or 5V power required
- ✅ Fully compatible with STEMMA QT chain

## Cross-Component Considerations
- ⚠️ SPI bus shared by multiple devices (SD, Ethernet, TFT)
- ⚠️ I2C bus shared by RTC and NeoKey (check addressing)
- ⚠️ Voltage drops and current draw may require capacitors or regulators


# --- docs/design/Electrical_Power.md ---

# Electrical Power
---

## 🧠 Wiring & Power Overview

This document summarizes the wiring and power distribution plan based on the ESP32-S3 Reverse Feather, Adalogger and Ethernet FeatherWings, NeoKey 1x4, motorized slide potentiometer, and an external 5V power supply.

### 🔌 Power Distribution Summary

| Source                | Voltage | Feeds                                | Notes |
|-----------------------|---------|--------------------------------------|-------|
| USB-C (PC)            | 5V      | Feather for USB CDC + HID + Charging | Connected always |
| External 5V (via diode) | 5V    | NeoPixels, H-Bridge, FeatherWings     | Use Schottky diode (SS14) to isolate |
| LiPoly Battery (optional) | 3.7V | Backup power                         | Buffers voltage dips, optional |

### 🔗 Key Connections

- `USB` pin on Feather: Connect external 5V via diode
- `NeoKey 1x4`: I2C (`SDA`, `SCL`, `5V`, `GND`)
- `Motorized Potentiometer`: Controlled via H-Bridge on GPIO 5/6
- `Slide Pot Wiper`: Connect to A0 (analog read)
- `Ethernet FeatherWing`: SPI + CS on GPIO 14
- `Adalogger FeatherWing`: SPI + CS on GPIO 10

---

## ⚡ Estimated Power Draw

| Component                 | Est. Current (mA) |
|---------------------------|-------------------|
| ESP32-S3 Feather + TFT    | ~120              |
| Ethernet FeatherWing      | ~150              |
| Adalogger FeatherWing     | ~20               |
| NeoKey 1x4 RGB (max)      | ~60               |
| Motor driver + pot        | 100–300 (peak)    |
| Joysticks / Encoders      | ~10–20            |
| **Estimated Total**       | **~400–650 mA**   |

Recommend 5V @ 1.5–2A external power source.

# --- docs/design/HID_Profiles.md ---

# 🎮 Profile Logic

_Details for SAS, camera, and throttle behavior across various input states._

- Build a compact, modular KSP control panel that integrates:
  - USB HID inputs (keyboard/gamepad style)
  - Simpit Revamped USB CDC feedback
  - RGB and motorized feedback (e.g., throttle)

Input modes:
1. KSP Controller
2. Generic HID controller
3. QMK-inspired mode (defined by text file JSON*?) (QMK is firmware based and not compatible with ESP32)

# --- docs/design/KSP_Mod_Capabilities.md ---

# Kerbal Simpit Revamped (KSR) vs. kRPC C-nano

## Purpose
This document outlines the features exposed by **Kerbal Simpit Revamped (KSR)** and compares them with what is available through **kRPC C-nano**. It focuses on actionable control and feedback elements relevant to cockpit panels and MFD (multi-function display) design.

## Key Goals
- Determine which features are supported by KSR
- Compare feature coverage with kRPC C-nano
- Identify features available *only* through kRPC C-nano
- Help inform which elements are appropriate for physical panel vs. MFD

---

## ✅ What Kerbal Simpit Revamped (KSR) Exposes

### 🔧 Control Inputs (from hardware → KSP)
| Feature                     | Supported | Notes |
|----------------------------|-----------|-------|
| Stage Activation           | ✅        | Activate next stage |
| Action Groups (AG1–AG10)   | ✅        | Direct access to custom AGs |
| Lights Toggle              | ✅        | Toggle vessel lights |
| Gear Toggle                | ✅        | Deploy/retract landing gear |
| Brakes Toggle              | ✅        | Brake on/off |
| SAS Toggle                 | ✅        | Activate/deactivate SAS |
| RCS Toggle                 | ✅        | Activate/deactivate RCS |
| Abort                     | ✅         | Trigger abort action |
| Throttle Up/Down/Zero/Full| ✅        | Discrete throttle control steps |
| Translate/Rotation Axes   | ✅        | For joystick inputs, if configured |

### 📡 Telemetry Feedback (from KSP → hardware)
| Feature                         | Supported | Notes |
|--------------------------------|-----------|-------|
| Action Group States (AG1–AG10) | ✅        | Allows LED indicators |
| SAS Mode                       | ✅        | E.g., Prograde, Retrograde, Hold |
| SAS/RCS Active Status          | ✅        | Can light toggle switches or LEDs |
| Lights/Gear/Brakes Status      | ✅        | Good for feedback panels |
| Current Flight Mode            | ✅        | Orbital, Surface, Target |
| Altitude                       | ✅        | Surface or sea level |
| Vertical Speed                 | ✅        | Useful for VSI or gauge |
| Apoapsis / Periapsis           | ✅        | Orbit display options |
| Orbital Period                 | ✅        | |
| Time to Apoapsis / Periapsis  | ✅        | |
| Time to Node / Burn Duration  | ✅        | Useful for maneuver planning |
| Remaining Delta-V             | ✅        | Stage or total delta-V |
| Fuel / Oxidizer / Monoprop     | ✅        | Resource levels, total only |
| Electric Charge                | ✅        | Useful for power warning LEDs |

---

## 🚧 What KSR Does *Not* Expose (But kRPC C-nano Can)
These are **unavailable in KSR**, but can be queried using **kRPC C-nano**:

| Feature                  | Available in C-nano | Notes |
|--------------------------|---------------------|-------|
| Stage Lock Status        | ✅                  | Can drive a 🔒 LED or icon |
| Solar Panel Status       | ✅                  | Extended/retracted state |
| Science Experiment Status| ✅                  | Deployed, used, etc. |
| Crew Info                | ✅                  | Not typically needed for panel, useful for MFD |
| Part-Level Resource Info | ✅                  | E.g. fuel per tank or engine |
| Engine Thrust / Flameout | ✅                  | Could indicate failure state |
| Detailed Orbit Info      | ✅                  | Inclination, eccentricity, etc. |
| Target Info              | ✅                  | Relative velocity, distance |
| Autopilot State          | ✅                  | More fine-grained than SAS/RCS |

These require:
- Loading the appropriate `.proto` service definitions
- Enough memory for response parsing
- Possibly a slower polling rate for performance

---

## 📊 MFD vs. Panel Usage Guidance

### 🕹️ Physical Panel — Recommended for:
- Action group state LEDs ✅
- SAS mode or state LEDs ✅
- Stage lock 🔒 (via kRPC) ✅
- Gear, light, brake toggles ✅
- RCS/SAS active status ✅

### 📺 MFD Display — Ideal for:
- Altitude, velocity, delta-V (via KSR)
- Orbit info (apo, peri, time to node)
- Science experiment states (via kRPC)
- Solar panel deployed state (via kRPC)
- System messages / warnings
- Crew info or docking details (if desired)

---

## 💬 Summary
- **KSR** supports most common telemetry and controls needed for cockpit hardware.
- **kRPC C-nano** expands that access to lower-level and more detailed game states.
- The best approach is a **hybrid design**:
  - Use **KSR** for panel + fast response inputs
  - Use **kRPC (C-nano or bridge)** for MFD feedback and advanced info
- Starting with KSR allows you to iterate quickly; add kRPC later as needs grow.


# --- docs/design/KSP_Protocols.md ---

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

# --- docs/design/Pin_Map.md ---

# KSP-Controller Pin Map

This document lists the pin assignments for the ESP32-S3 Reverse TFT Feather and attached peripherals.

| Function            | Pin         | Notes                              |
|---------------------|-------------|------------------------------------|
| TFT Display (built-in) | GPIO40-47 | Managed by board definition        |
| NeoKey I2C (QT)     | GPIO6 (SCL), GPIO5 (SDA) | Uses I2C0                        |
| Adalogger (RTC + SD)| SPI (GPIO36/35/37), GPIO21 | SPI interface + optional I2C   |
| Ethernet FeatherWing| SPI Shared, CS=GPIO10     | SPI w/ separate CS               |
| NeoPixel            | GPIO48      | Can be re-assigned if needed       |
| D0, D1, D2 Buttons  | GPIO0, GPIO1, GPIO2       | Digital inputs w/ pullups        |
| Encoder A/B/SW      | TBD         | Will require 3 GPIOs               |
| Analog Inputs       | TBD         | For sliders/pots                   |

---

## 📋 Annotated Pinout Notes (from pinout.md)

# 📌 GPIO Pinout

## 🧠 ESP32-S3 Feather (Adafruit 5691) — GPIO Pin Usage

| **Function**         | **GPIO Pin** | **Notes**                          |
|----------------------|--------------|------------------------------------|
| Built-in TFT CS      | GPIO 5       | ST7789 SPI Chip Select             |
| TFT DC               | GPIO 6       | Data/Command                       |
| TFT RST              | GPIO 7       | Reset                              |
| SPI MOSI             | GPIO 35      | Shared with display & Ethernet     |
| SPI SCK              | GPIO 36      | Shared with display & Ethernet     |
| SPI MISO             | GPIO 37      | Used by Ethernet only              |
| Ethernet CS          | GPIO 10      | W5500 SPI Chip Select              |
| I2C SDA              | GPIO 3       | Used by NeoKey QT                  |
| I2C SCL              | GPIO 4       | Used by NeoKey QT                  |
| NeoKey INT (optional)| -            | Not needed unless interrupts used  |
| Available GPIOs      | GPIO 8–20+   | For buttons, encoders, LEDs        |

## 📌 Default Pins Used by Onboard Hardware

| Function          | Pin  | Notes                      |
|------------------|------|----------------------------|
| TFT CS           | D7   | Chip Select for TFT        |
| TFT DC           | D8   | Command/Data select        |
| TFT Backlight    | D13  | PWM brightness control     |
| Button A         | D0   | Left button                |
| Button B         | D3   | Center button              |
| Button C         | D38  | Right button               |
| I2C SDA          | D2   | Shared with MAX17048       |
| I2C SCL          | D1   | Shared with MAX17048       |

# --- docs/design/README.md ---

# KSP-Controller Design Documents

This folder contains planning documents and architectural specifications for the KSP-Controller firmware project.

## Contents

- [CLI_Spec.md](CLI_Spec.md) – Command-line grammar and behavior specification
- [Pin_Map.md](Pin_Map.md) – Pin assignments and hardware connections
- [Capabilities.md](Capabilities.md) – Supported features, interfaces, and constraints
- [Architecture.md](Architecture.md) – High-level system architecture and module relationships
- [Config_Structure.md](Config_Structure.md) – JSON/EEPROM configuration layout and fallback logic

# --- docs/design/Storage_Strategy.md ---

# 📦 Storage Strategy

This document outlines the various storage options available on the ESP32-S3 Reverse TFT Feather and associated FeatherWings in your KSP Controller project. Each storage type is broken down by architecture, use case, performance, endurance, and ideal scenarios.

---

## 🧠 1. Internal Flash Memory

- **Type**: QSPI Flash (4MB total)
- **API**: SPIFFS / LittleFS, Preferences, direct access
- **Typical Use**: Firmware, configuration data, occasional logs
- **Size**: ~1–2MB usable after firmware
- **Speed**: Fast (tens of MB/s)
- **Endurance**: ~100,000 writes per sector

**✅ Best For**:
- Infrequently updated config
- Lightweight local files
- Static assets (images/fonts if not too large)

---

## 📥 2. EEPROM Emulation

- **Type**: Virtual EEPROM within flash sectors
- **API**: `Preferences.h` (recommended), `EEPROM.h` (legacy)
- **Typical Use**: Key/value settings, state tracking, HID profile IDs
- **Size**: ~4KB to 100KB
- **Speed**: Slower than RAM, fast enough for config
- **Endurance**: ~100,000 writes per sector

**✅ Best For**:
- Persistent mode memory (last profile, boot flags)
- Small key/value data
- Reliable atomic reads/writes

---

## 💾 3. microSD Card (Adalogger FeatherWing)

- **Type**: SPI-connected removable Flash
- **API**: `SD.h`, `SdFat.h`
- **Typical Use**: Log files, config backups, profile sets, large datasets
- **Size**: Up to **32GB FAT32** officially (larger with exFAT via `SdFat`)
- **Speed**: 2–10 MB/s typical (SPI limited)
- **Endurance**: 10,000–100,000 writes per block

**✅ Best For**:
- Rotating logs / timestamped telemetry
- Full HID and user profile backups
- Assets and large config files

---

## 🧰 Flash & SD Access APIs: Use-Case Comparison

| Storage Type | API | Best For | Pros | Cons |
|--------------|-----|----------|------|------|
| **Flash** (Key/Value) | `Preferences.h` | Boot mode, selected profile, config flags | Atomic, namespaced, robust | ~4KB per namespace |
| **Flash** (Legacy) | `EEPROM.h` | Porting older code | Simple, minimal | Not robust, needs manual `.commit()` |
| **Flash** (Files) | `LittleFS` | JSON configs, local logs, small assets | File structure, better than SPIFFS | Slower, needs mount/format |
| **SD Card** (Generic) | `SD.h` | Simple data logging, config backups | Easy to use | Less performance tuning |
| **SD Card** (Advanced) | `SdFat.h` | Fast or large-volume logging | Fast, exFAT, optimized | More complex, lower-level |

---

## ⚙️ Recommendations by Task

| Task / Use Case              | Best API             | Storage     | Rationale / Notes |
|-----------------------------|----------------------|-------------|-------------------|
| Boot state, flags           | `Preferences.h`      | 🔒 Flash     | Stored in internal flash; safe to write infrequently; persistent & atomic |
| Current profile ID          | `Preferences.h`      | 🔒 Flash     | Small scalar setting; fast access |
| All profile data (JSON)     | `LittleFS` or `SD.h` | 🔄 Flash / 💾 SD | Flash for fast access; SD for storage capacity and versioning |
| Debug logs                  | `SdFat.h`            | 💾 SD        | Frequent or high-volume writes; SD is removable |
| Backup files (e.g. configs) | `SD.h` or `LittleFS` | 🔄 Flash / 💾 SD | Choose based on file size and how often backups occur |
| Static assets (fonts/images)| `LittleFS`           | 🔒 Flash     | Persistent and fast reads for UI |
| Asset streaming (media)     | `SD.h` or `SdFat.h`  | 💾 SD        | Use SD for size capacity and removable access |
| Firmware and binaries       | *N/A (platform-managed)* | 🔒 Flash | Stored in flash via OTA or bootloader; can't use SD |
| HID profile (current only)  | `Preferences.h`      | 🔒 Flash     | Fast, atomic access for switching profiles |
| HID profiles (all saved)    | `SD.h`               | 💾 SD        | Versionable, large, external storage |
| JSON config & backups       | `SD.h` or `LittleFS` | 🔄 Flash / 💾 SD | JSON is flexible; SD allows offloading backups |
| Boot mode & startup flags   | `Preferences.h`      | 🔒 Flash     | Very limited writes; suitable for preferences |

**Legend:**
- 🔒 Flash
- 💾 SD
- 🔄 Either (depending on space, volatility, and speed)

---

## ✍ Notes

- ⚠ **Internal flash and EEPROM share erase blocks** — frequent EEPROM writes can reduce flash lifespan.
- ⚡ **microSD supports large log files** but requires proper write buffering and mount handling.
- 🚫 **EEPROM is not suitable for large structured config or logs**.

---

## 🧠 Flash Memory & Wear Leveling Options

### 🔒 1. **Internal Flash (ESP32-S3)**
ESP32’s internal flash uses **raw NOR flash memory** (external SPI chip but "internal" to the board logic). It **does not** do automatic wear leveling unless you're using a file system that implements it.

#### ✅ File System Layer (Recommended):
- **`LittleFS`**: YES, includes **basic wear leveling** and block management.
- **`SPIFFS`**: YES, but deprecated and inferior to LittleFS in terms of performance and reliability.
- ✅ **Best option if you're storing config/log files**.

#### ❌ Key-Value APIs (No Wear Leveling):
- **`Preferences.h`** and **`EEPROM.h`** write directly to specific flash pages/sectors.
- These do *not* perform wear leveling. Repeated writes to the same key or address can degrade those sectors quickly.

**Recommendation:** Rotate variable names (or pad structures) manually to reduce stress if using `Preferences`.

---

### 💾 2. **SD Card**
SD cards **do** implement wear leveling *internally* (via their controller firmware), especially **high-endurance** models designed for dashcams or data logging.

- **You don’t have to manage it yourself**.
- **Still** recommended to avoid excessive file rewrites and use proper **buffering** or **append-only** strategies.

---

### 🔄 3. **External Flash via QSPI (not on your current board)**
Some boards (like Feather RP2040 or ESP32 with external QSPI NOR/NAND) allow **more advanced wear leveling** with full **Flash Translation Layers (FTL)** or **FatFS** on top.

You’re not using these currently, but worth noting if you ever need **larger writable flash**.

---

## ✅ Summary: What to Use for Wear-Leveling

| API / System      | Wear-Leveling? | Suitable For               | Notes |
|-------------------|----------------|----------------------------|-------|
| `Preferences.h`   | ❌              | Flags, boot state          | Limited writes only |
| `EEPROM.h`        | ❌              | Legacy simple values       | Same risk |
| `LittleFS`        | ✅              | Configs, logs, small assets| Best balance |
| `SD.h`, `SdFat.h` | ✅ (internal)   | Logging, backups           | Use high-endurance cards |
| SPIFFS (legacy)   | ✅ (basic)      | Deprecated                 | Use LittleFS instead |

---

## 📝 Notes

- Always **flush buffers** for log safety on SD (`file.flush()` or `fs.close()`).
- Use **`Preferences`** over `EEPROM` for new projects.
- Prefer **LittleFS** over SPIFFS if available.







# --- docs/design/Switch_Keycap_Selection.md ---

# 🎛️ Prototyping Switch & Keycap Selection Guide

This guide documents the evaluation process for choosing **mechanical switches** and **keycaps** suitable for the KSP Controller project, with emphasis on **control panel usability**, **RGB visibility**, and **tactile feedback**. All switches discussed are MX-compatible and intended for use with the **NeoKey 1x4 STEMMA QT** board.

---

## ✅ Target Use Case

- Not intended for typing
- Prioritize **tactile feedback**, low actuation force, and **light diffusion**
- Must be **MX-compatible**
- RGB compatibility preferred (clear/transparent housing)

---

## 🔘 Recommended Switches

| Switch               | Type     | Feel                | RGB Friendly | Pros                                  | Cost Estimate |
|----------------------|----------|---------------------|--------------|----------------------------------------|----------------|
| **Gateron Clear**    | Linear   | Light, smooth       | ✅ Excellent  | Very soft press, RGB shines through   | ~$0.30–$0.50   |
| **Kailh Box Brown**  | Tactile  | Mild bump           | ✅ Excellent  | Tactile w/o click, dampened feel      | ~$0.40–$0.70   |
| **Kailh Box White**  | Clicky   | Tactile + click     | ✅ Good       | Audible feedback, crisp bump          | ~$0.40–$0.60   |
| **Outemu Ice Blue**  | Tactile  | Medium bump         | ✅ Excellent  | Sharp tactility, translucent housing  | ~$0.30–$0.50   |

---

## ⚙️ Switch Comparison Notes

- **Gateron Clear** is ideal for fast-tap buttons with minimal finger strain.
- **Box Brown** offers a good balance between tactility and silence.
- **Box White** is great for a tactile + audible "click," but may be too loud in shared spaces.
- **Outemu Ice Blue** gives satisfying tactility with full RGB support.

---

## ⌨️ Keycap Selection Guidelines

| Feature               | Preference                | Notes                                             |
|------------------------|---------------------------|----------------------------------------------------|
| **Mount Type**         | MX stem                   | Required for all recommended switches              |
| **Top Material**       | Opaque or lightly translucent | Allows selective RGB feedback                     |
| **Profile**            | DSA or SA (low profile)   | Improves control panel aesthetics & usability      |
| **Legends**            | Blank or side-printed     | Avoids visual clutter and supports clean lighting  |

> Current favorites: **Adafruit #5112** (diffused top with light pipe), or **“pudding-style” caps** for clear RGB diffusion if labeled legends are needed.

---

## 📝 Notes

- RGB LEDs beneath switches should be addressable (e.g., NeoPixels).
- Switch feel is subjective—**a variety tester kit is recommended**.
- Final switch choice may vary between button groups (e.g., mode switches vs. staging).

---

## 🔗 Related Design Documents

- [Controller_Design_Spec.md](./Controller_Design_Spec.md)
- [Capabilities.md](./Capabilities.md)
- [Pin_Map.md](./Pin_Map.md)

# --- docs/design/display-ui-notes.md ---

# 🖥 Display UI Notes

_Sketches and layouts for TFT/OLED screen menus and telemetry zones._

# --- docs/dev-log.md ---

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
### 🔄 KSP Simpit Revamped Compatibility (Current Hardware Support)

Your current hardware will support most telemetry "pull" features:

**TFT Display (5691)**:
- Altitude, velocity, apoapsis/periapsis, SAS mode, time to node, throttle level

**NeoKey 1x4 RGB Buttons (4980)**:
- Gear, brakes, lights, SAS, RCS state indicators via color

**SD Logging** (planned):
- Telemetry capture to file (altitude, mission time, etc.)

**(Not Yet Purchased)**:
- I²C RGB Encoders for camera/SAS feedback
- Additional OLEDs or segmented indicators for mode views

---

### 🔁 Telemetry Loop Sketch (Firmware Concept)

```cpp
void loop() {
  // Check for incoming Simpit messages
  if (Serial.available()) {
    parseKSPPacket(Serial.read());
  }

  // Update displays with last-known data
  displayTFT.setAltitude(ksp.altitude);
  displayTFT.setVelocity(ksp.velocity);
  displayTFT.setThrottle(ksp.throttle);
  displayTFT.setSASMode(ksp.sasMode);

  // Update NeoKey LEDs based on KSP state
  updateButtonLEDs(ksp.gear, ksp.brakes, ksp.rcs, ksp.lights);

  // Handle user input (buttons/encoders)
  processInputs();
}
```

---

### 🗺 Example Mapping (`config.json`)

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

This allows UI assignments to be changed without rebuilding firmware.

➡️ Next: Add docs/protocols.md to capture HID, serial, and Simpit mapping.

---

ℹ️ These upgrades allow the controller to be reconfigurable via SD card, easier to debug/log, and modular for adding rotary encoders, motorized input devices, and more flexible I²C/GPIO input chains.

# --- docs/gitignore-notes.md ---

# 📝 .gitignore Pattern Documentation

This document explains each pattern used in the project’s `.gitignore` file and why it’s useful.

## 🧰 General System & Editor Junk

- `.DS_Store`: macOS Finder metadata
- `Thumbs.db`: Windows Explorer thumbnail cache
- `*.bak`, `*.tmp`: Editor backup and temp files
- `*.log`: Output logs from builds or scripts
- `*.swp`: Vim swap files

## ⚙️ PlatformIO / VS Code Artifacts

- `.pio/`: PlatformIO build folder
- `.vscode/`: VS Code user config (not project-specific)
- `*.elf`, `*.bin`, `*.hex`: Firmware outputs
- `*.map`, `*.d`: Debug and dependency maps

## 🔌 Arduino Sketch Outputs

- `*.ino.*`, `*.cpp.*`, `*.o`: Intermediate preprocessed/compiled code

## 📦 Archives & Disk Images

- `*.zip`, `*.tar.gz`, `*.7z`, `*.rar`: Local backups or downloads
- `*.img`, `*.iso`: OS or SD card images

## 📐 PCB / CAD Tools

- `*.autosave`, `*.backup`, `*.bak`: Autosaves from design tools
- `*.sch-bak`, `*.pcb-bak`: KiCad backups

## 🐍 Python Scripts & Caches

- `__pycache__/`: Python bytecode folder

## 🔀 Merge Conflict Leftovers

- `*.orig`, `*.rej`, `*~`: Unwanted leftovers from failed merges or patches

# --- docs/hardware/Adalogger_FeatherWing.md ---

# Adalogger FeatherWing (PID 2922)

**Link**: https://www.adafruit.com/product/2922  
**Features**:
- MicroSD slot (SPI)
- DS3231 RTC (I2C)

## Pin Usage

- SD SPI: MOSI (GPIO36), MISO (GPIO35), SCK (GPIO37), CS (GPIO21)
- RTC I2C: SDA/SCL (shared with NeoKey if using QT port)

## Notes

- Battery backup for RTC (CR1220)
- Uses `RTClib` and `SD` or `SdFat` libraries

## Libraries

- `RTClib`
- `SdFat` or `SD`

## ❗ Technical Limitations & Notes

- ⚠️ RTC (DS3231) uses I2C — ensure no address conflicts with NeoKey or other I2C devices.
- ⚠️ SD Card uses SPI — must use a **dedicated CS pin** if Ethernet is also used on SPI.
---

## 📘 Technical Summary from Datasheet (Adafruit Adalogger FeatherWing)

- **Main Features**:
  - MicroSD slot for FAT32-formatted cards
  - DS3231 Precision Real-Time Clock (RTC) with temperature compensation
  - Coin cell battery backup support (for RTC)
  - 32KHz output pin (optional)
  - Works with all Feather boards via stackable headers

- **Pin Assignments**:
  - **RTC (DS3231)**: communicates over I2C
    - I2C SDA: shared (typically GPIO 2)
    - I2C SCL: shared (typically GPIO 1)
  - **microSD card**: communicates over SPI
    - Default Chip Select (CS) pin: **GPIO 10**
    - Can be rerouted via jumper and trace cut
  - Additional RTC Pins:
    - **SQW**: Square wave output (optional)
    - **32K**: Optional clock output pin

- **Battery**:
  - Supports CR1220 coin cell for RTC backup
  - Not rechargeable—just a backup for RTC during power loss

- **Libraries**:
  - Arduino: `RTClib`, `SD`
  - CircuitPython: `adafruit_ds3231`, `adafruit_sdcard`

- **Power Considerations**:
  - Powered via Feather 3.3V rail
  - Keep in mind cumulative draw if using multiple FeatherWings

- **Physical Notes**:
  - Designed to fit the FeatherWing form factor
  - Stackable, but must ensure CS/I2C conflicts are avoided


# --- docs/hardware/BOM.md ---

# 📦 Bill of Materials

_This file will track all hardware components, links, and quantities._

## 🧾 Bill of Materials (Phase 1 Dev Setup)

| **Component**                                | **Qty** | **Product ID / Link**                             | **Notes**                                |
|---------------------------------------------|--------|--------------------------------------------------|------------------------------------------|
| ESP32-S3 Reverse TFT Feather                 | 1      | [Adafruit 5691](https://www.adafruit.com/product/5691) | Main MCU with display                     |
| Ethernet FeatherWing (W5500)                | 1      | [Adafruit 3201](https://www.adafruit.com/product/3201) | Optional wired networking                 |
| NeoKey 1x4 QT I2C Mechanical Keypad         | 1      | [Adafruit 4980](https://www.adafruit.com/product/4980) | Input + RGB feedback                      |
| FeatherWing Doubler                         | 1      | [Adafruit 2890](https://www.adafruit.com/product/2890) | Side-by-side stacking                     |
| Feather Stacking Headers                    | 1      | [Adafruit 2830](https://www.adafruit.com/product/2830) | For stacking Feather and Wings           |
| Breadboard Kit                              | 1      | Bojack (Amazon, X002TQ7ITZ)                      | Jumper wires, breadboard, accessories     |
| USB-C Cable                                 | 1      | Any USB-C cable supporting data                 | For programming and power                 |

> 💡 Add tactile buttons, rotary encoder, or OLED later as needed.

# --- docs/hardware/ESP32-S3_Feather.md ---

# ESP32-S3 Reverse TFT Feather (Adafruit PID 5691)

**Link**: https://www.adafruit.com/product/5691  
**MCU**: ESP32-S3 (dual-core 240 MHz, 512KB RAM + 8MB PSRAM)  
**Display**: Built-in 240x135 TFT with SPI ILI9341  
**USB**: USB-C with native USB OTG support (CDC, HID, etc.)

## GPIO Overview

| GPIO | Pin # | Notes |
|:---:|:---:|---|
| `00`-`19` | | Usable for general I/O|
| `21` | | Usable for general I/O|
| `33`-`48` | | Usable for general I/O|
| `06` | | `SCL0` (used for QT port) |
| `05` | | `SDA0` (used for QT port) |
| `10` | | `CS` (used for Ethernet or `SPI` device) |
| `36` | | `SPI`:`MOSI` |
| `35` | | `SPI`:`MISO`|
| `37` | | `SPI`:`SCK`|
| `21` | | SD Card `CS` (on Adalogger) |
| `40`-`47` | | built-in TFT |

## Notes

- GPIO40–47 used for built-in TFT and are not recommended for external use.
- TFT and NeoPixel are pre-wired on board.
- Bootloader supports TinyUSB (CDC + HID).

## Libraries

- `Adafruit_TinyUSB`
- `Adafruit_GFX`, `Adafruit_ILI9341`

## ❗ Technical Limitations & Notes

- 🚫 Does **not** support Classic Bluetooth — only BLE is available.
- ⚠️ GPIO40–47 are reserved for the built-in TFT display and **should not be used for external peripherals**.
- ⚠️ ESP32-S3 has **fewer ADC channels** than the standard ESP32. Plan analog inputs accordingly.
- ✅ Native USB supports **CDC, HID, and Mass Storage** via TinyUSB.

---

## 📘 ESP32-S3 Reverse TFT Feather – Adafruit Learn Guide Highlights

- **Display**: 1.14" 240×135 TFT (ST7789), rear-mounted
- **Microcontroller**: ESP32-S3 @ 240MHz, dual-core, with BLE and Wi-Fi
- **USB-C**: Native USB interface for HID, CDC, and power
- **Memory**: 4MB Flash, 2MB PSRAM
- **Power Options**: USB-C, LiPoly, with battery monitoring (MAX17048)
- **Default Pin Assignments**:
  - TFT CS: GPIO 7
  - TFT DC: GPIO 8
  - TFT Backlight: GPIO 13
  - I2C: GPIO 1 (SCL), GPIO 2 (SDA)
  - User buttons: GPIOs 0, 3, 38
- **Notes**:
  - Use **ADC1 only** when Wi-Fi or BLE is active
  - No Classic Bluetooth (BLE only)
  - UF2 bootloader supports drag-and-drop recovery

# --- docs/hardware/Ethernet_FeatherWing.md ---

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

# --- docs/hardware/NeoKey_1x4.md ---

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

# --- docs/hardware/README.md ---

# KSP-Controller Hardware Reference

This directory contains reference information about all hardware components used in the KSP-Controller project. It includes pinouts, connection notes, library dependencies, and links to datasheets or product pages.

# --- docs/new-discussion/README.md ---

# KSP Controller Project (Post-SendCutSend Phase)

This repository documents the continued development of a custom Kerbal Space Program (KSP) control panel following the completion of initial laser-cut panels (ordered via SendCutSend). The goal is a modular, intelligent input device that integrates USB HID, Simpit Revamped telemetry, and context-aware feedback such as RGB lighting and motorized sliders.

## Sections

- [Goals & Philosophy](goals.md)
- [Hardware Overview](hardware.md)
- [Design Strategy](design_strategy.md)
- [KSP Integration Plan](ksp_integration.md)
- [Expansion Thoughts](expansion.md)
- [Emotional Reflection](reflection.md)
# --- docs/new-discussion/design_strategy.md ---

# Design Strategy

## Physical Design

- Modules are kept compact and reusable (e.g., 1x4 key clusters)
- Front panel cut with tight-fitting cutouts for seamless device integration
- Mounting tabs for structural support with small support rings and standoffs

## Electrical

- I2C used for all key and encoder input boards (NeoKey, 4991)
- RGB used for context feedback (e.g., gear up/down, SAS, modes)
- Simpit telemetry data drives feedback (RGB, slider)

## Practical Considerations

- Panel and hole tolerances adjusted for powder coating (~0.1–0.2mm)
- Aluminum panel is main interface, Delrin or acrylic used as non-conductive backing
- Screw sizing focused around M3 or US #4 hardware (common at hardware stores)
# --- docs/new-discussion/expansion.md ---

# Future Expansion Ideas

## Modular Keyboards

- Design custom PCBs with Choc V1 switches and RGB per-key lighting
- Connect over I2C using QT connectors
- Standardize to 1x4 or 2x2 modules for reuse and simplicity

## Breakout/Socketed Logic Boards

- Socket-mounted Feather + Ethernet + Logging FeatherWing
- Breakout connections for analog inputs (joysticks, throttle, etc.)
- Could evolve into a custom logic board (optional)

## Additional Components

- Add OLED or TFT displays for:
  - Contextual readouts
  - Status display (e.g., fuel, altitude, burn timer)
- Plan for input multiplexing or port expanders (e.g., MCP23017)
# --- docs/new-discussion/goals.md ---

# Project Goals & Philosophy

- Build a compact, modular KSP control panel that integrates:
  - USB HID inputs (keyboard/gamepad style)
  - Simpit Revamped USB CDC feedback
  - RGB and motorized feedback (e.g., throttle)
- Avoid unnecessary complexity; only add controls that improve gameplay or immersion
- Respect emotional connection to KSP1 and the anticipation of building
- Enable mode-switching functionality with RGB and/or OLED/TFT displays

## Philosophical Approach

- Don't replace the keyboard/mouse unless there's clear benefit
- Prioritize controls that provide physical or contextual feedback better than screen-only UI
- Embrace anticipation and gradual build progress as part of the joy
# --- docs/new-discussion/hardware.md ---

# Hardware Overview

## Microcontroller

- **Adafruit Feather ESP32-S3 TFT Reverse**
  - USB HID + USB CDC support
  - Built-in display, USB-C, and Qwiic/STEMMA QT

## Add-on FeatherWings

- **Ethernet FeatherWing**
- **Logging FeatherWing** (RTC + microSD)

## Input Devices

- **Adafruit NeoKey 1x4 QT (4980)** with RGB
- **2x Rotary Encoders with I2C Breakouts (4991)**
- **Future: Motorized linear potentiometer for throttle**

## Panels

- **Top panel:** Aluminum 5052 (1.6mm), textured black powdercoat
- **Secondary plate:** Delrin (same DXF)
- **Backplate:** Clear acrylic, mounts to standoffs
# --- docs/new-discussion/ksp_integration.md ---

# KSP Integration Plan

## Game Input/Output Methods

| Function Type        | Technology Used     |
|----------------------|---------------------|
| Primary Controls     | USB HID (Gamepad/KB) |
| Secondary Commands   | Simpit Revamped (USB CDC) |
| Game Feedback        | Simpit -> RGB/TFT/OLED |
| Optional Displays    | iPad/PC via Telemachus-style mod |

## Features to Implement

- Motorized throttle driven by Simpit telemetry
- RGB lighting for:
  - Landing gear status
  - RCS/SAS toggle indicators
  - Stage arming or action group state
- OLED for mode/context display or cycling readouts
# --- docs/new-discussion/reflection.md ---

# Emotional Reflection & Project Philosophy

> “The anticipation is better than opening the present sometimes.”

## Notes

- The project isn't just about replacing controls — it's about *making the experience richer*
- Emotional investment is strong, even if KSP isn't currently played often
- It’s okay for this to be a hobby, not just a tool
- Building the panel is as valuable as using it

## Key Takeaway

> This project is powered by curiosity, not obligation.
> Every part you assemble, code you write, and idea you test is already a win.