#include "include/prototype.h"

enum value get_value_for_hhour(enum value current_value)
{
	enum value new_value;
	switch(current_value)
	{
		case null:
			new_value = one;
		break;

		case one:
			new_value = two;
		break;

		case two:
			new_value = null;
		break;
	}
	return new_value;
}
