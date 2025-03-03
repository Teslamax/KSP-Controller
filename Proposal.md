# **Comprehensive Project Proposal: KSP & Space Simulation Controller**

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

## **🛠 Features & Software Integration**
### **Implemented Features**
✔ **Throttle with auto-calibration** (Motorized Potentiometer)  
✔ **Rotary encoders for SAS & camera modes**  
✔ **OLED-based menu for settings & calibration**  
✔ **USB-HID profile selection (KSP, Elite Dangerous, Default USB-HID)**  
✔ **LED-lit feedback for mode toggles** (Landing Gear, RCS, etc.)  
✔ **Stage lock button with LED indicator**  

### **Planned Software Enhancements**
🚀 **Modular firmware to allow remapping of buttons & encoders**  
🚀 **Logging system for power usage & button presses**  
🚀 **Optional Ethernet-based IoT features** (remote status, integration with other systems)  

---

## **🔌 Integration with KSP Mods**
### **Primary Mod: Kerbal Simpit Revamped**
- Supports **bidirectional game data exchange**
- Enables **reading throttle, altitude, SAS modes, etc.**
- Allows **controlling SAS, RCS, lights, gear, action groups**

### **Future Expansion: kRPC Mod**
- More advanced scripting & telemetry
- Possible **custom autopilot & automation features**
- **More complex than Kerbal Simpit Revamped**, but allows full API access

---

## **🎮 USB Profiles & Game Compatibility**
### **Game Modes (Selectable via Menu System)**
| **Profile** | **Purpose** |
|-----------|-----------|
| **KSP Mode** | Uses Kerbal Simpit Revamped for full integration |
| **Elite Dangerous Mode** | Maps controls for 6DOF flight & combat |
| **Default USB-HID Mode** | Recognized as a standard joystick/gamepad |

---

## **📝 Appendix: Review of Past Decisions & Feature Summary**
### **Past Decisions & Justifications**
- **Motorized potentiometer chosen** for throttle due to calibration benefits.
- **Removed rotary throttle limiter** as motorized throttle provides necessary control.
- **Spring-loaded slider added** for fore/aft translation instead of repurposing joystick.
- **Precision Control Mode Button (Fine Control) replaced Docking Mode Button**, as it is more generally useful.
- **Stage Lock Button (LED-lit) added** to prevent accidental staging.
- **Ethernet (PoE) included** as an internal UCTRONICS splitter for power & optional data features.

### **Summary of All Planned Features**
- **Full joystick-based 6DOF control** with translation & rotation.
- **Motorized throttle with OLED display feedback.**
- **Customizable action groups (20 buttons, split into 2x10 layout).**
- **LED-lit toggle buttons for important functions (SAS, RCS, Gear, Brakes, Stage Lock).**
- **RGB rotary encoders for SAS & Camera Modes.**
- **TFT display for primary status readout (altitude, velocity, mode indicators).**
- **OLED menu system with a rotary encoder for settings & calibration.**
- **USB-C power with optional PoE backup.**
- **Future expansion via kRPC for full autopilot scripting support.**

---

## **📌 Next Steps**
- **Refine internal wiring design (keystone vs. panel-mount connectors).**
- **Design a PCB layout for switch & encoder connections.**
- **Begin prototype assembly with Teensy 4.1 & PoE splitter.**

---

🚀 **This document provides a structured plan for the controller build, ensuring a clean design and effective integration. Let me know if you need revisions!**

