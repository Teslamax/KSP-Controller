# KSP-Controller
Custom KSP controller (USB-HID with data displays, microcontroller driven)


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
| **RGB-Lit Buttons** | Indicate status of landing gear, brakes, RCS, SAS | Provides immediate visual feedback |
| **RGB-Lit Rotary Encoders** | Used for SAS mode and camera mode selection | Blinks briefly when a mode is switched |

### **Controls**
| **Control** | **Function** | **Notes** |
|-----------|------------|----------|
| **2x Joysticks (JH-D400X-R4)** | **Translation (X, Y, Z) & Rotation (Pitch, Yaw, Roll)** | One for translation, one for rotation |
| **Linear Potentiometer (Throttle)** | **Primary throttle control** | Motorized for self-calibration & auto-throttle |
| **Rotary Encoder (Throttle Limiter)** | Limits max throttle | Shows limit on OLED |
| **Rotary Encoder (Camera Mode)** | Cycles through camera views | Click toggles Free Camera |
| **Rotary Encoder (SAS Mode)** | Changes SAS mode | RGB-lit for mode indication |
| **20x Action Group Buttons** | Used for custom game functions | Split into 2x10 layout |
| **Momentary/Toggling Throttle Cutoff** | Disables throttle input | Useful for automation |
| **Docking Mode Button** | Enables fine-tuned docking mode | LED-lit for status indication |

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

## **📝 Appendix: Rejected Features & Why**
| **Feature Considered** | **Reason for Rejection** |
|------------------|------------------|
| **Built-in AC-DC PSU (IEC C7/C8)** | Too complex, unnecessary for now |
| **Fully Integrated PoE on PCB** | Using external UCTRONICS splitter instead |
| **Dedicated Launch Countdown Display** | Could be implemented later in software |
| **Haptic Feedback** | Not necessary, increases cost & complexity |
| **RGB-lit Rotary Encoders for Throttle** | Not needed for function, may be added later |

---

## **📌 Next Steps**
- **Refine internal wiring design (keystone vs. panel-mount connectors)**
- **Design a PCB layout for switch & encoder connections**
- **Begin prototype assembly with Teensy 4.1 & PoE splitter**

---

🚀 **This document provides a structured plan for the controller build, ensuring a clean design and effective integration. Let me know if you need revisions!**

