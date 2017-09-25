#include <stdio.h>

//volatile static uint8_t porthistory = 0xff;
//volatile unsigned int cnt3 = 0, cnt7 = 0, cnt4 = 0, cnt6 = 0;

unsigned char v[4];
//unsigned char* vptr = v;

#include "prototype.h"

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









