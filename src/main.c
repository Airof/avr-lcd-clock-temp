#include <avr/io.h>
#include <util/delay.h>
#include "lcd_driver.h"
#include "clock.h" 
#include "clock_input.h" // <--- CRITICAL: Include this to fix 'Implicit Declaration'

int main(void) {
    LCD_Init(); 
    LCD_Clear();
    Clock_Input_Init(); // Initialize the buttons

    // Start at 12:00:00, Jan 1st 2025
    Clock_Init(23, 59, 58, 31, 11, 2024);

    while (1) {
        // Read Buttons
        Clock_Input_Update();
        
        // Update Time
        Clock_Tick();
        
        // Draw Screen
        Clock_Display();

        // Interface Speed Control:
        // Fast blink if editing (200ms), Slow tick if running (1000ms)
        if (Clock_GetEditState() != EDIT_NONE) {
            _delay_ms(200); 
        } else {
            _delay_ms(990); 
        }
    }
    return 0;
}