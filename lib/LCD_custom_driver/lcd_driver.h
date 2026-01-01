// lib/LCD_custom_driver/lcd_driver.h
#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <avr/io.h>
#include <util/delay.h>

// =========================================================================
//                           PIN CONFIGURATION
// =========================================================================
// Edit these if you change your wiring!

#if defined(__AVR_ATmega328P__)
    // Control Pins
    #define LCD_CTRL_PORT PORTB
    #define LCD_CTRL_DDR  DDRB
    #define LCD_RS        PB4
    #define LCD_EN        PB3
    
    // Data Pins
    #define LCD_DATA_PORT PORTD
    #define LCD_DATA_DDR  DDRD
    #define D4            PD5
    #define D5            PD4
    #define D6            PD3
    #define D7            PD2

#elif defined(__AVR_ATmega32__)
    // ATmega32 Config
    #define LCD_CTRL_PORT PORTA
    #define LCD_CTRL_DDR  DDRA
    #define LCD_RS        PA0
    #define LCD_EN        PA1
    #define LCD_DATA_PORT PORTA
    #define LCD_DATA_DDR  DDRA
    #define D4 PA2
    #define D5 PA3
    #define D6 PA4
    #define D7 PA5
#endif

// =========================================================================
//                           FUNCTION PROTOTYPES
// =========================================================================

// Initialize the LCD
void LCD_Init(void);

// Send a Command (like clear screen or move cursor)
void LCD_Command(unsigned char cmd);

// Send a single character
void LCD_Char(unsigned char data);

// Print a full string
void LCD_Print(char *str);

#endif