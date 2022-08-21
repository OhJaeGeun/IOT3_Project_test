/*
 * UART.h
 *
 * Created: 2022-07-10 오후 3:21:04
 *  Author: JAEGEUN
 */ 


#ifndef UART_H_
#define UART_H_

void UART_1_init(void); // 초기화
void UART1_transmit(char data); // 송신
unsigned char UART1_receive(void); // 수신



#endif /* UART_H_ */
