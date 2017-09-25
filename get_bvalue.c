#include "prototype.h"

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

