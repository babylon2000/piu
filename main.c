#include <stdio.h>
#include <stdlib.h>

//volatile static uint8_t porthistory = 0xff;
//volatile unsigned int cnt3 = 0, cnt7 = 0, cnt4 = 0, cnt6 = 0;
//unsigned char* vptr = v;
#include "crc8.h"
#include "prototype.h"
#include "frame_creator.h"

#define LEN	4

enum states current_state = code;
enum signals signal = pc4;
enum digit dig = dig1;
enum value current_value = null;

unsigned char a[8];

int main(int argc, char **argv) {

	while(1)
	{
		set_value(v, current_state, dig, get_new_value);
		unsigned char* f = frame_creator(v, current_state, crc8);
		for(int i = 0; i < 8; i++)
		{
			a[i] = f[i];
		}
		free(f);
	}
	return 0;
}









