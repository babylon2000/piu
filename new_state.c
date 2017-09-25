#include "prototype.h"

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
