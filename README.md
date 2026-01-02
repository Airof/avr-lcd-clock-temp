AVR-ThermoChron 🌡️🕒

AVR-ThermoChron is a dual-mode digital clock and thermometer designed for AVR microcontrollers. It features a custom-written LCD driver, a robust state-machine based UI for setting time/date, and real-time temperature monitoring using an LM35 sensor.

The codebase is designed to be portable, compiling seamlessly for both ATmega32 and ATmega328P chips using PlatformIO.

✨ Features

Dual Chip Support: Runs on ATmega32 (Port A LCD) and ATmega328P (Port B/D LCD) from the same source code.

Real-Time Clock: Tracks Year, Month, Day, Hour, Minute, Second.

Smart Calendar: Handles days per month (leap year logic included).

Temperature Mode: Automatically cycles between Clock and Room Temperature (C/F) every 45 seconds.

Manual Override: Instantly check temperature via button press.

Interactive UI: Blink-based editing mode to set time and date.

Pure C Driver: Custom lightweight LCD library (no Arduino dependencies).

🛠 Hardware Setup

1. Wiring the LCD (16x2)

Pin Name

ATmega328P

ATmega32

RS

PB4

PA0

EN

PB3

PA1

D4

PD5

PA2

D5

PD4

PA3

D6

PD3

PA4

D7

PD2

PA5

2. Button Controls

Connect buttons between the pins below and GND (internal pull-ups are enabled).

Button

Pin (Port B)

Function

Test Action

MODE

PB0

Cycle Selection

Press to start blinking the Year, Month, etc.

UP

PB1

Increment (+)

Press to increase the selected number.

DOWN

PB2

Decrement (-)

Press to decrease the selected number.

COMBO

PB1+PB2

Toggle Edit Mode

Hold UP + DOWN to quickly enter or exit editing.

3. Sensors

LM35 Temperature Sensor: Connect Vout to PA7 (ATmega32) or PC0 (ATmega328P).

📚 Technical Reference

Custom LCD Driver Commands

The project uses a custom lightweight driver. Below are the hex codes used for low-level control defined in Commands.h.

Command

Hex Code

Description

Clear Display

0x01

Wipes text, resets cursor to start. (Needs 2ms delay)

Return Home

0x02

Moves cursor to start, leaves text alone.

Entry Mode

0x06

Auto-increment cursor (write left-to-right).

Display ON

0x0C

Display ON, Cursor OFF.

Cursor ON

0x0E

Display ON, Cursor ON (Underscore).

Blink ON

0x0F

Display ON, Cursor Blinking.

Shift Left

0x18

Shifts the entire text to the left.

Shift Right

0x1C

Shifts the entire text to the right.

Line 1 Start

0x80

Force cursor to Line 1 start.

Line 2 Start

0xC0

Force cursor to Line 2 start.

📝 Development Notes & Troubleshooting

Summary of challenges encountered and resolved during development.

1. Arduino vs. AVR Native

Issue: The initial LCD driver implementation relied on Arduino libraries (LiquidCrystal), which bloated the code and obscured hardware details.

Solution: A custom, register-level driver was written from scratch using <avr/io.h>. This allows direct port manipulation for maximum speed and portability.

2. C/C++ Linker Errors

Issue: undefined reference to LCD_Init()

Cause: The project mixed .c (driver) and .cpp (main) files. The C++ compiler "mangled" function names, causing the linker to fail when looking for C functions.

Solution: Renamed main.cpp to main.c. The entire project is now pure C.

3. Pointer Qualifiers

Issue: Warning: passing argument 1 of 'LCD_Print' discards 'const' qualifier

Cause: The print function was defined as void LCD_Print(char *str), but string literals (e.g., "January") are const.

Solution: Updated the function signature in the header and source to accept constant strings:

void LCD_Print(const char *str, uint8_t line);



4. Display Ghosting

Issue: Old text characters remained on the screen when switching between menus or updating numbers (e.g., changing "December" to "May").

Solution: Implemented explicit LCD_Clear() calls on mode switches and added trailing spaces to shorter strings to overwrite previous data buffer.

🚀 How to Build

Install VS Code and the PlatformIO extension.

Clone this repository.

Select your environment in PlatformIO:

env:ATmega32 for the 40-pin chip.

env:ATmega328p for the Arduino Uno/Nano chip.

Build and Upload!

After building, the compiled binary files (.hex and .elf) can be found in:

.pio/build/ATmega32/

.pio/build/ATmega328p/