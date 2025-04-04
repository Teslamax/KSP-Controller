# 🧪 Analog Input Strategy for ESP32-S3 Reverse TFT Feather

This document summarizes how to handle analog inputs for your custom controller using the ESP32-S3 Reverse TFT Feather (Adafruit #5691), especially in scenarios where Wi-Fi or BLE is in use.

---

## 📈 Native ADC Capabilities

| Feature            | Description |
|-------------------|-------------|
| **Total ADC Pins** | Up to 20 on-chip, but only ~6 exposed on Feather |
| **Resolution**     | 12-bit (0–4095), ~11-bit effective due to noise |
| **Sampling Rate**  | Up to ~18,000 samples/sec |
| **ADC1 vs ADC2**   | **ADC1** can be used alongside Wi-Fi/BLE; **ADC2** cannot |

> ⚠️ **Use only ADC1 pins when Wi-Fi or BLE is active.**

---

## 🧩 External ADC Options

### ✅ Recommended Chips

| Chip        | Interface | Channels | Resolution | Speed       | Notes |
|-------------|-----------|----------|------------|-------------|-------|
| **ADS1115** | I²C       | 4        | 16-bit     | ~860 SPS    | High precision |
| **ADS1015** | I²C       | 4        | 12-bit     | ~3300 SPS   | Faster, less precise |
| **MCP3008** | SPI       | 8        | 10-bit     | Fast        | Simple & inexpensive |
| **ADS7830** | I²C       | 8        | 8-bit      | Very Fast   | Small resolution, compact |

---

## 🎮 Input Type Recommendations

| Input Device       | Priority      | Suggested Resolution |
|--------------------|---------------|-----------------------|
| **Analog Joystick** | Smooth motion | 10–12 bits |
| **Throttle (manual)** | Precise scaling | 12–14 bits |
| **Motorized Pot (feedback)** | PID-friendly | 12–16 bits |
| **Sliders / knobs** | Mode changes | 8–10 bits |

---

## 🧠 Recommended Strategy

- Use **1–2 native ADC1 pins** for latency-sensitive inputs
- Use **external I²C ADC (e.g. ADS1115)** for 4+ other analog devices
- Consider using **2 ADCs** (e.g. two ADS1015s) if you need >4 channels with I²C

---

## 🧮 ESP32-S3 Feather Pin Usage Estimate (WIP)

| Purpose               | GPIOs Used | Notes |
|------------------------|------------|-------|
| I²C ADC (ADS1115)      | 2 (SDA/SCL) | Shared with display/sensors |
| SPI devices (e.g. SD)  | 3 + 1 per device | Shared SPI, unique CS |
| USB / CDC              | Built-in   | USB stack uses internal GPIOs |
| Native Analog Pins     | 2–4        | ADC1 only if Wi-Fi active |

> 📌 Refer to `docs/Pin_Map.md` for exact GPIO availability.

---

## 🔚 Conclusion

For your 7+ analog input needs:

- Reserve **ADC1 GPIOs** for throttle or joystick axes
- Add **ADS1115 or ADS1015** via I²C for the remainder
- Keep SPI pins for SD, Ethernet, etc.
- Avoid ADC2 pins entirely when Wi-Fi or BLE is active

