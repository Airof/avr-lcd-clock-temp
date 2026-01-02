// lib/Temperature/temp.h
#ifndef TEMP_H
#define TEMP_H

#include <avr/io.h>

// Configuration
#if defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)
    #define TEMP_ADC_CHANNEL 7
#elif defined(__AVR_ATmega328P__)
    #define TEMP_ADC_CHANNEL 0
#endif

// Prototypes
void Temp_Init(void);
uint8_t Temp_Read(void);
void Temp_Display_Screen(void);

// NEW: Function to force the temperature cycle to start immediately
// We pass the pointer to the timer variable from main
void Temp_ForceShow(uint8_t *timer_ptr);

#endif