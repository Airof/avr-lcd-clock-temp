# ⏱️ AVR-ThermoChron 🌡️  

**AVR-ThermoChron** is a dual-mode digital **clock + thermometer** designed for AVR microcontrollers.  
It features a **custom-written LCD driver**, a **state-machine–based UI** for setting time/date, and **real-time temperature monitoring** using an **LM35** sensor.

The codebase is designed to be **portable**, compiling seamlessly for both **ATmega32** and **ATmega328P** using **PlatformIO** ⚙️.

---

## ✨ Features
* 🧩 **Dual Chip Support:** Runs on ATmega32 (Port A LCD) and ATmega328P (Port B/D LCD) from the same source code.
* ⏰ **Real-Time Clock:** Tracks Year, Month, Day, Hour, Minute, Second.
* 📅 **Smart Calendar:** Handles days per month (leap year logic included).
* 🌡️ **Temperature Mode:** Automatically cycles between Clock and Room Temperature (°C / °F) every 45 seconds.
* 🖱️ **Manual Override:** Instantly check temperature via button press.
* 🔁 **Interactive UI:** Blink-based editing mode to set time and date.
* 🧪 **Pure C Driver:** Custom lightweight LCD library (no Arduino dependencies).

---

## 🛠 Hardware Setup

### 📟 1. Wiring the LCD (16x2)
| Pin Name | ATmega328P | ATmega32 |
| :--- | :--- | :--- |
| **RS** | `PB4` | `PA0` |
| **EN** | `PB3` | `PA1` |
| **D4** | `PD5` | `PA2` |
| **D5** | `PD4` | `PA3` |
| **D6** | `PD3` | `PA4` |
| **D7** | `PD2` | `PA5` |

---

### 🔘 2. Button Controls
Connect buttons between the pins below and **GND** (internal pull-ups are enabled).

| Button | Pin (Port B) | Function | Test Action |
| :--- | :--- | :--- | :--- |
| **MODE** | `PB0` | Cycle Selection | Start blinking Year, Month, etc. |
| **UP** | `PB1` | Increment (+) | Increase selected value |
| **DOWN** | `PB2` | Decrement (-) | Decrease selected value |
| **COMBO** | `PB1`+`PB2` | Toggle Edit Mode | Hold **UP + DOWN** |

---

### 🌡️ 3. Sensors
* **LM35 Temperature Sensor:**  
  * Vout → `PA7` (ATmega32)  
  * Vout → `PC0` (ATmega328P)

---

## 📚 Technical Reference

### 🧾 Custom LCD Driver Commands
The project uses a custom lightweight driver. Below are the hex codes defined in `Commands.h`.

| Command | Hex Code | Description |
| :--- | :--- | :--- |
| **Clear Display** | `0x01` | Clears screen, resets cursor (2ms delay) |
| **Return Home** | `0x02` | Cursor to start, text unchanged |
| **Entry Mode** | `0x06` | Auto-increment cursor |
| **Display ON** | `0x0C` | Display ON, Cursor OFF |
| **Cursor ON** | `0x0E` | Cursor visible |
| **Blink ON** | `0x0F` | Blinking cursor |
| **Shift Left** | `0x18` | Shift display left |
| **Shift Right** | `0x1C` | Shift display right |
| **Line 1 Start** | `0x80` | Cursor to Line 1 |
| **Line 2 Start** | `0xC0` | Cursor to Line 2 |

---

## 📝 Development Notes & Troubleshooting

### 🧱 1. Arduino vs. AVR Native
**Issue:** LCD driver relied on Arduino libraries (`LiquidCrystal`), increasing code size and hiding hardware details.  
**Solution:** Rewrote the driver using `<avr/io.h>` for direct register-level control.

---

### 🔗 2. C/C++ Linker Errors
**Issue:** `undefined reference to LCD_Init()`  
**Cause:** Mixing `.c` and `.cpp` files caused name mangling.  
**Solution:** Converted the entire project to **pure C** by renaming `main.cpp` → `main.c`.

---

### 📌 3. Pointer Qualifiers
**Issue:**  
`passing argument 1 of 'LCD_Print' discards 'const' qualifier`  

**Cause:** String literals are `const`, but the function expected `char *`.  
**Solution:** Updated function signature:

```c
void LCD_Print(const char *str, uint8_t line);
```
### 👻 4. Display Ghosting
**Issue:** Old characters remained when switching modes (e.g., `"December"` → `"May"`).  

**Solution:**  
* Added `LCD_Clear()` on mode changes  
* Appended trailing spaces to overwrite leftover characters  

---

## 🚀 How to Build
1. 🧩 Install **VS Code** and the **PlatformIO** extension  
2. 📥 Clone this repository  
3. ⚙️ Select your PlatformIO environment:
   * `ATmega32` → 40-pin MCU  
   * `ATmega328p` → Arduino Uno / Nano  
4. 🔨 Build & Upload!

---

## 📦 Build Output
After building, compiled files are located at:

* 📁 `.pio/build/ATmega32/`
* 📁 `.pio/build/ATmega328p/`

