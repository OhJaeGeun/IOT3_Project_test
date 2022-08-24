#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <wiringSerial.h>

//#include <curses.h>
//#include <conio.h>

//#include "linux_kbhit.h"
#include "my_conio.h"

#define BAUD 115200

#define UP 65
#define DOWN 66
#define LEFT 68
#define RIGHT 67
#define STOP 32

int main(void)
{
	int fd;
	char con;

	init_keyboard();
	//sleep(1);
	if((fd = serialOpen("/dev/ttyS0", BAUD)) < 0){
	//if((fd = serialOpen("/dev/ttyAMA1", BAUD)) < 0){
		printf("Device file open error!! use sudo ...\n");
		return 1;
	}
	printf("[UART test with Arduino board]\n");
	serialPuts(fd, "[UART test with Arduino board]\n");

	printf("start : please press the con\n");
	//sleep(1);
	con = 'S';
	//sleep();
	//printf("%d********\n",con); 
	serialPutchar(fd, con);
	//sleep(5);

	while(1){
		//printf("\nInput a arrow keys: ");

		if(_kbhit()){
			con = _getch();
			//printf("%c******", con);
			if(con == UP || con == DOWN || con == LEFT || con == RIGHT)
				con = con;
			else if(con == STOP)
				con = 'S';
			else
				continue;
			
			printf("%d \n", con);
			serialPutchar(fd, con);
			
			continue;
			//sleep(0.5);
			//serialFlush(fd);
		}
		//con = 'S';
		//sleep();
		//printf("%d********\n",con); 
		//serialPutchar(fd, con);
	}
	close_keyboard();

	return 0;
}
