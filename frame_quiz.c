#include <stdlib.h>
#include "include/prototype.h"
#include "include/crc8.h"
#include "include/frame_creator.h"

#define FRAME_LEN	8
#define START_BYTE	0xFF
#define FINISH_BYTE	0x10

unsigned char* frame_quiz()
{
	unsigned char* frame = (unsigned char*)calloc(FRAME_LEN, sizeof(unsigned char));
	if(frame == NULL) goto fail;
	frame[0] = START_BYTE;
	frame[1] = 1;
	for(register int i = 0; i < FRAME_LEN/2; i++)
	{
		frame[i + 2] = (i/2);
	}
	frame[6] = frame[2]&frame[3]&frame[4]&frame[5];
	frame[7] = FINISH_BYTE;

	return frame;

	fail:
		free(frame);
		return NULL;
}
