#include "include/prototype.h"

enum value get_bvalue_for_hhour(enum value current_value)
{
	enum value new_value;
	switch(current_value)
	{
		case null:
			new_value = two;
		break;

		case one:
			new_value = null;
		break;

		case two:
			new_value = one;
		break;
	}
	return new_value;
}
