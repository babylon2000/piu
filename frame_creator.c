/*
 * Выделяем динамически память для массива размерностью 8 байт, т.к наш фрейм именно такой размерности и инициализируем его
 * освобождение памяти произойдет после успешной передачи данных!
 */
#include <stdlib.h>
#include "prototype.h"
#include "crc8.h"
#include "frame_creator.h"

#define FRAME_LEN	8
#define START_BYTE	0x01
#define FINISH_BYTE	0x10

unsigned char* frame_creator(unsigned char* data, enum states st, crc8_t crc)
{
	unsigned char* frame = (unsigned char*)calloc(FRAME_LEN, sizeof(unsigned char));
	if(frame == NULL) goto fail;
	frame[0] = START_BYTE;
	frame[1] = st;
	for(register int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
	{
		frame[i + 2] = data[i];
	}
	frame[6] = crc(data, sizeof(data)/sizeof(data[0]));
	frame[7] = FINISH_BYTE;

	return frame;

	fail:
		free(frame);
		return NULL;
}
