#include <avr/io.h>
#include "include/set_pin.h"

void symcreate(char sym)
{
	switch(sym)
	{
		case '0':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_low(PORTC, PC2);
			break;
		case '1':
			set_pin_low(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_low(PORTD, PD3);
			set_pin_low(PORTB, PB1);
			set_pin_low(PORTA, PA6);
			set_pin_low(PORTC, PC2);
			break;
		case '2':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_low(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_low(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case '3':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_low(PORTB, PB1);
			set_pin_low(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case '4':
			set_pin_low(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_low(PORTD, PD3);
			set_pin_low(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case '5':
		case 'S':
			set_pin_high(PORTA, PA5);
			set_pin_low(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_low(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case '6':
			set_pin_high(PORTA, PA5);
			set_pin_low(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case '7':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_low(PORTD, PD3);
			set_pin_low(PORTB, PB1);
			set_pin_low(PORTA, PA6);
			set_pin_low(PORTC, PC2);
			break;
		case '8':
		case 'B':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case '9':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_low(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case 'P':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_low(PORTC, PC0);
			set_pin_low(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case 'A':
			set_pin_high(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_low(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case 'V':
			set_pin_low(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_low(PORTC, PC2);
			break;
		case 'C':
			set_pin_high(PORTA, PA5);
			set_pin_low(PORTA, PA7);
			set_pin_low(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_high(PORTA, PA6);
			set_pin_low(PORTC, PC2);
			break;
		case 'r':
			set_pin_low(PORTA, PA5);
			set_pin_low(PORTA, PA7);
			set_pin_low(PORTC, PC0);
			set_pin_low(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_low(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case 'd':
			set_pin_low(PORTA, PA5);
			set_pin_high(PORTA, PA7);
			set_pin_high(PORTC, PC0);
			set_pin_high(PORTD, PD3);
			set_pin_high(PORTB, PB1);
			set_pin_low(PORTA, PA6);
			set_pin_high(PORTC, PC2);
			break;
		case 'N':
		default:
			set_pin_low(PORTA, PA5);
			set_pin_low(PORTA, PA7);
			set_pin_low(PORTC, PC0);
			set_pin_low(PORTD, PD3);
			set_pin_low(PORTB, PB1);
			set_pin_low(PORTA, PA6);
			set_pin_low(PORTC, PC2);
			break;
	}
}
