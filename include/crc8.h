/*
 * crc8.h
 *
 *  Created on: 25 сент. 2017
 *      Author: kostiantyn
 */

#ifndef CRC8_H_
#define CRC8_H_

unsigned char crc8(unsigned char*, unsigned char);
typedef unsigned char (*crc8_t)(unsigned char*, unsigned char);

#endif /* CRC8_H_ */
