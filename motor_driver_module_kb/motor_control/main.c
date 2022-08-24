#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>
//#include <conio.h>

#include "UART1.h"

#define UP 65
#define DOWN 66
#define LEFT 68
#define RIGHT 67
#define STOP 32

/*
PB0 input 1
PD4 input 2
PB2 enable A
PB3 enable B
PB4 input 3
PB5 input 4
*/

void setPwm()
{
	//TCCR1A |= (1 << WGM11) | (1 << WGM10);
	//TCCR1A |= (1 << COM1A1);
	//TCCR1B |= (1 << CS12);
	
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	//TCCR2A |= (1 << WGM22) | (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
	TCCR2B |= (1 << CS22);
}

void port_init()
{
	PORTB = 0x00;
	PORTD = 0x00;
}
void setPort(char motor_left_pb, char motor_right_pd)
{
	PORTB = motor_left_pb; // motor_right_pb | motor_left_pb;
	PORTD = motor_right_pd;
}
void setSpeed(int left_wheel, int right_wheel)
{
	OCR2A = left_wheel; // left
	OCR2B = right_wheel; // right
}

int main(void)
{
	int data;
	
	DDRB = 0xFF; // 0011 1000
	DDRD = 0x1C; // 0001 1100
	
	setPwm();
	port_init();
	UART_1_init(); // UART1 초기화
	
	//_delay_ms(1000);
	
	while(1)
	{
		//setPort(0x00, 0x00);
		_delay_ms(50);
		
		setSpeed(0, 0);
		
		port_init();
		
		data = UART1_receive();
		
		if(data == 'A'){ // up
			setSpeed(110, 110);
			setPort(0x28, 0x18);
		}
		else if(data == 'B'){ // down
			setSpeed(120, 120);
			setPort(0x18, 0x0C);
		}
		else if(data == 'C'){ // left
			setSpeed(175, 175);
			setPort(0x28, 0x0C);
			//_delay_ms(150);
		}
		else if(data == 'D'){ // right
			setSpeed(175, 175);
			setPort(0x18, 0x18);
			//_delay_ms(150);
		}
		else if(data == 'S'){
			setSpeed(0, 0);
			setPort(0x00, 0x00);
		}
	}
	return 0;
}



/*
int main(void)
{
	//char motor_left = 0x05;   // 0000 0'1'01
	//char motor_right = 0x28;  // 0010 '1'000
	char motor_left = 0x00;
	char motor_right = 0x00;
	
	//int cnt = 0;
	int data;
	
	DDRB = 0xFF;
	
	pwm_init();
	port_init();
	UART_1_init(); // UART1 초기화
	
	//_delay_ms(1000);
	
	while(1)
	{
		PORTB = motor_left | motor_right;
		
		_delay_ms(50);
		
		port_init();
		
		data = UART1_receive();
		
		if(data == 'A'){ // up
			OCR1B = 200;
			OCR2A = 200;
			
			motor_left = 0x05;  // 0000 0'1'10
			motor_right = 0x28; // 0010 '1'000
			//motor_left = 0x05;  // 0000 0'1'10
			//motor_right = 0x18; // 0010 '1'000
		}
		else if(data == 'B'){ // down
			OCR1B = 150;
			OCR2A = 150;
			
			motor_left = 0x05;  // 0000 0'1'10
			motor_right = 0x18; // 0010 '1'000
			//motor_left = 0x06;  // 0000 0'1'10
			//motor_right = 0x28; // 0010 '1'000
		}
		else if(data == 'C'){ // left
			OCR1B = 100;
			OCR2A = 100;
			
			motor_left = 0x05;
			motor_right = 0x28;
			//motor_left = 0x06;
			//motor_right = 0x18;
		}
		else if(data == 'D'){ // right
			OCR1B = 100;
			OCR2A = 100;
			motor_left = 0x06;
			motor_right = 0x18;
			//motor_left = 0x05;
			//motor_right = 0x28;
		}
		else if(data == 'S'){
			OCR1B = 0;
			OCR2A = 0;
			motor_left = 0x00;
			motor_right = 0x00;
		}
	}
	return 0;
}
*/



