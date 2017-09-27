#include <avr/io.h>
#include <avr/delay.h>
#include "include/set_pin.h"
#include "include/symcreate.h"
#include "include/dotout.h"

#define LED_DOT_COM             2

void showsym(unsigned char* data, const char dots)
{
	symcreate(data[0]);

	set_pin_high(PORTA, PA0);
	_delay_us(1);
	set_pin_low(PORTA, PA0);

	symcreate(data[1]);

	set_pin_high(PORTA, PA1);
	_delay_us(1);
	set_pin_low(PORTA, PA1);

	symcreate(data[2]);

	set_pin_high(PORTA, PA3);
	_delay_us(1);
	set_pin_low(PORTA, PA3);

	symcreate(data[3]);

	set_pin_high(PORTA, PA4);
	_delay_us(1);
	set_pin_low(PORTA, PA4);

        //dotout(0);
        dotout(dots);
        set_pin_high(PORTA,LED_DOT_COM);
        _delay_us(1);
        set_pin_low(PORTA,LED_DOT_COM);

}
