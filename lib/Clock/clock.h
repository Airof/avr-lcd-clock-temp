// lib/Clock/clock.h
#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

// Shared Enum
typedef enum {
    EDIT_NONE = 0,
    EDIT_YEAR,
    EDIT_MONTH,
    EDIT_DAY,
    EDIT_HOUR,
    EDIT_MINUTE
} EditState;

// Standard Functions
void Clock_Init(uint8_t h, uint8_t m, uint8_t s, uint8_t d, uint8_t month_idx, uint16_t y);
void Clock_Tick(void);
void Clock_Display(void);

// Input Control
void Clock_SetEditState(EditState state);
EditState Clock_GetEditState(void);
void Clock_ToggleEditMode(void); // Enters/Exits editing

void Clock_NextField(void);      // Move selection to next field
void Clock_Increment(void);      // Add 1
void Clock_Decrement(void);      // Subtract 1 (NEW)

#endif