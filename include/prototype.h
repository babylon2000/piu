/*
 * prototype.h
 *
 *  Created on: 25 сент. 2017
 *      Author: kostiantyn
 */

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

enum states {standby, code, vb, va, configuration, time, rd, power};
enum signals {idle, pd6, pc5, pc3, pc4, pc6, pc7};
enum digit {dig0, dig1, dig2, dig3};
enum value {null, one, two, three, four, five, six, seven, eight, nine};

enum states new_state(enum states, enum signals);
//**************prototypes for forward value************************/
enum value get_value(enum value);
enum value get_value_for_hhour(enum value);
enum value get_value_for_lhour(enum value);
enum value get_value_for_hminutes(enum value);
//******************************************************************/

//****************prototypes for backforward value*****************/
enum value get_bvalue(enum value);
enum value get_bvalue_for_hhour(enum value);
enum value get_bvalue_for_lhour(enum value);
enum value get_bvalue_for_hminutes(enum value);
//******************************************************************/
typedef enum value (*funcv)(enum value);
typedef enum value (*gnv)(enum value, enum signals, funcv, funcv);

enum value get_new_value(enum value, enum signals, funcv, funcv);
enum digit get_new_dig(enum states, enum signals, enum digit);
void set_value(unsigned char*, enum states, enum digit, gnv);

#endif /* PROTOTYPE_H_ */
