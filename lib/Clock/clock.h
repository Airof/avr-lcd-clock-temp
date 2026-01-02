#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

// Edit States
typedef enum {
    EDIT_NONE = 0,
    EDIT_YEAR,
    EDIT_MONTH,
    EDIT_DAY,
    EDIT_HOUR,
    EDIT_MINUTE
} EditState;

// Init
void Clock_Init(uint8_t h, uint8_t m, uint8_t s, uint8_t d, uint8_t month_idx, uint16_t y);

// Core Logic
void Clock_Tick(void);
void Clock_Display(void);

// Input Handling
void Clock_NextMode(void); // Cycle: Year -> Month -> Day...
void Clock_Increment(void); // Add 1 to current selection
EditState Clock_GetState(void); // Ask "Are we editing?"

#endif