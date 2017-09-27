#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN	4

volatile static uint8_t porthistory = 0xff;
volatile unsigned int cnt3 = 0, cnt7 = 0, cnt4 = 0, cnt6 = 0;
//unsigned char* vptr = v;

#include "include/crc8.h"
#include "include/prototype.h"
#include "include/frame_creator.h"
#include "include/symcreate.h"
#include "include/dotout.h"

void init_register(void);

enum states current_state = standby;
enum signals signal = idle;
enum digit dig = dig1;
enum value current_value = null;

//unsigned char a[8];

int main(int argc, char **argv) {

	init_register();
	sei();
	while(1)
	{
		current_state = new_state(current_state, signal);
		dig = get_new_dig(current_state, signal, dig);
		set_value(v, current_state, dig, get_new_value);
		/*unsigned char* f = frame_creator(v, current_state, crc8);
		for(int i = 0; i < 8; i++)
		{
			a[i] = f[i];
		}
		free(f);*/
	}
	return 0;
}

void init_register(void)
{
	DDRB |= 0x1A;
	DDRD |= 0x18;
	PORTC |= ((1 << PC6)|(1 << PC4)|(1 << PC5)|(1 << PC7)|(1 << PC3));
	DDRC |= 0x07;

	PORTD |= (1 << PD6);

	DDRA |= 0xff;
	GICR |= (1 << PCIE1);
	PCMSK1 |= ((1 << PCINT11)|(1 << PCINT12)|(1 << PCINT14)|(1 << PCINT15)|(1 << PCINT13));
}

/**********interrupt handler**********************************/
ISR(PCINT1_vect)
{
	uint8_t changebits;
	changebits = PINC ^ porthistory;
	porthistory = PINC;

	if((changebits&(1 << PINC3)))
	{
		cnt3++;
		if((cnt3%2 == 0) && (cnt3 != 0)) signal = pc3;
	}

	if((changebits&(1 << PINC7)))
	{
		cnt7++;
		if((cnt7%2 == 0) && (cnt7 != 0)) signal = pc7;
	}

	if((changebits&(1 << PINC4)))
	{
		signal = pc4;
	}

	if((changebits&(1 << PINC6)))
	{
		signal = pc6;
	}

	if((changebits&(1 << PINC5)))
	{
		signal = pc5;
	}
}
