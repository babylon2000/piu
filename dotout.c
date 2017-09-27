#include <avr/io.h>
#include "include/set_pin.h"
#include "include/dot_reg.h"

void dotout(char dots)
{
        if(dots == 0)
        {
                set_pin_low(PORTC,LED_DOT1);
                set_pin_low(PORTB,LED_DOT2);
                set_pin_low(PORTD,LED_DOT3);
                set_pin_low(PORTB,LED_DOT67);
                set_pin_low(PORTB,LED_DOT8);
                set_pin_low(PORTD,LED_DOT9);
                set_pin_low(PORTB,LED_DOT11);

                return;
        }

        if(dots&0x01) set_pin_high(PORTC,LED_DOT1); //D1_K
        if(dots&0x02) set_pin_high(PORTB,LED_DOT2); //D2_K
        if(dots&0x04) set_pin_high(PORTD,LED_DOT3); //D3_K
        if(dots&0x08) set_pin_high(PORTB,LED_DOT67); //D6D7_K
        if(dots&0x10) set_pin_high(PORTB,LED_DOT8); //D8_K
        if(dots&0x20) set_pin_high(PORTD,LED_DOT9); //D9_K
        if(dots&0x40) set_pin_high(PORTB,LED_DOT11); //D11_K
}