/*
int main(void)
{
	char motor_left_pb = 0x00; // input 3
	char motor_left_pd = 0x00; // input 4
	char motor_right_pb = 0x00; // input 1, 2
	//char motor_right_pd = 0x00; // input x
	
	//int cnt = 0;
	int data;
	
	DDRB = 0xFF;
	DDRD = 0x08;
	
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1);
	TCCR2B |= (1 << CS22);
	
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1A |= (1 << COM1B1);
	TCCR1B |= (1 << CS12);

	PORTB = 0x00;
	PORTD = 0x00;
	
	//OCR1B = 10;
	//OCR2A = 10;
	
	UART_1_init(); // UART1 초기화
	
	//_delay_ms(1000);
	
	while(1)
	{
		PORTB = motor_right_pb | motor_left_pb;
		PORTD = motor_left_pd; // motor_right_pd | motor_left_pd;
		_delay_ms(50);
		
		OCR1A = 0;
		OCR1B = 0;	
		OCR2A = 0;
		OCR2B = 0;
		
		PORTB = 0x00;
		PORTD = 0x00;
		
		data = UART1_receive();
		
		if(data == 'A'){ // up
			OCR2A = 0;
			OCR2B = 100;
			
			motor_right_pb = 0x04; // 0000 0100
			
			OCR1A = 0;
			OCR1B = 100;
			
			motor_left_pb = 0x00; // 0000 0000
			motor_left_pd = 0x08; // 0000 1000
		}
		else if(data == 'B'){ // down
			OCR1A = 100;
			OCR1B = 0;
			
			OCR2A = 100;
			OCR2B = 0;
			
			//motor_right_pb = 0x04; // 0000 0100
			motor_right_pb = 0x02; // 0000 0010
			//motor_left_pb = 0x00; // 0000 0000
			//motor_left_pd = 0x08; // 0000 1000
			motor_left_pb = 0x08; // 0000 1000
			motor_left_pd = 0x00; // 0000 0000
		}
		else if(data == 'C'){ // left
			OCR1A = 100;
			OCR1B = 0;
			
			OCR2A = 0;
			OCR2B = 100;
			
			//motor_right_pb = 0x04; // 0000 0100
			motor_right_pb = 0x02; // 0000 0010
			motor_left_pb = 0x00; // 0000 0000
			motor_left_pd = 0x08; // 0000 1000
			//motor_left_pb = 0x08; // 0000 1000
			//motor_left_pd = 0x00; // 0000 0000
		}
		else if(data == 'D'){ // right
			OCR1A = 0;
			OCR1B = 100;
			
			OCR2A = 100;
			OCR2B = 0;
			
			motor_right_pb = 0x04; // 0000 0100
			//motor_right_pb = 0x02; // 0000 0010
			//motor_left_pb = 0x00; // 0000 0000
			//motor_left_pd = 0x08; // 0000 1000
			motor_left_pb = 0x08; // 0000 1000
			motor_left_pd = 0x00; // 0000 0000
		}
		else if(data == 'S'){
			OCR1A = 0;
			OCR1B = 0;
			
			OCR2A = 0;
			OCR2B = 0;
			
			motor_right_pb = 0x00;
			motor_left_pd = 0x00;
			motor_left_pb = 0x00;
		}
	}
	return 0;
}
*/




// motor button
/*
#define F_CPU 160000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	char motor_left = 0x05;   // 0000 0'1'01
	char motor_right = 0x28;  // 0010 '1'000
	//char state = 0;
	
	DDRB = 0xFF;
	DDRD = 0x00;
	
	PORTD = 0x0C; // 0000 1100
	
	while(1)
	{
		PORTB = motor_left | motor_right; // 00101101
		//if((PIND & 0x04) == 0x00 && state == 0){
		//}
		if((PIND & 0x04) == 0x00){
			motor_left = 0x05;
			motor_right = 0x28;
		}
		if((PIND & 0x08) == 0x00){
			motor_left = 0x06;
			motor_right = 0x18; // 0001 1000
		}
	}
	
}
*/

// motor PWM
/*
#define F_CPU 160000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0xFF;
	
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1A |= (1 << COM1B1);
	TCCR1B |= (1 << CS12);
	
	PORTB = 0x00;

	while (1)
	{
		PORTB = 0x05; //0000 0101
		//_delay_ms(1000);
		
		//OCR1B = 0;
		for(int i = 0; i < 256; i += 5){
			OCR1B = i;
			_delay_ms(10);
		}
		OCR1B = 0;
		
		PORTB = 0x06; // 0000 0011
		//_delay_ms(1000);
		
		for(int i = 0; i < 256; i += 5){
			OCR1B = i;
			_delay_ms(10);
		}
		OCR1B = 0;
		
		PORTB = 0x00;
		_delay_ms(100);
	}
}
*/

