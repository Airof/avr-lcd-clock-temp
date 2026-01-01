// src/main.c
#include <avr/io.h>
#include <util/delay.h>
#include "lcd_driver.h"  // <--- Include your new library
#include <stdlib.h>


int main(void) {
    LCD_Init(); 

    LCD_Print("Drivers Works!");
    
    // Move to 2nd line using Command function
    LCD_Command(0xC0); 
    LCD_Print("So Clean.");

    _delay_ms(1000);
    LCD_clear();
    char string_buffer[16];
    while (1) {
        for (int i = 0; i < 100; i++){
        itoa(i, string_buffer, 10); 
            
            // Print the resulting string
            LCD_Print(string_buffer);
            
            // Print a few spaces to overwrite old digits (e.g. going 100 -> 0)
            // LCD_Print("  ");
     
            _delay_ms(1000);
            LCD_clear(); 
        }
    }
    return 0;
}