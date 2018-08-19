![lm016l Banner](https://micro-pi.ru/wp-content/uploads/2016/10/%D0%9F%D0%BE%D0%B4%D0%BA%D0%BB%D1%8E%D1%87%D0%B5%D0%BD%D0%B8%D0%B5-HD44780-%D0%BA-ATmega16-LM016L-LCD-16x2-3.png)
# Simple library for lcd "LM016L"
This library encapsulates most necessary functions(according to datasheet) for working with this display.

## Display Commands:

* Clear all display data and reset AC(address counter):
```c 
void ClearDisplay() 
``` 

* Reset AC(address counter):
```c
void ReturnHome() 
```

* Set entry mode. I_D - (1: cursor moves right and DDRAM address increased by 1, 1: cursor moves left and DDRAM address decreased by 1), SH - shifting enable
```c
void EntryModeSet(unsigned char I_D, unsigned char SH)
```
    
* **ON/OFF** Display/Cursor/Blink == 1 then turn on else turn off
```c
void Display_On_Off(unsigned char Display, unsigned char Cursor, unsigned char Blink)
```

* **Cursor or Display Shift**. S_C - (0: moves cursor, 1: moves all the display), R_L - (0: left, 1: right)
```c
void CursourOrDisplayShift(unsigned char S_C, unsigned char R_L)
```

* Set CGRAM address to AC:
```c 
void SetCGRAMAddress(unsigned char address)
```

* Set DDRAM address to AC:
```c
void SetDDRAMAddress(unsigned char address)
```

* Write binary 8-bit data to DDRAM/CGRAM:
```c
void WriteDataToRAM(unsigned char data)
```
    
## Setting functions:

* Set pin numbers and ports using 4-bit data bus:
```c
void SetPinout4Bits(unsigned char data_port, unsigned char setting_port, unsigned char rs, unsigned char e, unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7)
```

* Set pin numbers and ports using 8-bit data bus:
```c
void SetPinout8Bits(unsigned char data_port, unsigned char setting_port, unsigned char rs, unsigned char e, unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7)
```

* Display initializing
```c    
void InitLCD()
```
    
**Note:** For 8-bit data bus (pins D0-D7) use method "**SetPinout8Bits**", for 4-bit data bus (pins D4-D7) - "**SetPinout4Bits**"
    
## Example

```c
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
```

    
