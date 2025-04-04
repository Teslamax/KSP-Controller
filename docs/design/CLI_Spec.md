# 💻 CLI System Specification – KSP Controller

This document outlines the command-line interface (CLI) and logging system architecture for the KSP & Space Simulation Controller.

---

## 🧩 Purpose

Provide a consistent, extensible, and fault-tolerant command interface for debugging, configuration, status display, and manual control.

---

## 🖧 Supported Interfaces

The CLI system is accessible over the following interfaces:

| Interface     | Purpose                      | Notes                        |
|---------------|------------------------------|------------------------------|
| USB CDC       | Primary debug interface      | Always active (if available) |
| Telnet (Ethernet/Wi-Fi) | Remote debugging     | CLI over IP stack            |
| BLE UART      | Wireless, limited platforms  | macOS/iOS BLE serial may be limited |
| TFT Display   | Output-only log/status view  | Button-controlled navigation |

---

## 🧠 Command Routing & Operator Model

A single shared command handler services all input interfaces. Interfaces pass commands to a **common parser**, and output is routed back to the correct origin or to all relevant outputs (e.g., logs).

### Operator Model

```
[ Input Interface ] --> [ Command Parser ] --> [ Operator Dispatcher ] --> [ Output & Log Streams ]
```

All interfaces feed into the same parser and handler, sharing:

- History buffer
- Log buffer (with timestamping)
- CLI grammar
- Command registry

---

## 🔤 CLI Grammar

```plaintext
<command> [arguments...] [flags]

Examples:
  status
  status json
  config save
  log level debug
  reboot
```

Supports:
- Command aliases
- Flags and switches (e.g., `--verbose`)
- Subcommands
- JSON output for machine-readable results

---

## 🧾 Command Categories

| Category        | Examples                        |
|----------------|----------------------------------|
| System Status   | `status`, `uptime`, `version`   |
| Config/Profile  | `config save`, `profile load`   |
| Network         | `ip`, `wifi status`, `dns`      |
| HID Mode        | `hid test`, `hid profile`       |
| Simpit Control  | `sim status`, `sim reset`       |
| Logging         | `log level`, `log clear`, `log tail` |
| Debug/Utility   | `i2c scan`, `pinmap`, `reboot`  |

---

## 📝 Logging System

Supports multi-channel log distribution:

| Channel     | Purpose                     | Notes                        |
|-------------|-----------------------------|------------------------------|
| USB CDC     | Verbose logs, errors        | Console output to host       |
| BLE UART    | Optional serial over BLE    | May require mobile viewer    |
| Telnet      | IP remote logs + CLI        | Can log to session or broadcast |
| TFT Display | Color-coded log viewer      | Scrollable via buttons       |
| SD Card     | Persistent log storage      | Log rotation + timestamping  |

### Log Levels
- DEBUG
- INFO
- WARNING
- ERROR
- CRITICAL

Logs include:
- Timestamps (from RTC/NTP)
- Source interface
- Severity level
- Optional emojis/symbols

---

## 🧮 Command History

- Shared across interfaces (except display)
- Recall via arrow keys (USB CDC / Telnet)
- Configurable max buffer length
- May be saved to SD or EEPROM optionally

---

## 🔒 Fallbacks and Graceful Degradation

| Feature     | Behavior When Unavailable               |
|-------------|------------------------------------------|
| TFT         | Logs redirected to USB/Telnet           |
| BLE UART    | Disabled without affecting others        |
| Network     | Falls back to USB if Ethernet/Wi-Fi down |
| Clock       | RTC → NTP → millis() fallback sequence  |

---

## 💾 Persistent Features

- Configuration & profiles saved as JSON to SD
- On boot: loads config from SD, then EEPROM fallback
- Command: `config save`, `config load`, `config reset`

---

## 📅 Future Enhancements

- Web interface for log viewing and CLI
- Command auto-completion
- Secure command authorization for critical commands
- Interactive TFT command mode

---

Let me know if you'd like to add commands, rework the grammar, or link this with architecture or pinout files.
