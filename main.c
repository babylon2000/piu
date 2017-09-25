#include <stdio.h>

enum states {standby, code, vb, va, configuration, time, rd, power};
enum signals {idle, pd6, pc5, pc3, pc4, pc6, pc7};
enum digit {dig0, dig1, dig2, dig3};
enum value {null, one, two, three, four, five, six, seven, eight, nine};

//volatile static uint8_t porthistory = 0xff;
//volatile unsigned int cnt3 = 0, cnt7 = 0, cnt4 = 0, cnt6 = 0;

unsigned char v[4];
//unsigned char* vptr = v;

enum states new_state(enum states, enum signals);
//**************prototypes for forward value************************/
enum value get_value(enum value);
enum value get_value_for_hhour(enum value);
enum value get_value_for_lhour(enum value);
enum value get_value_for_hminutes(enum value);
//******************************************************************/

//****************prototypes for backforward value*****************/
enum value get_bvalue(enum value);
enum value get_bvalue_for_hhour(enum value);
enum value get_bvalue_for_lhour(enum value);
enum value get_bvalue_for_hminutes(enum value);
//******************************************************************/
typedef enum value (*funcv)(enum value);

enum value get_new_value(enum value, enum signals, funcv, funcv);
enum digit get_new_dig(enum states, enum signals, enum digit);

enum states current_state = standby;
enum signals signal = idle;
enum digit dig = dig0;
enum value current_value = null;

funcv callback_get_value;

int main(int argc, char **argv) {

	while(1)
	{

	}
	return 0;
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
					st = code;
				break;
				default:
					st =  standby;
				break;
			}
		break;
		case code:
			switch(sgn)
			{
				case pd6:
					st = vb;
				break;
				default:
					st = code;
				break;
			}
		break;
		case vb:
			switch(sgn)
			{
				case pd6:
					st = va;
				break;
				default:
					st = vb;
				break;
			}
		break;
		case va:
			switch(sgn)
			{
				case pd6:
					st = configuration;
				break;
				default:
					st = va;
				break;
			}
		break;

		case configuration:
			switch(sgn)
			{
				case pd6:
					st = time;
				break;

				default:
					st = configuration;
				break;
			}
		break;

		case time:
			switch(sgn)
			{
				case pd6:
					st = rd;
				break;

				default:
					st = time;
				break;
			}
		break;

		case rd:
			switch(sgn)
			{
				case pd6:
					st = power;
				break;

				default:
					st = rd;
				break;
			}
		break;

		case power:
			switch(sgn)
			{
				case pd6:
					st = standby;
				break;

				default:
					st = power;
				break;
			}
		break;
	}
	return st;
}

enum digit get_new_dig(enum states st, enum signals sgn, enum digit current_digit)
{
	static enum digit d;
	switch(sgn)
	{
		case pc7:
			switch(st)
			{
				case standby:
					d = current_digit;
				break;

				case code:
					switch(current_digit)
					{
						case dig1:
							d = dig3;
						break;

						case dig2:
							d = dig1;
						break;

						case dig3:
							d = dig2;
						break;
					}
				break;

				case vb:
					d = current_digit;
				break;

				case va:
					switch(current_digit)
					{
						case dig2:
							d = dig3;
						break;

						case dig3:
							d = dig2;
						break;
					}
				break;

				case configuration:
					switch(current_digit)
					{
						case dig1:
							d = dig3;
						break;

						case dig2:
							d = dig1;
						break;

						case dig3:
							d = dig2;
						break;
					}
				break;

				case time:
					switch(current_digit)
					{
						case dig0:
							d = dig3;
						break;

						case dig1:
							d = dig0;
						break;

						case dig2:
							d = dig1;
						break;

						case dig3:
							d = dig2;
						break;
					}
				break;

				case rd:
					d = current_digit;
				break;

				case power:
					d = current_digit;
				break;
			}
		break;

		case pc3:
			switch(st)
			{
				case standby:
					d = current_digit;
				break;

				case code:
					switch(current_digit)
					{
						case dig1:
							d = dig2;
						break;

						case dig2:
							d = dig3;
						break;

						case dig3:
							d = dig1;
						break;
					}
				break;

				case vb:
					d = current_digit;
				break;

				case va:
					switch(current_digit)
					{
						case dig2:
							d = dig3;
						break;

						case dig3:
							d = dig2;
						break;
					}
				break;

				case configuration:
					switch(current_digit)
					{
						case dig1:
							d = dig2;
						break;

						case dig2:
							d = dig3;
						break;

						case dig3:
							d = dig1;
						break;
					}
				break;

				case time:
					switch(current_digit)
					{
						case dig0:
							d = dig1;
						break;

						case dig1:
							d = dig2;
						break;

						case dig2:
							d = dig3;
						break;

						case dig3:
							d = dig0;
						break;
					}
				break;

				case rd:
					d = current_digit;
				break;

				case power:
					d = current_digit;
				break;
			}
		break;

		default:
			d = current_digit;
		break;
	}
	return d;
}

enum value get_new_value(enum value current_value, enum signals sg, funcv forward, funcv backforward)
{
	static enum value nwvl;
	switch(sg)
	{
		case pc4:
			nwvl = forward(current_value);
		break;

		case pc6:
			nwvl = backforward(current_value);
		break;

		default:
			nwvl = current_value;
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

enum value get_bvalue(enum value current_value)
{
	static enum value new_value = 0;
	switch(current_value)
	{
		case null:
			new_value = nine;
		break;

		case one:
			new_value = null;
		break;

		case two:
			new_value = one;
		break;

		case three:
			new_value = two;
		break;

		case four:
			new_value = three;
		break;

		case five:
			new_value = four;
		break;

		case six:
			new_value = five;
		break;

		case seven:
			new_value = six;
		break;

		case eight:
			new_value = seven;
		break;

		case nine:
			new_value = eight;
		break;
	}
	return new_value;
}
