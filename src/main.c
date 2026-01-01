// src/main.c
#include <avr/io.h>
#include <util/delay.h>
#include "lcd_driver.h"  // <--- Include your new library

int main(void) {
    LCD_Init(); 

    LCD_Print("Drivers Works!");
    
    // Move to 2nd line using Command function
    LCD_Command(0xC0); 
    LCD_Print("So Clean.");

    while (1) {
    }
    return 0;
}