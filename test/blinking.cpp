#include <avr/io.h>
#include <util/delay.h>


#if defined(__AVR_ATmega328P__)
    // ATmega328P Definitions
    #define LED_DDR     DDRB
    #define LED_PORT    PORTB

    
#elif defined(__AVR_ATmega32__)
    // ATmega32 Definitions
    #define LED_DDR     DDRB
    #define LED_PORT    PORTB

#else
    #error "Unknown Chip! Please add definitions."
#endif


int main() {
    // Set LED pin as output
    DDRB |= (1 << PB7);
    DDRB &= ~(1 << PB6); 
    PORTB |= (1 << PB6);

    while (1)
    {
      if (! (PINB & (1 << PB6))){
        PORTB = (1 << PB7);
      } else {
        PORTB ^= (1 << PB7);
        _delay_ms(50);
      }

    }
    return 0;
}