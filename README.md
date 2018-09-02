![lm016l Banner](https://micro-pi.ru/wp-content/uploads/2016/10/%D0%9F%D0%BE%D0%B4%D0%BA%D0%BB%D1%8E%D1%87%D0%B5%D0%BD%D0%B8%D0%B5-HD44780-%D0%BA-ATmega16-LM016L-LCD-16x2-3.png)
# Simple AVR library for LCD1602(LM016L) which is based on HD44780
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
void EntryModeSet(uint8_t I_D, uint8_t SH)
```
    
* **ON/OFF** Display/Cursor/Blink == 1 then turn on else turn off
```c
void Display_On_Off(uint8_t Display, uint8_t Cursor, uint8_t Blink)
```

* **Cursor or Display Shift**. S_C - (0: moves cursor, 1: moves all the display), R_L - (0: left, 1: right)
```c
void CursourOrDisplayShift(uint8_t S_C, uint8_t R_L)
```

* Set CGRAM address to AC:
```c 
void SetCGRAMAddress(uint8_t address)
```

* Set DDRAM address to AC:
```c
void SetDDRAMAddress(uint8_t address)
```

* Write binary 8-bit data to DDRAM/CGRAM:
```c
void WriteDataToRAM(uint8_t data)
```
    
## Setting functions:

* Set pin numbers and ports using 4-bit data bus:
```c
void SetPinout4Bits(uint8_t data_port, uint8_t setting_port, uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
```

* Set pin numbers and ports using 8-bit data bus:
```c
void SetPinout8Bits(uint8_t data_port, uint8_t setting_port, uint8_t rs, uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
```

* Display initializing
```c    
void InitLCD()
```
    
**Note:** For 8-bit data bus (pins D0-D7) use method "**SetPinout8Bits**", for 4-bit data bus (pins D4-D7) - "**SetPinout4Bits**"
    
## Example 1 (4-bit data bus)

### Circuit
![lm016l Banner](https://github.com/Alexandervelilyaev/lm016l/blob/master/circuits/circuit4-bit%20data%20bus.png?raw=true)

### Code
```c
#include "lcd1602_base.h"
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
```

## Example 2 (8-bit data bus)

### Circuit
![lm016l Banner](https://github.com/Alexandervelilyaev/lm016l/blob/master/circuits/circuit8-bit%20data%20bus.png?raw=true)

### Code
```c
#include "lcd1602_base.h"
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
	SetPinout8Bits('B', 'C', 0, 1, 0, 1, 2, 3, 4, 5, 6, 7);

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

    
