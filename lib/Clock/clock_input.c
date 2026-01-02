#include "clock_input.h"
#include "clock.h"
#include <util/delay.h>

// Flag to signal main.c that we want to see the temp
static uint8_t temp_request_flag = 0;

void Clock_Input_Init(void) {
    // 1. Set PB0, PB1, PB2 as Input (Logic 0)
    BUTTON_DDR &= ~((1 << PIN_MODE) | (1 << PIN_UP) | (1 << PIN_DOWN));
    
    // 2. Enable Pull-Up Resistors (Logic 1)
    BUTTON_PORT |= (1 << PIN_MODE) | (1 << PIN_UP) | (1 << PIN_DOWN);
}

void Clock_Input_Update(void) {
    // Read all buttons (Active LOW)
    uint8_t up_pressed   = !(BUTTON_PIN & (1 << PIN_UP));
    uint8_t down_pressed = !(BUTTON_PIN & (1 << PIN_DOWN));
    uint8_t mode_pressed = !(BUTTON_PIN & (1 << PIN_MODE));

    // --- 1. CHECK COMBO (UP + DOWN) ---
    // Toggle Edit Mode
    if (up_pressed && down_pressed) {
        Clock_ToggleEditMode();
        _delay_ms(50);
        while (!(BUTTON_PIN & (1 << PIN_UP)) || !(BUTTON_PIN & (1 << PIN_DOWN)));
        _delay_ms(50);
        return; 
    }

    // --- 2. Logic based on State ---
    if (Clock_GetEditState() != EDIT_NONE) {
        // === EDITING MODE ===
        
        // UP: Increment
        if (up_pressed) {
             Clock_Increment();
             _delay_ms(20); while (!(BUTTON_PIN & (1 << PIN_UP))); _delay_ms(20);
        }
        // DOWN: Decrement
        if (down_pressed) {
             Clock_Decrement();
             _delay_ms(20); while (!(BUTTON_PIN & (1 << PIN_DOWN))); _delay_ms(20);
        }
        // MODE: Next Field (Year -> Month...)
        if (mode_pressed) {
             Clock_NextField();
             _delay_ms(20); while (!(BUTTON_PIN & (1 << PIN_MODE))); _delay_ms(20);
        }
    } 
    else {
        // === NORMAL MODE ===
        
        // MODE Button: Request Temperature
        if (mode_pressed) {
            temp_request_flag = 1;
            
            // Debounce and wait for release
            _delay_ms(20);
            while (!(BUTTON_PIN & (1 << PIN_MODE)));
            _delay_ms(20);
        }
        
        // (UP and DOWN do nothing here unless used for the combo)
    }
}

// Getter for main.c
uint8_t Clock_Input_WasTempRequested(void) {
    if (temp_request_flag) {
        temp_request_flag = 0; // Clear flag after reading
        return 1;
    }
    return 0;
}