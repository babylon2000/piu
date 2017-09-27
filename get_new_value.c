#include "include/prototype.h"

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
