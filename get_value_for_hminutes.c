#include "prototype.h"

enum value get_value_for_hminutes(enum value current_value)
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
			new_value = three;
		break;

		case three:
			new_value = four;
		break;

		case four:
			new_value = five;
		break;

		case five:
			new_value = null;
		break;
	}
	return new_value;
}
