### first error 
the driver for LCD works via arduino not avr/io.h

*handle:* write it myself 

### second error
```
C:\Users\Airof\AppData\Local\Temp\ccDp9NoF.ltrans0.ltrans.o: In function `main':
<artificial>:(.text.startup+0x0): undefined reference to `LCD_Init()'
<artificial>:(.text.startup+0x8): undefined reference to `LCD_Print(char*)'
<artificial>:(.text.startup+0xe): undefined reference to `LCD_Command(unsigned char)'     
<artificial>:(.text.startup+0x16): undefined reference to `LCD_Print(char*)'
collect2.exe: error: ld returned 1 exit status
*** [.pio\build\ATmega328p\firmware.elf] Error 1
```
The error is a classic C vs C++ compatibility issue (often called "Name Mangling").

*handle:* change main.cpp to main.c


## third error
```
src\main.c:37:23: warning: passing argument 1 of 'LCD_Print' discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]

             LCD_Print(calendar[i].name,1);

                       ^~~~~~~~

In file included from src\main.c:4:0:

lib\LCD_custom_driver/lcd_driver.h:56:6: note: expected 'char *' but argument is of type 'const char * const' 

 void LCD_Print(char *str, uint8_t line);

```
*handle:* change
```
void LCD_Print(char *str, uint8_t line)
```
to 
```
void LCD_Print(const char *str, uint8_t line)
```

## third error:
[img path]
*handle:* didn't clear automatically so add `LCD_Clear()`;


## 🛠 Button Controls
Connect buttons between the pins below and **GND** (internal pull-ups are enabled).

| Button | Pin | Function | Test Action |
| :--- | :--- | :--- | :--- |
| **MODE** | `PB0` | Cycle Selection | Press to start blinking the Year, Month, etc. |
| **UP** | `PB1` | Increment (+) | Press to increase the selected number. |
| **DOWN** | `PB2` | Decrement (-) | Press to decrease the selected number. |
| **COMBO** | `PB1`+`PB2` | Toggle Edit Mode | Hold **UP** + **DOWN** to quickly enter or exit editing. |


## list of lcd commands:
Function,Hex Code,Description
Clear Display,0x01,"Wipes text, resets cursor to start. (Needs 2ms delay)"
Return Home,0x02,"Moves cursor to start, leaves text alone. (Needs 2ms delay)"
Entry Mode,0x06,Auto-increment cursor (write left-to-right).
Display Control,0x0C,"Display ON, Cursor OFF."
Display Control,0x0E,"Display ON, Cursor ON (Underscore)."
Display Control,0x0F,"Display ON, Cursor Blinking."
Shift Left,0x18,Shifts the entire text to the left.
Shift Right,0x1C,Shifts the entire text to the right.
Set Cursor,0x80,Force cursor to specific position (Line 1 start).
Set Cursor,0xC0,Force cursor to specific position (Line 2 start). 