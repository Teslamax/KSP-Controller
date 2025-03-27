# 📝 .gitignore Pattern Documentation

This document explains each pattern used in the project’s `.gitignore` file and why it’s useful.

## 🧰 General System & Editor Junk

- `.DS_Store`: macOS Finder metadata
- `Thumbs.db`: Windows Explorer thumbnail cache
- `*.bak`, `*.tmp`: Editor backup and temp files
- `*.log`: Output logs from builds or scripts
- `*.swp`: Vim swap files

## ⚙️ PlatformIO / VS Code Artifacts

- `.pio/`: PlatformIO build folder
- `.vscode/`: VS Code user config (not project-specific)
- `*.elf`, `*.bin`, `*.hex`: Firmware outputs
- `*.map`, `*.d`: Debug and dependency maps

## 🔌 Arduino Sketch Outputs

- `*.ino.*`, `*.cpp.*`, `*.o`: Intermediate preprocessed/compiled code

## 📦 Archives & Disk Images

- `*.zip`, `*.tar.gz`, `*.7z`, `*.rar`: Local backups or downloads
- `*.img`, `*.iso`: OS or SD card images

## 📐 PCB / CAD Tools

- `*.autosave`, `*.backup`, `*.bak`: Autosaves from design tools
- `*.sch-bak`, `*.pcb-bak`: KiCad backups

## 🐍 Python Scripts & Caches

- `__pycache__/`: Python bytecode folder

## 🔀 Merge Conflict Leftovers

- `*.orig`, `*.rej`, `*~`: Unwanted leftovers from failed merges or patches
