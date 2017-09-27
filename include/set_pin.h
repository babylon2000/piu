/*
 * set_pin.h
 *
 *  Created on: 27 сент. 2017
 *      Author: kostiantyn
 */

#ifndef SET_PIN_H_
#define SET_PIN_H_

#define set_pin_high(port, pin) port |= (1 << pin)
#define set_pin_low(port, pin) port &=~ (1 << pin)

#endif /* SET_PIN_H_ */
