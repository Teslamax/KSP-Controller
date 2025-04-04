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
| Boot state, flags           | `Preferences.h`      | 🔒 Flash     | Stored in internal flash; safe to write infrequently; persistent & atomic |
| Current profile ID          | `Preferences.h`      | 🔒 Flash     | Small scalar setting; fast access |
| All profile data (JSON)     | `LittleFS` or `SD.h` | 🔄 Flash / 💾 SD | Flash for fast access; SD for storage capacity and versioning |
| Debug logs                  | `SdFat.h`            | 💾 SD        | Frequent or high-volume writes; SD is removable |
| Backup files (e.g. configs) | `SD.h` or `LittleFS` | 🔄 Flash / 💾 SD | Choose based on file size and how often backups occur |
| Static assets (fonts/images)| `LittleFS`           | 🔒 Flash     | Persistent and fast reads for UI |
| Asset streaming (media)     | `SD.h` or `SdFat.h`  | 💾 SD        | Use SD for size capacity and removable access |
| Firmware and binaries       | *N/A (platform-managed)* | 🔒 Flash | Stored in flash via OTA or bootloader; can't use SD |
| HID profile (current only)  | `Preferences.h`      | 🔒 Flash     | Fast, atomic access for switching profiles |
| HID profiles (all saved)    | `SD.h`               | 💾 SD        | Versionable, large, external storage |
| JSON config & backups       | `SD.h` or `LittleFS` | 🔄 Flash / 💾 SD | JSON is flexible; SD allows offloading backups |
| Boot mode & startup flags   | `Preferences.h`      | 🔒 Flash     | Very limited writes; suitable for preferences |

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

## 🧠 Flash Memory & Wear Leveling Options

### 🔒 1. **Internal Flash (ESP32-S3)**
ESP32’s internal flash uses **raw NOR flash memory** (external SPI chip but "internal" to the board logic). It **does not** do automatic wear leveling unless you're using a file system that implements it.

#### ✅ File System Layer (Recommended):
- **`LittleFS`**: YES, includes **basic wear leveling** and block management.
- **`SPIFFS`**: YES, but deprecated and inferior to LittleFS in terms of performance and reliability.
- ✅ **Best option if you're storing config/log files**.

#### ❌ Key-Value APIs (No Wear Leveling):
- **`Preferences.h`** and **`EEPROM.h`** write directly to specific flash pages/sectors.
- These do *not* perform wear leveling. Repeated writes to the same key or address can degrade those sectors quickly.

**Recommendation:** Rotate variable names (or pad structures) manually to reduce stress if using `Preferences`.

---

### 💾 2. **SD Card**
SD cards **do** implement wear leveling *internally* (via their controller firmware), especially **high-endurance** models designed for dashcams or data logging.

- **You don’t have to manage it yourself**.
- **Still** recommended to avoid excessive file rewrites and use proper **buffering** or **append-only** strategies.

---

### 🔄 3. **External Flash via QSPI (not on your current board)**
Some boards (like Feather RP2040 or ESP32 with external QSPI NOR/NAND) allow **more advanced wear leveling** with full **Flash Translation Layers (FTL)** or **FatFS** on top.

You’re not using these currently, but worth noting if you ever need **larger writable flash**.

---

## ✅ Summary: What to Use for Wear-Leveling

| API / System      | Wear-Leveling? | Suitable For               | Notes |
|-------------------|----------------|----------------------------|-------|
| `Preferences.h`   | ❌              | Flags, boot state          | Limited writes only |
| `EEPROM.h`        | ❌              | Legacy simple values       | Same risk |
| `LittleFS`        | ✅              | Configs, logs, small assets| Best balance |
| `SD.h`, `SdFat.h` | ✅ (internal)   | Logging, backups           | Use high-endurance cards |
| SPIFFS (legacy)   | ✅ (basic)      | Deprecated                 | Use LittleFS instead |

---

## 📝 Notes

- Always **flush buffers** for log safety on SD (`file.flush()` or `fs.close()`).
- Use **`Preferences`** over `EEPROM` for new projects.
- Prefer **LittleFS** over SPIFFS if available.






