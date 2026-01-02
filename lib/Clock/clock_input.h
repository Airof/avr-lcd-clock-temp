// lib/Clock/clock_input.h
#ifndef CLOCK_INPUT_H
#define CLOCK_INPUT_H

#include <avr/io.h>

// ==========================================
//    PIN CONFIGURATION (Port B)
// ==========================================
// ATmega328P: PB0(8), PB1(9), PB2(10)
// ATmega32A:  PB0(1), PB1(2), PB2(3)

// Define the Port Registers
#define BUTTON_DDR   DDRB
#define BUTTON_PORT  PORTB
#define BUTTON_PIN   PINB

// Define the Pin Numbers
#define PIN_MODE     PB0  // Cycle Selection (Year -> Month...)
#define PIN_UP       PB1  // Increase Value
#define PIN_DOWN     PB2  // Decrease Value

// ==========================================
//               PROTOTYPES
// ==========================================

void Clock_Input_Init(void);
void Clock_Input_Update(void);

#endif