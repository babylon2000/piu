
#ifndef UART_H_
#define UART_H_

void uart_init(unsigned int);
void uart_send_byte(unsigned char);
int uart_send_package(unsigned char*, char len);

#endif /* UART_H_ */
