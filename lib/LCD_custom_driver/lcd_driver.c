// lib/LCD_custom_driver/lcd_driver.c
#include "lcd_driver.h"
#include "Commands.h"
#include <stdlib.h>
// --- Internal Helper Functions (Not usually called by user) ---

void LCD_Pulse_Enable() {
    LCD_CTRL_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_CTRL_PORT &= ~(1 << LCD_EN);
    _delay_us(100);
}

void LCD_Send_Nibble(unsigned char data) {
    // Clear current data bits
    LCD_DATA_PORT &= ~((1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));

    // Map the bits
    if(data & 1) LCD_DATA_PORT |= (1<<D4);
    if(data & 2) LCD_DATA_PORT |= (1<<D5);
    if(data & 4) LCD_DATA_PORT |= (1<<D6);
    if(data & 8) LCD_DATA_PORT |= (1<<D7);

    LCD_Pulse_Enable();
}

void LCD_Byte(unsigned char val, int is_cmd) {
    if (is_cmd) LCD_CTRL_PORT &= ~(1 << LCD_RS); 
    else        LCD_CTRL_PORT |= (1 << LCD_RS);  

    LCD_Send_Nibble(val >> 4);   // High Nibble
    LCD_Send_Nibble(val & 0x0F); // Low Nibble
}

// --- Public Functions (Listed in Header) ---

void LCD_Init() {
    LCD_CTRL_DDR |= (1<<LCD_RS) | (1<<LCD_EN);
    LCD_DATA_DDR |= (1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
    
    _delay_ms(50);

    LCD_CTRL_PORT &= ~(1 << LCD_RS);
    LCD_Send_Nibble(0x03); _delay_ms(5);
    LCD_Send_Nibble(0x03); _delay_us(150);
    LCD_Send_Nibble(0x03);
    LCD_Send_Nibble(0x02); // 4-bit mode

    // NOW USE THE MACROS:
    LCD_Byte(LCD_FUNCTION_4BIT_2LINE, 1); // 0x28
    LCD_Byte(LCD_DISPLAY_ON, 1);          // 0x0C
    LCD_Byte(LCD_ENTRY_INC, 1);           // 0x06
    LCD_Byte(LCD_CMD_CLEAR, 1);           // 0x01
    _delay_ms(2);
}

void LCD_Command(unsigned char cmd) {
    LCD_Byte(cmd, 1);
}

void LCD_Char(unsigned char data) {
    LCD_Byte(data, 0);
}

void LCD_Print(const char *str, uint8_t line) {
    if (line == 0) {
        LCD_Command(LCD_LINE1_START); // Force start of Line 1
    } 
    else if (line == 1) {
        LCD_Command(LCD_LINE2_START); // Force start of Line 2
    }
    while (*str) {
        LCD_Char(*str++);
    }
}

void LCD_Clear(){
    LCD_Command(LCD_CMD_CLEAR);   // 0x01
    _delay_ms(2);       
}

void LCD_Print_Int(int num, uint8_t line){
    char string_buffer[16];
    itoa(num, string_buffer, 10); 
    // Print the resulting string
    LCD_Print(string_buffer, 1);

}