#include "clock.h"
#include "lcd_driver.h"
#include <stdlib.h>

// --- Data ---
typedef struct {
    const char *name;
    int days;
} Month;

static const Month calendar[] = {
    {"Jan", 31}, {"Feb", 28}, {"Mar", 31}, 
    {"Apr", 30}, {"May", 31}, {"Jun", 30}, 
    {"Jul", 31}, {"Aug", 31}, {"Sep", 30}, 
    {"Oct", 31}, {"Nov", 30}, {"Dec", 31}
};

static uint16_t year;
static uint8_t seconds, minutes, hours, day, month_index;

// NEW: Track what we are editing
static EditState current_state = EDIT_NONE;
static uint8_t blink_state = 0; // For flashing the cursor

// --- Helpers ---
static void print_two_digits(uint8_t num) {
    char buffer[5];
    if (num < 10) LCD_Print("0", 255);
    itoa(num, buffer, 10);
    LCD_Print(buffer, 255);
}

// --- Public Functions ---

void Clock_Init(uint8_t h, uint8_t m, uint8_t s, uint8_t d, uint8_t month_idx, uint16_t y) {
    hours = h; minutes = m; seconds = s;
    day = d; month_index = month_idx; year = y;
}

// Button 1: Switch Mode
void Clock_NextMode(void) {
    current_state++;
    if (current_state > EDIT_MINUTE) {
        current_state = EDIT_NONE; // Exit edit mode
    }
}

// Button 2: Increase Value
void Clock_Increment(void) {
    switch (current_state) {
        case EDIT_YEAR:
            year++;
            if (year > 2100) year = 2024;
            break;
        case EDIT_MONTH:
            month_index++;
            if (month_index >= 12) month_index = 0;
            // Safety: If we go Jan 31 -> Feb, clamp day to 28
            if (day > calendar[month_index].days) day = calendar[month_index].days;
            break;
        case EDIT_DAY:
            day++;
            if (day > calendar[month_index].days) day = 1;
            break;
        case EDIT_HOUR:
            hours++;
            if (hours >= 24) hours = 0;
            break;
        case EDIT_MINUTE:
            minutes++;
            if (minutes >= 60) minutes = 0;
            seconds = 0; // Reset seconds when adjusting time
            break;
        default:
            break;
    }
}

EditState Clock_GetState(void) {
    return current_state;
}

void Clock_Tick(void) {
    // DON'T tick time while user is setting it (optional preference)
    if (current_state != EDIT_NONE) {
        blink_state = !blink_state; // Toggle blink every tick
        return; 
    }

    seconds++;
    if (seconds >= 60) {
        seconds = 0; minutes++;
        if (minutes >= 60) {
            minutes = 0; hours++;
            if (hours >= 24) {
                hours = 0; day++;
                if (day > calendar[month_index].days) {
                    day = 1; month_index++;
                    if (month_index >= 12) {
                        month_index = 0; year++;
                    }
                }
            }
        }
    }
}

void Clock_Display(void) {
    char buffer[10];
    
    // Logic: If we are editing THIS field, and blink_state is 1, print spaces
    // Otherwise, print the number normally.

    // --- Line 1: Month Day Year ---
    LCD_Print("", 0); 
    
    // Month
    if (current_state == EDIT_MONTH && blink_state) LCD_Print("   ", 255);
    else LCD_Print(calendar[month_index].name, 255); 
    LCD_Print(" ", 255);
    
    // Day
    if (current_state == EDIT_DAY && blink_state) LCD_Print("  ", 255);
    else print_two_digits(day); 
    LCD_Print(" ", 255);

    // Year
    if (current_state == EDIT_YEAR && blink_state) LCD_Print("    ", 255);
    else {
        itoa(year, buffer, 10);
        LCD_Print(buffer, 255);
    }
    LCD_Print("    ", 255); // Ghosts

    // --- Line 2: HH:MM:SS ---
    LCD_Print("", 1); 

    // Hour
    if (current_state == EDIT_HOUR && blink_state) LCD_Print("  ", 255);
    else print_two_digits(hours);
    LCD_Print(":", 255);

    // Minute
    if (current_state == EDIT_MINUTE && blink_state) LCD_Print("  ", 255);
    else print_two_digits(minutes);
    LCD_Print(":", 255);

    // Second (Never edited, always visible)
    print_two_digits(seconds);
    LCD_Print("        ", 255); // Ghosts
}