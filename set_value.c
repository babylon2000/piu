#include "include/prototype.h"

#define CHAR_PREFIX 0x30

extern enum states current_state;
extern enum signals signal;
extern enum digit dig;
extern enum value current_value;

void set_value(unsigned char* data, enum states st, enum digit d, gnv val)
{
	switch(st)
	{
		case standby:
			data[0] = 'S';
			data[1] = 'N';
			data[2] = 'N';
			data[3] = 'N';
		break;

		case code:
			data[0] = 'C';
			//data[1] = CHAR_PREFIX;
			//data[2] = CHAR_PREFIX;
			//data[3] = CHAR_PREFIX;
			if(d == dig1)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[1] = current_value + CHAR_PREFIX;
			}
			if(d == dig2)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[2] = current_value + CHAR_PREFIX;
			}
			if(d == dig3)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[3] = current_value + CHAR_PREFIX;
			}
		break;

		case vb:
			data[0] = 'V';
			data[1] = 'B';
			data[2] = 'N';
			data[3] = 'N';
		break;

		case va:
			data[0] = 'V';
			data[1] = 'A';
			if(d == dig2)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[2] = current_value + CHAR_PREFIX;
			}
			if(d == dig3)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[3] = current_value + CHAR_PREFIX;
			}
		break;

		case configuration:
			data[1] = 'P';
			if(d == dig1)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[1] = current_value + CHAR_PREFIX;
			}
			if(d == dig2)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[2] = current_value + CHAR_PREFIX;
			}
			if(d == dig3)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[3] = current_value + CHAR_PREFIX;
			}
		break;

		case time:
			if(d == dig0)
			{
				current_value = val(current_value, signal, get_value_for_hhour, get_bvalue_for_hhour);
				data[0] = current_value + CHAR_PREFIX;
			}
			if(d == dig1)
			{
				if((data[0] == 0x30) || (data[0] == 0x31)) current_value = val(current_value, signal, get_value, get_bvalue);
				if(data[0] == 0x32) current_value = val(current_value, signal, get_value_for_lhour, get_bvalue_for_lhour);
				data[1] = current_value + CHAR_PREFIX;
			}
			if(d == dig2)
			{
				current_value = val(current_value, signal, get_value_for_hminutes, get_bvalue_for_hminutes);
				data[2] = current_value + CHAR_PREFIX;
			}
			if(d == dig3)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[3] = current_value + CHAR_PREFIX;
			}
		break;

		case rd:
			data[0] = 'r';
			data[1] = 'd';
			data[2] = 'N';
			data[3] = 'N';
		break;

		case power:
			data[0] = 'P';
			if(d == dig1)
			{
				current_value = val(current_value, signal, get_value, get_bvalue);
				data[1] = current_value + CHAR_PREFIX;
			}
		break;
	}
}

