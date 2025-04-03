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
