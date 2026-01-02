#ifndef COMMANDS_H
#define COMMANDS_H

// =========================================================================
//                           COMMAND DEFINITIONS
// =========================================================================

// Clear & Home
#define LCD_CMD_CLEAR           0x01
#define LCD_CMD_HOME            0x02

// Entry Mode
#define LCD_ENTRY_DEC           0x04
#define LCD_ENTRY_DEC_SHIFT     0x05
#define LCD_ENTRY_INC           0x06
#define LCD_ENTRY_INC_SHIFT     0x07

// Display Control
#define LCD_DISPLAY_OFF         0x08
#define LCD_DISPLAY_ON          0x0C
#define LCD_CURSOR_ON           0x0E
#define LCD_CURSOR_BLINK        0x0F

// Cursor / Display Shift
#define LCD_MOVE_CURSOR_LEFT    0x10
#define LCD_MOVE_CURSOR_RIGHT   0x14
#define LCD_SHIFT_DISPLAY_LEFT  0x18
#define LCD_SHIFT_DISPLAY_RIGHT 0x1C

// Function Set
#define LCD_FUNCTION_4BIT_2LINE 0x28
#define LCD_FUNCTION_8BIT_2LINE 0x38

// Line Addresses
#define LCD_LINE1_START         0x80
#define LCD_LINE2_START         0xC0

#endif // COMMANDS_H