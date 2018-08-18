#include <avr/io.h>
#include "lm016l.h"

void SendString(char * data)
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
	SetPinout('B', 'C', 0, 1, 0, 1, 2, 3, 4, 5, 6, 7);
	InitLCD();
	ClearDisplay();
	ReturnHome();
	Display_On_Off(1,0,0);
	SendString("Hello World");

	while (1)
	{
		_delay_ms(1000);
		CursourOrDisplayShift(1, 1);
	}
}