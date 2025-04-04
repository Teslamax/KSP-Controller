# ** KSP & Space Simulation Controller — System Design Specification**

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
### **What Really Needs to Be in This Project?**
- Essential **flight controls, throttle, and key spacecraft toggles** (SAS, RCS, lights, landing gear, brakes).
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
