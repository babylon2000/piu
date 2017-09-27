#include "include/prototype.h"

enum value get_bvalue_for_hminutes(enum value current_value)
{
	enum value new_value;
	switch(current_value)
	{
		case null:
			new_value = five;
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
	}
	return new_value;
}
