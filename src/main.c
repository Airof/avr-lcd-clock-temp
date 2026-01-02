#include <avr/io.h>
#include <util/delay.h>
#include "lcd_driver.h"
#include "clock.h" 
#include "clock_input.h"
#include "temp.h"

int main(void) {
    LCD_Init(); 
    LCD_Clear();
    Clock_Input_Init();
    Temp_Init(); 

    Clock_Init(23, 59, 58, 31, 11, 2024);

    // This is the "Counter"
    uint8_t display_timer = 0;

    while (1) {
        // 1. Inputs
        Clock_Input_Update();

        // NEW: Check if User pressed UP to see Temp
        if (Clock_Input_WasTempRequested()) {
            Temp_ForceShow(&display_timer); // Sets timer to 45
            LCD_Clear(); // Clear screen for clean switch
        }

        // 2. Logic
        Clock_Tick();

        if (Clock_GetEditState() != EDIT_NONE) {
            display_timer = 0;
            Clock_Display();
            _delay_ms(200); 
        } 
        else {
            if (display_timer < 45) {
                Clock_Display();
            } 
            else {
                Temp_Display_Screen();
            }

            display_timer++;
            if (display_timer >= 50) {
                display_timer = 0; 
                LCD_Clear();       
            }

            _delay_ms(90); 
        }
    }
    return 0;
}