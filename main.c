#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN	4
#define MYUBRR 95

#define blink_on(port, pin)	port |= pin
#define blink_off(port, pin) port &=~ pin

volatile static uint8_t porthistory = 0xff;
volatile unsigned int cnt3 = 0, cnt7 = 0, cnt4 = 0, cnt6 = 0, cnt5 = 0;

#include "include/crc8.h"
#include "include/prototype.h"
#include "include/frame_creator.h"
#include "include/showsym.h"
#include "include/uart.h"

void init_register(void);
void modeHandler(void);
void btn_pc5_handler(enum states, enum signals);

enum states current_state = standby;
enum signals signal = idle;
enum digit dig = dig1;
enum value current_value = null;

unsigned char v[4];
unsigned char* vptr = v;
char dots = 0x00;

int main(int argc, char **argv) {

	init_register();
	uart_init(MYUBRR);
	sei();
	while(1)
	{
		showsym(v, dots);
		modeHandler();
		current_state = new_state(current_state, signal);
		//if(signal == pc5) current_state = code;
		dig = get_new_dig(current_state, signal, dig);
		set_value(v, current_state, dig, get_new_value);
		btn_pc5_handler(current_state, signal);
		signal = idle;
	}
	return 0;
}

void modeHandler()
{
	if((PIND&(1 << PD6)) == 0)
	{
		_delay_ms(40);
		if((PIND&(1 << PD6)))
		{
			signal = pd6;
			v[0] = 0x30;
			v[1] = 0x30;
			v[2] = 0x30;
			v[3] = 0x30;
		}

	}
}

void btn_pc5_handler(enum states st, enum signals sg)
{
	switch (sg) {
		case pc5:
			if((st != standby) && (st != vb))
			{
				unsigned char* new_frame = frame_creator(v, st, crc8);
				uart_send_package(new_frame, sizeof(new_frame)/sizeof(new_frame[0]));
				dots = 0x02;
				free(new_frame);//пока не определюсь с проверкой!
			}
			break;
		default:
			break;
	}
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

/**********interrupt handler for pin change**********************************/
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
		cnt4++;
		if((cnt4%2 == 0) && (cnt4 != 0)) signal = pc4;
	}

	if((changebits&(1 << PINC6)))
	{
		cnt6++;
		if((cnt6%2 == 0) && (cnt6 != 0)) signal = pc6;
	}

	if((changebits&(1 << PINC5)))
	{
		cnt5++;
		if((cnt5%2 == 0) && (cnt5 != 0)) signal = pc5;
	}
}
/**********************************************************************/
