/*
 * UART1.h
 *
 * Created: 2022-08-21 오후 8:52:57
 *  Author: JAEGEUN
 */ 


#ifndef UART1_H_
#define UART1_H_

void UART_1_init(void); // 초기화
void UART1_transmit(char data); // 송신
unsigned char UART1_receive(void); // 수신



#endif /* UART1_H_ */