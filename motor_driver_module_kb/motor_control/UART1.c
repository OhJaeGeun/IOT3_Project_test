/*
 * UART.c
 *
 * Created: 2022-07-10 오후 3:11:51
 *  Author: JAEGEUN
 */ 

#define _BV(bit) (1<<Bit)
#include <avr/io.h>

void UART_1_init(void)
{
	//Baudrate 설정 (F_osc : 16MHz => 9600Bps)
	UBRR0H = 0x00;
	//UBRR0L = 207; // 1100 1111???
	UBRR0L = 16; 
	
	// 2배속 모드(= _BV(U2X1))
	// 정확도를 위해 UART는 보통 2배 모드를 사용.
	UCSR0A = UCSR0A | (1<<1);
	
	// 비동기 & 8bit 전송
	UCSR0C |= 0x06;
	
	 // 송,수신 기능 활성화
	 UCSR0B |= _BV(RXEN0);
	 UCSR0B |= _BV(TXEN0);
}

void UART1_transmit(char data)
{
	// 송신 가능 대기
	while(!(UCSR0A & (1 << UDRE0)));
	// 데이터 전송
	UDR0 = data;
}

unsigned char UART1_receive(void)
{
	// Receive Complete 플래그 확인
	while(!(UCSR0A & (1 << RXC0)));
	// Data Register 값 반환
	return UDR0;
	
}
