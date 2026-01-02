// lib/Clock/clock_input.c
#include "clock_input.h"
#include "clock.h"
#include <util/delay.h>

void Clock_Input_Init(void) {
    // 1. Set PB0, PB1, PB2 as Input (Logic 0)
    BUTTON_DDR &= ~((1 << PIN_MODE) | (1 << PIN_UP) | (1 << PIN_DOWN));
    
    // 2. Enable Pull-Up Resistors (Logic 1)
    // Pins will read HIGH (1) when not pressed, and LOW (0) when pressed.
    BUTTON_PORT |= (1 << PIN_MODE) | (1 << PIN_UP) | (1 << PIN_DOWN);
}

void Clock_Input_Update(void) {
    // Read all buttons (Active LOW)
    uint8_t up_pressed   = !(BUTTON_PIN & (1 << PIN_UP));
    uint8_t down_pressed = !(BUTTON_PIN & (1 << PIN_DOWN));
    uint8_t mode_pressed = !(BUTTON_PIN & (1 << PIN_MODE));

    // --- 1. CHECK COMBO (UP + DOWN) ---
    // If both are pressed, toggle between "Clock Mode" and "Edit Mode"
    if (up_pressed && down_pressed) {
        Clock_ToggleEditMode();
        
        // Blocking wait until BOTH are released to prevent accidental clicks
        _delay_ms(50);
        while (!(BUTTON_PIN & (1 << PIN_UP)) || !(BUTTON_PIN & (1 << PIN_DOWN)));
        _delay_ms(50);
        return; // Skip other checks this cycle
    }

    // Only allow editing buttons if we are actually in Edit Mode
    if (Clock_GetEditState() != EDIT_NONE) {
        
        // --- 2. Increment ---
        if (up_pressed) {
            Clock_Increment();
            _delay_ms(20);
            while (!(BUTTON_PIN & (1 << PIN_UP))); // Wait for release
            _delay_ms(20);
        }

        // --- 3. Decrement ---
        if (down_pressed) {
            Clock_Decrement();
            _delay_ms(20);
            while (!(BUTTON_PIN & (1 << PIN_DOWN))); // Wait for release
            _delay_ms(20);
        }

        // --- 4. Switch Field (Year -> Month -> Day) ---
        if (mode_pressed) {
            Clock_NextField();
            _delay_ms(20);
            while (!(BUTTON_PIN & (1 << PIN_MODE))); // Wait for release
            _delay_ms(20);
        }
    }
}