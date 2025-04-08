# 🎛️ Prototyping Switch & Keycap Selection Guide

This guide documents the evaluation process for choosing **mechanical switches** and **keycaps** suitable for the KSP Controller project, with emphasis on **control panel usability**, **RGB visibility**, and **tactile feedback**. All switches discussed are MX-compatible and intended for use with the **NeoKey 1x4 STEMMA QT** board.

---

## ✅ Target Use Case

- Not intended for typing
- Prioritize **tactile feedback**, low actuation force, and **light diffusion**
- Must be **MX-compatible**
- RGB compatibility preferred (clear/transparent housing)

---

## 🔘 Recommended Switches

| Switch               | Type     | Feel                | RGB Friendly | Pros                                  | Cost Estimate |
|----------------------|----------|---------------------|--------------|----------------------------------------|----------------|
| **Gateron Clear**    | Linear   | Light, smooth       | ✅ Excellent  | Very soft press, RGB shines through   | ~$0.30–$0.50   |
| **Kailh Box Brown**  | Tactile  | Mild bump           | ✅ Excellent  | Tactile w/o click, dampened feel      | ~$0.40–$0.70   |
| **Kailh Box White**  | Clicky   | Tactile + click     | ✅ Good       | Audible feedback, crisp bump          | ~$0.40–$0.60   |
| **Outemu Ice Blue**  | Tactile  | Medium bump         | ✅ Excellent  | Sharp tactility, translucent housing  | ~$0.30–$0.50   |

---

## ⚙️ Switch Comparison Notes

- **Gateron Clear** is ideal for fast-tap buttons with minimal finger strain.
- **Box Brown** offers a good balance between tactility and silence.
- **Box White** is great for a tactile + audible "click," but may be too loud in shared spaces.
- **Outemu Ice Blue** gives satisfying tactility with full RGB support.

---

## ⌨️ Keycap Selection Guidelines

| Feature               | Preference                | Notes                                             |
|------------------------|---------------------------|----------------------------------------------------|
| **Mount Type**         | MX stem                   | Required for all recommended switches              |
| **Top Material**       | Opaque or lightly translucent | Allows selective RGB feedback                     |
| **Profile**            | DSA or SA (low profile)   | Improves control panel aesthetics & usability      |
| **Legends**            | Blank or side-printed     | Avoids visual clutter and supports clean lighting  |

> Current favorites: **Adafruit #5112** (diffused top with light pipe), or **“pudding-style” caps** for clear RGB diffusion if labeled legends are needed.

---

## 📝 Notes

- RGB LEDs beneath switches should be addressable (e.g., NeoPixels).
- Switch feel is subjective—**a variety tester kit is recommended**.
- Final switch choice may vary between button groups (e.g., mode switches vs. staging).

---

## 🔗 Related Design Documents

- [Controller_Design_Spec.md](./Controller_Design_Spec.md)
- [Capabilities.md](./Capabilities.md)
- [Pin_Map.md](./Pin_Map.md)
