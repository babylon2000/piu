#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


void uart_init(unsigned int ubrr)
{
	UBRR0H = (unsigned int)(ubrr >> 8);
	UBRR0L = (unsigned int)ubrr;
	UCSR0B = (1 << RXCIE0)|(1 << RXEN0)|(1 << TXEN0)|(0 << UCSZ02); //receiver and transmitter enable
	UCSR0C = (1 << URSEL0)|(1 << UPM01)|(1 << UCSZ01)|(1 << UCSZ00); // even parity, 1 stop bit, 8-bit frame
}

void uart_send_byte(unsigned char byte)
{
	while((UCSR0A&(1 << UDRE0)) == 0);
	UDR0 = byte;
}

void uart_send_package(unsigned char* package, char len)
{
	cli();
	uart_send_byte(*(package + 0));
	uart_send_byte(*(package + 1));
	uart_send_byte(*(package + 2));
	uart_send_byte(*(package + 3));
	uart_send_byte(*(package + 4));
	uart_send_byte(*(package + 5));
	uart_send_byte(*(package + 6));
	uart_send_byte(*(package + 7));
	sei();
}
