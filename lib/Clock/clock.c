// lib/Clock/clock.c
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
static EditState current_state = EDIT_NONE;
static uint8_t blink_state = 0; 

// --- Helpers ---
static void print_two_digits(uint8_t num) {
    char buffer[5];
    if (num < 10) LCD_Print("0", AUTO);
    itoa(num, buffer, 10);
    LCD_Print(buffer, AUTO);
}

// --- Public Functions ---

void Clock_Init(uint8_t h, uint8_t m, uint8_t s, uint8_t d, uint8_t month_idx, uint16_t y) {
    hours = h; minutes = m; seconds = s;
    day = d; month_index = month_idx; year = y;
}

// === CONTROL FUNCTIONS ===

void Clock_ToggleEditMode(void) {
    if (current_state == EDIT_NONE) {
        current_state = EDIT_YEAR; // Start editing Year
    } else {
        current_state = EDIT_NONE; // Save and Exit
    }
    blink_state = 0; // Make visible immediately
}

void Clock_SetEditState(EditState state) {
    current_state = state;
}

EditState Clock_GetEditState(void) {
    return current_state;
}

void Clock_NextField(void) {
    current_state++;
    if (current_state > EDIT_MINUTE) {
        current_state = EDIT_YEAR; // Loop back to Year (Don't exit)
    }
    blink_state = 0;
}

void Clock_Increment(void) {
    blink_state = 0;
    switch (current_state) {
        case EDIT_YEAR:
            year++;
            if (year > 2100) year = 2000;
            break;
        case EDIT_MONTH:
            month_index++;
            if (month_index >= 12) month_index = 0;
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
            seconds = 0;
            break;
        default: break;
    }
}

// NEW FUNCTION: Handle going backwards
void Clock_Decrement(void) {
    blink_state = 0;
    switch (current_state) {
        case EDIT_YEAR:
            year--;
            if (year < 2000) year = 2100;
            break;

        case EDIT_MONTH:
            if (month_index == 0) month_index = 11;
            else month_index--;
            
            // Safety: Check days (e.g. going form Mar 31 to Feb)
            if (day > calendar[month_index].days) day = calendar[month_index].days;
            break;

        case EDIT_DAY:
            day--;
            if (day < 1) day = calendar[month_index].days;
            break;

        case EDIT_HOUR:
            if (hours == 0) hours = 23;
            else hours--;
            break;

        case EDIT_MINUTE:
            if (minutes == 0) minutes = 59;
            else minutes--;
            seconds = 0;
            break;

        default: break;
    }
}

// === CORE LOGIC ===

void Clock_Tick(void) {
    if (current_state != EDIT_NONE) {
        blink_state = !blink_state; 
        return; 
    }
    // Standard Time Math
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
    LCD_Print("", LINE_1); 
    
    // Month
    if (current_state == EDIT_MONTH && blink_state) LCD_Print("   ", AUTO);
    else LCD_Print(calendar[month_index].name, AUTO); 
    LCD_Print(" ", AUTO);
    
    // Day
    if (current_state == EDIT_DAY && blink_state) LCD_Print("  ", AUTO);
    else print_two_digits(day); 
    LCD_Print(" ", AUTO);

    // Year
    if (current_state == EDIT_YEAR && blink_state) LCD_Print("    ", AUTO);
    else {
        itoa(year, buffer, 10);
        LCD_Print(buffer, AUTO);
    }
    LCD_Print("    ", AUTO); 

    LCD_Print("", LINE_2); 

    // === MODIFIED AM/PM LOGIC ===
    uint8_t display_hour = hours;
    const char* suffix = "AM";

    if (display_hour >= 12) {
        suffix = "PM";
        // If it's 13, 14, etc., subtract 12 to get 1, 2...
        // If it's 12 (Noon), it stays 12.
        if (display_hour > 12) display_hour -= 12;
    }
    
    // REMOVED: The line "if (display_hour == 0) display_hour = 12;"
    // Result: Midnight (00) stays 00 AM. Noon (12) stays 12 PM.

    // Hour
    if (current_state == EDIT_HOUR && blink_state) LCD_Print("  ", AUTO);
    else print_two_digits(display_hour);
    LCD_Print(":", AUTO);

    // Minute
    if (current_state == EDIT_MINUTE && blink_state) LCD_Print("  ", AUTO);
    else print_two_digits(minutes);
    LCD_Print(":", AUTO);

    print_two_digits(seconds);
    LCD_Print(" ", AUTO);
    LCD_Print(suffix, AUTO);
    LCD_Print("  ", AUTO);
}