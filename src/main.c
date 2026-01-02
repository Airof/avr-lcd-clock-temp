// src/main.c
#include <avr/io.h>
#include <util/delay.h>
#include "lcd_driver.h" 


void clock();

uint8_t secconds;
uint8_t hour;
typedef struct {
    const char *name;
    int days;
} Month;
uint8_t year;

int main(void) {

    const Month calendar[] = {
        {"January", 31}, {"February", 28}, {"March", 31}, 
        {"April", 30},   {"May", 31},      {"June", 30}, 
        {"July", 31},    {"August", 31},   {"September", 30}, 
        {"October", 31}, {"November", 30}, {"December", 31}
    };

    LCD_Init(); 

    LCD_Print("Drivers Works!" ,0);

    _delay_ms(1000);
    LCD_Clear();


    while (1) {
        for (int i = 0; i < 12; i++){

            LCD_Print(calendar[i].name,1);
            _delay_ms(500);
        }
    }
    return 0;
}


void clock(){

}