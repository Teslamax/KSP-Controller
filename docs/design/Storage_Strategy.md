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

## 🔍 Recommendation Table

| Use Case                      | Recommended Storage        | Rationale |
|------------------------------|----------------------------|-----------|
| Boot state, last mode        | EEPROM / Preferences       | Persistent, atomic |
| HID profile (current only)   | EEPROM                     | Fast, small |
| HID profiles (all saved)     | SD Card                    | Larger, versionable |
| Debug logs                   | SD Card                    | Frequent writes, removable |
| JSON config & backups        | SD Card                    | Flexible format, space |
| Images / fonts (UI)          | Flash or SD                | Flash for speed, SD for size |
| Firmware & binaries          | Flash                      | Only supported location |

---

## ✍ Notes

- ⚠ **Internal flash and EEPROM share erase blocks** — frequent EEPROM writes can reduce flash lifespan.
- ⚡ **microSD supports large log files** but requires proper write buffering and mount handling.
- 🚫 **EEPROM is not suitable for large structured config or logs**.
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

| Task | Best API | Notes |
|------|----------|-------|
| Boot state, flags | `Preferences.h` | Stored in flash, safe to write infrequently |
| Current profile ID | `Preferences.h` | Small scalar |
| All profile data (JSON) | `LittleFS` or `SD.h` | Flash for fast access, SD for space |
| Telemetry / debug logs | `SdFat.h` | Especially if frequent or high-volume |
| Backup files | `SD.h` or `LittleFS` | Depending on size & permanence |
| Static assets (UI) | `LittleFS` | Fast read, persistent |
| Asset streaming (images, etc.) | `SD.h` or `SdFat.h` | Flash too small, use SD |

---

## 📝 Notes

- Always **flush buffers** for log safety on SD (`file.flush()` or `fs.close()`).
- Use **`Preferences`** over `EEPROM` for new projects.
- Prefer **LittleFS** over SPIFFS if available.
