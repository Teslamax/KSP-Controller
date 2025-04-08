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
