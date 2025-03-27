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
