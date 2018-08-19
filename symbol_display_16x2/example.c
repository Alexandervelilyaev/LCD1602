#include "lm016l.h"

void PrintText(char * data)
{
	unsigned char i = 0;
	while(data[i] != '\0')
	{
		WriteDataToRAM(data[i]);
		i++;
	}
}

int main(void)
{
	//For 8-bit data bus (pins D0-D7) use method "SetPinout8Bits",
	//For 4-bit data bus ((pins D4-D7)) - "SetPinout4Bits"
	

	//Set PORTS(DATA and SETTINGS), pinout and mode of data transmission(4-bit or 8-bit)
	SetPinout4Bits('B', 'C', 0, 1, 4, 5, 6, 7);
	//SetPinout8Bits('B', 'C', 0, 1, 0, 1, 2, 3, 4, 5, 6, 7);

	//Initialize Display
	InitLCD();
	
	//Display is ready for use

	//Print famous phrase
	PrintText("Hello World");

	while (1)
	{
		//ticker effect(interval 1 second)
		_delay_ms(1000);
		CursourOrDisplayShift(1, 1);
	}
}