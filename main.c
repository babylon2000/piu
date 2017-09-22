#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void init_register(void);

enum states {standby, code, vb, va, configuration, time, rd, power};
enum signals {idle, pd6, pc5, pc3, pc4, pc6, pc7};
enum digit {dig0, dig1, dig2, dig3};
enum value {null, one, two, three, four, five, six, seven, eight, nine};

volatile static uint8_t porthistory = 0xff;
volatile unsigned int cnt3 = 0, cnt7 = 0;

char v[4] = {0, 1, 2, 3};
char* vptr = v;

enum states new_state(enum states, enum signals);
char* get_value_address(enum states, enum signals, enum digit, char*);
enum value get_value(enum value);

typedef enum value (*funcv)(enum value);
typedef enum value (*ptr)(enum value, enum signals, funcv); // pointer to get_new_value();

enum value get_new_value(enum value, enum signals, funcv);
enum value get_limit_value(enum value, enum digit, ptr, enum states);


enum states current_state = standby;
enum signals signal = idle;
enum digit dig = dig0;
enum value current_value = null;

funcv callback_get_value;
ptr callback_get_limit_value;

const char dotsa = 0x01;
const char dotsb = 0x02;
const char dotsd = 0x04;
char dotse = 0x08;
const char dotnull = 0x00;
const char dotsf = 0x10;
const char dotsg = 0x20;
const char dotsi = 0x40;

/*void symcreate(char sym)
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


void showsym(char sym1, char sym2, char sym3, char sym4, const char dots)
{
	symcreate(sym1);

	set_pin_high(PORTA, PA0);
	_delay_us(1);
	set_pin_low(PORTA, PA0);

	symcreate(sym2);

	set_pin_high(PORTA, PA1);
	_delay_us(1);
	set_pin_low(PORTA, PA1);

	symcreate(sym3);

	set_pin_high(PORTA, PA3);
	_delay_us(1);
	set_pin_low(PORTA, PA3);

	symcreate(sym4);

	set_pin_high(PORTA, PA4);
	_delay_us(1);
	set_pin_low(PORTA, PA4);

        dotout(0);
        dotout(dots);
        set_pin_high(PORTA,LED_DOT_COM);
        _delay_us(1);
        set_pin_low(PORTA,LED_DOT_COM);

}*/

void modeHandler()
{
	if((PIND&(1 << PD6)) == 0)
	{
		_delay_ms(40);
		if((PIND&(1 << PD6)))
			signal = pd6;
	}
}


int main()
{
	init_register();
	callback_get_value = get_value;
	callback_get_limit_value = get_new_value;
	sei();

	while(1)
	{
		current_value = get_new_value(current_value, signal, callback_get_value);
		if(current_value == null) PORTA = (1 << PA0)|(1 << PA5);
		if(current_value == one) PORTA = (1 << PA1)|(1 << PA5);
		//init_state(current_state, signal);
		//modeHandler();
		//current_state = new_state(current_state, signal);
		//ptr = get_value_address(current_state, signal, dig, v);
		//signal = idle;
		/*if(current_state == standby) PORTA = (1 << PA0)|(1 << PA5);
		if(current_state == code) PORTA = (1 << PA1)|(1 << PA5);
		if(current_state == vb) PORTA = (1 << PA3)|(1 << PA5);
		if(current_state == va) PORTA = (1 << PA4)|(1 << PA5);
		if(current_state == configuration) PORTA = (1 << PA0)|(1 << PA7);
		if(current_state == time) PORTA = (1 << PA1)|(1 << PA7);
		if(current_state == rd) PORTA = (1 << PA3)|(1 << PA7);
		if(current_state == power) PORTA = (1 << PA4)|(1 << PA7);*/
		//if(ptr == (v + 0)) PORTA = (1 << PA0)|(1 << PA5);
		//if(ptr == (v + 1)) PORTA = (1 << PA1)|(1 << PA5);
		//if(ptr == (v + 2)) PORTA = (1 << PA3)|(1 << PA5);
		//if(ptr == (v + 3)) PORTA = (1 << PA4)|(1 << PA5);
	}
}

