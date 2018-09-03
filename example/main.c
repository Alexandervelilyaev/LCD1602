#include "../lcd1602/lcd1602.h"
#include <util/delay.h>

void PrintText(char * data)
{
	for (uint8_t i = 0; data[i] != '\0'; i++)
	{
		WriteDataToRAM(data[i]);
	}
}

int main(void)
{
	//Set PORTS(DATA and SETTINGS), pinout and mode of data transmission(4-bit or 8-bit)
	SetPinout4Bits('B', 'C', 0, 1, 4, 5, 6, 7);

	//Initialize Display
	InitLCD();
	
	//Print famous phrase
	PrintText("Hello World");

	while (1)
	{
		//ticker effect(interval 1 second)
		_delay_ms(1000);
		CursourOrDisplayShift(1, 1);
	}
}