#include "include/prototype.h"

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
