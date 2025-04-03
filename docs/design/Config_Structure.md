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
