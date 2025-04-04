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

| Task / Use Case              | Best API             | Storage     | Rationale / Notes |
|-----------------------------|----------------------|-------------|-------------------|
| Firmware and binaries       | *N/A (platform-managed)* | 🔒 Flash | Stored in flash via OTA or bootloader; can't use SD |
| Boot mode & startup flags   | `Preferences.h`      | 🔒 Flash     | Very limited writes; suitable for preferences |
| Boot state, flags           | `Preferences.h`      | 🔒 Flash     | Stored in internal flash; safe to write infrequently; persistent & atomic |
| Current profile ID          | `Preferences.h`      | 🔒 Flash     | Small scalar setting; fast access |
| Static assets (fonts/images)| `LittleFS`           | 🔒 Flash     | Persistent and fast reads for UI |
| HID profile (current only)  | `Preferences.h`      | 🔒 Flash     | Fast, atomic access for switching profiles |
| All profile data (JSON)     | `LittleFS` or `SD.h` | 🔄 Flash / 💾 SD | Flash for fast access; SD for storage capacity and versioning |
| Backup files (e.g. configs) | `SD.h` or `LittleFS` | 🔄 Flash / 💾 SD | Choose based on file size and how often backups occur |
| JSON config & backups       | `SD.h` or `LittleFS` | 🔄 Flash / 💾 SD | JSON is flexible; SD allows offloading backups |
| Debug logs                  | `SdFat.h`            | 💾 SD        | Frequent or high-volume writes; SD is removable |
| Asset streaming (media)     | `SD.h` or `SdFat.h`  | 💾 SD        | Use SD for size capacity and removable access |
| HID profiles (all saved)    | `SD.h`               | 💾 SD        | Versionable, large, external storage |

**Legend:**
- 🔒 Flash
- 💾 SD
- 🔄 Either (depending on space, volatility, and speed)

---

## ✍ Notes

- ⚠ **Internal flash and EEPROM share erase blocks** — frequent EEPROM writes can reduce flash lifespan.
- ⚡ **microSD supports large log files** but requires proper write buffering and mount handling.
- 🚫 **EEPROM is not suitable for large structured config or logs**.

---

Let me know if you want this integrated with an existing doc later or refactored by storage type instead of task!


---

## 🔁 Write-Cycle and Endurance Notes

| Storage Type | API           | Write Endurance        | Notes |
|--------------|---------------|------------------------|-------|
| Flash (Internal) | `Preferences.h` | ~10,000 writes per 4KB sector | Wear leveling not automatic. Avoid frequent writes to same keys. |
| Flash (Internal) | `EEPROM.h`      | ~10,000 writes per 4KB sector | Requires manual `.commit()`; same wear limits as Preferences. |
| Flash (Internal) | `LittleFS`      | Moderate (varies by chip)    | Use with care for logging. Avoid frequent rewrites of same file. |
| SD Card         | `SD.h` / `SdFat.h` | Depends on card quality      | High-endurance cards recommended for logging. Usually 100k+ writes per block. |

---


## 🧩 Initialization & Mounting Notes

- `Preferences.h`: No mounting required. Key/value namespace system, safe for quick use.
- `EEPROM.h`: Requires `.begin(size)` and `.commit()` to finalize writes. Not atomic.
- `LittleFS`: Requires mounting (`LittleFS.begin()`) and optional formatting if first time.
- `SD.h`: Automatically mounts on `.begin(cs_pin)` but limited performance.
- `SdFat.h`: Must match card type (FAT16/32 or exFAT); fast but requires correct settings (e.g., SPI speed).

Be aware that improper initialization or failed mounting can crash or silently fail. Always check return values.
---

## 📝 Notes

- Always **flush buffers** for log safety on SD (`file.flush()` or `fs.close()`).
- Use **`Preferences`** over `EEPROM` for new projects.
- Prefer **LittleFS** over SPIFFS if available.

---

## 🧪 Example Use Cases

- `preferences_demo.ino`: Demonstrates reading/writing scalar values using `Preferences.h`.
- `eeprom_config.ino`: Legacy-style EEPROM storage (must call `.commit()`).
- `lfs_config_load.ino`: Loads and parses JSON config from `LittleFS`.
- `sd_logging.ino`: Writes time-stamped logs to an SD card using `SdFat`.

You can place these in `/firmware/examples/storage/` to organize test/demo code.
