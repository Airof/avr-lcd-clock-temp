#include <avr/io.h>
#include <util/delay.h>
#include "lcd_driver.h"
#include "clock.h" 

int main(void) {
    LCD_Init(); 
    LCD_Clear();

    // Start Date: Dec 31st, 2025 at 23:59:55
    Clock_Init(23, 59, 55, 31, 11, 2025);

    while (1) {
        Clock_Tick();
        Clock_Display();
        _delay_ms(1000);
    }
    return 0;
}