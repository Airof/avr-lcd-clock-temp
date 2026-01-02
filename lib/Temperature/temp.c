// lib/Temperature/temp.c
#include "temp.h"
#include "lcd_driver.h"
#include <stdlib.h>

// ... (Keep Temp_Init, ADC_Read_Raw, Temp_Read, Temp_Display_Screen as they were) ...

void Temp_Init(void) {
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADCSRA |= (1 << ADEN);
}

static uint16_t ADC_Read_Raw(uint8_t channel) {
    ADMUX &= 0xF0;
    ADMUX |= (channel & 0x07);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

uint8_t Temp_Read(void) {
    uint16_t adc_val = ADC_Read_Raw(TEMP_ADC_CHANNEL);
    uint32_t temp = ((uint32_t)adc_val * 500UL) / 1024UL;
    return (uint8_t)temp;
}

void Temp_Display_Screen(void) {
    uint8_t c = Temp_Read();
    uint16_t f = (c * 9 / 5) + 32;

    LCD_Print("Room Temperature", LINE_1);
    LCD_Print("", LINE_2); 
    LCD_Print_Int(c, AUTO);
    LCD_Print("C / ", AUTO);
    LCD_Print_Int(f, AUTO);
    LCD_Print("F      ", AUTO); 
}

// NEW: Force the display timer to the "Temp Window" (45-50s)
void Temp_ForceShow(uint8_t *timer_ptr) {
    *timer_ptr = 45; 
}