#define F_CPU 8000000UL //8Mhz - frequency of CPU (Change this value if frequency of your CPU is different)
#include "../lcd1602/lcd1602.h"
#include <util/delay.h>
#include <stdlib.h>

int main(void)
{
	//Set PORTS(DATA and SETTINGS), pinout and mode of data transmission(4-bit or 8-bit)
	SetPinout4Bits('B', 'C', 0, 1, 4, 5, 6, 7);

	//Initialize Display
	InitLCD();
	
	//Print famous phrase
	PrintText("Hello World");
	SetPosition(1, 0);
	PrintText("Привет, мир ");

	//Print number value
	char number[5] = "";
	itoa(200, number, 10);
	PrintText(number);


	while (1)
	{
		//ticker effect(interval 1 second)
		_delay_ms(1000);
		ShiftLeft(1, 1);
	}
}