enum states new_state(enum states current_state, enum signals sgn)
{
	static enum states st;
	switch(current_state)
	{
		case standby:
			switch(sgn)
			{
				case pd6:
					signal = idle;
					st = code;
				break;
				default:
					signal = idle;
					st =  standby;
				break;
			}
		break;
		case code:
			switch(sgn)
			{
				case pd6:
					signal = idle;
					st = vb;
				break;
				default:
					signal = idle;
					st = code;
				break;
			}
		break;
		case vb:
			switch(sgn)
			{
				case pd6:
					signal = idle;
					st = va;
				break;
				default:
					signal = idle;
					st = vb;
				break;
			}
		break;
		case va:
			switch(sgn)
			{
				case pd6:
					signal = idle;
					st = configuration;
				break;
				default:
					signal = idle;
					st = va;
				break;
			}
		break;

		case configuration:
			switch(sgn)
			{
				case pd6:
					st = standby;
					signal = idle;
				break;

				case pc4:
					st = time;
					signal = idle;
				break;

				case pc6:
					st = power;
					signal = idle;
				break;

				default:
					st = configuration;
					signal = idle;
				break;
			}
		break;

		case time:
			switch(sgn)
			{
				case pd6:
					st = standby;
					signal = idle;
				break;

				case pc4:
					st = rd;
					signal = idle;
				break;

				case pc6:
					st = configuration;
					signal = idle;
				break;

				default:
					st = time;
					signal = idle;
				break;
			}
		break;

		case rd:
			switch(sgn)
			{
				case pd6:
					st = standby;
					signal = idle;
				break;

				case pc4:
					st = power;
					signal = idle;
				break;

				case pc6:
					st = time;
					signal = idle;
				break;

				default:
					st = rd;
					signal = idle;
				break;
			}
		break;

		case power:
			switch(sgn)
			{
				case pd6:
					st = standby;
					signal = idle;
				break;

				case pc4:
					st = configuration;
					signal = idle;
				break;

				case pc6:
					st = rd;
					signal = idle;
				break;

				default:
					st = power;
					signal = idle;
				break;
			}
		break;
	}
	return st;
}

//Обработчик для клавиш PC7 u PC3
char* get_value_address(enum states st, enum signals sgn, enum digit current_digit, char* array_values)
{
	static char* return_address;
	switch(sgn)
	{
		case pc7:
			switch(st)
			{
				case standby:
					return NULL;
				break;

				case code:
					switch(current_digit)
					{
						case dig1:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig2:
							dig = dig1;
							return_address = (array_values + dig1);
						break;

						case dig3:
							dig = dig2;
							return_address = (array_values + dig2);
						break;
					}
				break;

				case vb:
					return NULL;
				break;

				case va:
					switch(current_digit)
					{
						case dig2:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig3:
							dig = dig2;
							return_address = (array_values + dig2);
						break;
					}
				break;

				case configuration:
					switch(current_digit)
					{
						case dig1:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig2:
							dig = dig1;
							return_address = (array_values + dig1);
						break;

						case dig3:
							dig = dig2;
							return_address = (array_values + dig2);
						break;
					}
				break;

				case time:
					switch(current_digit)
					{
						case dig0:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig1:
							dig = dig0;
							return_address = (array_values + dig0);
						break;

						case dig2:
							dig = dig1;
							return_address = (array_values + dig1);
						break;

						case dig3:
							dig = dig2;
							return_address = (array_values + dig2);
						break;
					}
				break;

				case rd:
					return_address = NULL;
				break;

				case power:
					return_address = NULL;
				break;
			}
		break;

		case pc3:
			switch(st)
			{
				case standby:
					return NULL;
				break;

				case code:
					switch(current_digit)
					{
						case dig1:
							dig = dig2;
							return_address = (array_values + dig2);
						break;

						case dig2:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig3:
							dig = dig1;
							return_address = (array_values + dig1);
						break;
					}
				break;

				case vb:
					return NULL;
				break;

				case va:
					switch(current_digit)
					{
						case dig2:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig3:
							dig = dig2;
							return_address = (array_values + dig2);
						break;
					}
				break;

				case configuration:
					switch(current_digit)
					{
						case dig1:
							dig = dig2;
							return_address = (array_values + dig2);
						break;

						case dig2:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig3:
							dig = dig1;
							return_address = (array_values + dig1);
						break;
					}
				break;

				case time:
					switch(current_digit)
					{
						case dig0:
							dig = dig1;
							return_address = (array_values + dig1);
						break;

						case dig1:
							dig = dig2;
							return_address = (array_values + dig2);
						break;

						case dig2:
							dig = dig3;
							return_address = (array_values + dig3);
						break;

						case dig3:
							dig = dig0;
							return_address = (array_values + dig0);
						break;
					}
				break;

				case rd:
					return_address = NULL;
				break;

				case power:
					return_address = NULL;
				break;
			}
		break;

        default:
        break;
	}
	return return_address;
}

enum value get_new_value(enum value current_value, enum signals sg, enum value (*f)(enum value v))
{
	static enum value nwvl;
	switch(sg)
	{
		case pc4:
			nwvl = f(current_value);
			signal = idle;
		break;

		case pc6:
			nwvl = nine - f(current_value);
			signal = idle;
		break;

		default:
			signal = idle;
		break;
	}
	return nwvl;
}



enum value get_value(enum value current_value)
{
	static enum value new_value;
	switch(current_value)
	{
		case null:
			new_value = one;
		break;

		case one:
			new_value = two;
		break;

		case two:
			new_value = three;
		break;

		case three:
			new_value = four;
		break;

		case four:
			new_value = five;
		break;

		case five:
			new_value = six;
		break;

		case six:
			new_value = seven;
		break;

		case seven:
			new_value = eight;
		break;

		case eight:
			new_value = nine;
		break;

		case nine:
			new_value = null;
		break;
	}
	return new_value;
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
