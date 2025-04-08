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