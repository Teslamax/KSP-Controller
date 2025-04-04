# Project TODOs

This document tracks ideas and implementation tasks that should be revisited later to improve and complete the system.

---

## ✅ Global / Architecture-Wide

- [ ] Centralize SD card logic in a `sd_card_helpers.cpp/.h` file.
  - Move `SD.begin(...)`, health checks, and directory listings.
  - Cleanup logic for cleaner modular access.
  - ```cpp
    // TODO: Move SD init logic to sd_card_helpers.[cpp/h] for cleaner modular access
    ```

- [ ] Confirm SPI CS pin assignments to avoid conflict between SD and Ethernet FeatherWings.
  - ```cpp
    // TODO: Confirm SPI CS pin assignments to avoid conflict between SD and Ethernet
    ```

---

## `json_config.cpp`

- [ ] Add robust error handling for malformed or partial config files.
  - ```cpp
    // TODO: Add fallback defaults and recovery for missing/invalid config keys
    ```

- [ ] Support writing config backups (e.g., `config.json.bak`).
  - ```cpp
    // TODO: Implement backup-saving of config to config.json.bak
    ```

- [ ] Expand config schema (e.g., screen brightness, logging level).
  - ```cpp
    // TODO: Expand config schema to support display/logging customization
    ```

---

## `cli_commands.cpp`

- [ ] Finalize implementation of `status json` and `status short` commands.
  - ```cpp
    // TODO: Finalize 'status json' and 'status short' CLI output formats
    ```

- [ ] Add `config reload` and `config save` CLI commands.
  - ```cpp
    // TODO: Add 'config reload' and 'config save' CLI commands
    ```

---

## `telnet_server.cpp`

- [ ] Consider calling `flush()` after `println()` to ensure full transmission.
  - ```cpp
    // TODO: Evaluate if telnetClient.flush() is needed after println
    ```

- [ ] Add Ethernet reconnect logic when cable is unplugged/replugged.
  - ```cpp
    // TODO: Add Ethernet reconnect logic on cable unplug/replug
    ```

---

## `status_summary.cpp`

- [ ] Expand `status json` and `status short` with richer system telemetry:
  - SD card presence and capacity
  - RTC sync state
  - Uptime
  - Current screen mode
  - CLI client connectivity
  - ```cpp
    // TODO: Add more telemetry fields to status_summary outputs
    ```

---

## `main.cpp`

- [ ] Defer Ethernet initialization until physical link is detected.
  - ```cpp
    // TODO: Delay Ethernet init until physical link is active
    ```

- [ ] Ensure boot summary logs are printed to all log destinations (TFT, USB CDC, Telnet, etc).
  - ```cpp
    // TODO: Ensure boot summary prints to all enabled outputs
    ```

