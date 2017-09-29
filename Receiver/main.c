#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN	8
#define MYUBRR 95

#define FRAMING_ERROR (1 << FE0)
#define PARITY_ERROR (1 << UPE0)
#define DATA_OVERRUN (1 << DOR0)

#include "include/crc8.h"
#include "include/uart.h"
#include "include/showsym.h"

void init_register(void);

volatile unsigned char rx_data[LEN];
unsigned char data[LEN/2];
char dots = 0x00;
unsigned char crc = 0;
volatile unsigned char cnt1 = 0, flag_of_receive_package = 0;

int main(int argc, char **argv) {

	init_register();
	uart_init(MYUBRR);
	sei();
	while(1)
	{
		if(flag_of_receive_package == 1)
		{
			if(rx_data[0] == 0x01)
			{
				for(register int i = 0; i < LEN/2; i++)
				{
					data[i] = rx_data[i + 2];
				}
				crc = crc8(data, LEN/2);
				if(crc == rx_data[6])
				{
					dots = 0x02;
					flag_of_receive_package = 0;
				}/*else
				{
					goto fail;
				}*/
			}else if(rx_data[0] == 0xFF)
			{
				cli();
				//делаем отправку пакета
				dots = 0x08;
				sei();
			}


		}
		showsym(data, dots);
	}
	return 0;

	//fail:

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

ISR(USART0_RXC_vect)
{
	char status = UCSR0A;
	if(!(status&(PARITY_ERROR | DATA_OVERRUN | FRAMING_ERROR)))
	{
			*(rx_data + cnt1) = UDR0;
			if((*(rx_data + 0) == 0x01) || (*(rx_data + 0) == 0xFF) )
			{
				cnt1++;
				if(cnt1 == LEN)
				{
					flag_of_receive_package = 1; // пакет принят
					cnt1 = 0;
				}
			}
	}

}
