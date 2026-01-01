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
