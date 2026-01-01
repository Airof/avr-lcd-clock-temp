// lib/LCD_custom_driver/lcd_driver.c
#include "lcd_driver.h"

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

    LCD_Byte(0x28, 1); // Function Set
    LCD_Byte(0x0C, 1); // Display ON
    LCD_Byte(0x06, 1); // Entry Mode
    LCD_Byte(0x01, 1); // Clear
    _delay_ms(2);
}

void LCD_Command(unsigned char cmd) {
    LCD_Byte(cmd, 1);
}

void LCD_Char(unsigned char data) {
    LCD_Byte(data, 0);
}

void LCD_Print(char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}