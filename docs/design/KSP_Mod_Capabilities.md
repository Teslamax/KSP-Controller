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

