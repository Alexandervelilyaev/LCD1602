#include "lcd1602.h"

#define DELAY0 38
#define DELAY1 1520
#define SET_BIT(PORT, POS, VALUE) PORT = (PORT & ~(1 << POS)) | (VALUE << POS)
#define GET_BIT(PORT, POS) (PORT & (1 << POS)) >> POS

uint8_t DATA_BUS, SETTING_BUS;
uint8_t RS, E, D0, D1, D2, D3, D4,D5, D6, D7;
uint8_t DL;//Data Length: (1 - 8 bit DATA_BUS, 0 - 4 bit DATA_BUS)
uint8_t AC = 0;

#ifdef RUSSIAN
uint8_t buf_cntr = 0;
uint8_t CGRAM_Buffer[8] = "\0\0\0\0\0\0\0\0";
uint8_t RUSSIAN_PATTERNS[45][8] ={{0b11111,0b10001,0b10000,0b11110,0b10001,0b10001,0b11110,0b00000},/*Б*/{0b11111,0b10001,0b10000,0b10000,0b10000,0b10000,0b10000,0b00000},/*Г*/{0b01111,0b00101,0b00101,0b01001,0b10001,0b11111,0b10001,0b00000},/*Д*/{0b01010,0b00000,0b11111,0b10000,0b11110,0b10000,0b11111,0b00000},/*Ё*/{0b10101,0b10101,0b10101,0b01110,0b10101,0b10101,0b10101,0b00000},/*Ж*/{0b11110,0b00001,0b00001,0b00110,0b00001,0b00001,0b11110,0b00000},/*З*/{0b10001,0b10001,0b10011,0b10101,0b11001,0b10001,0b10001,0b00000},/*И*/{0b10101,0b10001,0b10011,0b10101,0b11001,0b10001,0b10001,0b00000},/*Й*/{0b01111,0b00101,0b00101,0b00101,0b00101,0b10101,0b01001,0b00000},/*Л*/{0b11111,0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b00000},/*П*/{0b01110,0b00100,0b01110,0b10101,0b01110,0b00100,0b01110,0b00000},/*Ф*/{0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b11111,0b00001},/*Ц*/{0b10001,0b10001,0b10001,0b01111,0b00001,0b00001,0b00001,0b00000},/*Ч*/{0b10101,0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00000},/*Ш*/{0b10101,0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00001},/*Щ*/{0b11000,0b01000,0b01000,0b01110,0b01001,0b01001,0b01110,0b00000},/*Ъ*/{0b10001,0b10001,0b10001,0b11001,0b10101,0b10101,0b11001,0b00000},/*Ы*/{0b01000,0b01000,0b01000,0b01110,0b01001,0b01001,0b01110,0b00000},/*Ь*/{0b01110,0b10001,0b00101,0b01011,0b00001,0b10001,0b01110,0b00000},/*Э*/{0b10010,0b10101,0b10101,0b11101,0b10101,0b10101,0b10010,0b00000},/*Ю*/{0b01111,0b10001,0b10001,0b01111,0b00101,0b01001,0b10001,0b00000},/*Я*/{0b00011,0b01100,0b10000,0b11110,0b10001,0b10001,0b01110,0b00000},/*б*/{0b00000,0b00000,0b11110,0b10001,0b11110,0b10001,0b11110,0b00000},/*в*/{0b00000,0b00000,0b11111,0b10001,0b10000,0b10000,0b10000,0b00000},/*г*/{0b00000,0b00110,0b01010,0b01010,0b01010,0b11111,0b10001,0b00000},/*д*/{0b01010,0b00000,0b01110,0b10001,0b11111,0b10000,0b01110,0b00000},/*ё*/{0b00000,0b00000,0b10101,0b10101,0b01110,0b10101,0b10101,0b00000},/*ж*/{0b00000,0b00000,0b11110,0b00001,0b01110,0b00001,0b11110,0b00000},/*з*/{0b00100,0b00000,0b10001,0b10001,0b10001,0b10011,0b01101,0b00000},/*й*/{0b00000,0b00000,0b10001,0b10010,0b11100,0b10010,0b10001,0b00000},/*к*/{0b00000,0b00000,0b00111,0b01001,0b01001,0b01001,0b10001,0b00000},/*л*/{0b00000,0b00000,0b10001,0b11011,0b10101,0b10001,0b10001,0b00000},/*м*/{0b00000,0b00000,0b10001,0b10001,0b11111,0b10001,0b10001,0b00000},/*н*/{0b00000,0b00000,0b11111,0b10001,0b10001,0b10001,0b10001,0b00000},/*п*/{0b00010,0b00100,0b01110,0b10101,0b01110,0b00100,0b01000,0b00000},/*ф*/{0b00000,0b00000,0b10010,0b10010,0b10010,0b10010,0b11111,0b00001},/*ц*/{0b00000,0b00000,0b10001,0b10001,0b01111,0b00001,0b00001,0b00000},/*ч*/{0b00000,0b00000,0b10101,0b10101,0b10101,0b10101,0b11111,0b00000},/*ш*/{0b00000,0b00000,0b10101,0b10101,0b10101,0b10101,0b11111,0b00001},/*щ*/{0b00000,0b00000,0b11000,0b01000,0b01110,0b01001,0b01110,0b00000},/*ъ*/{0b00000,0b00000,0b10001,0b10001,0b11001,0b10101,0b11001,0b00000},/*ы*/{0b00000,0b00000,0b10000,0b10000,0b11110,0b10001,0b11110,0b00000},/*ь*/{0b00000,0b00000,0b01110,0b10001,0b00111,0b10001,0b01110,0b00000},/*э*/{0b00000,0b00000,0b10010,0b10101,0b11101,0b10101,0b10010,0b00000},/*ю*/ {0b00000,0b00000,0b01111,0b10001,0b01111,0b01001,0b10001,0b00000}/*я*/};
uint8_t commonCharacters[] = {192, 194, 197, 202, 204, 205, 206, 208, 209, 210, 211, 213, 224, 229, 232, 238, 240, 241, 242, 243, 245};
uint8_t onlyRussianCharacters[] = {193, 195, 196, 168, 198, 199, 200, 201, 203, 207, 212, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 225, 226, 227, 228, 184, 230, 231, 233, 234, 235, 236, 237, 239, 244, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};
#endif // RUSSIAN

uint8_t GetPortAddress(uint8_t c)
{
	switch(c)
	{
		case 'B':
		case 'b': return 0x05;
		case 'C':
		case 'c': return 0x08;
		case 'D':
		case 'd': return 0x0B;
		default: return 0;
	}
}

//Set pin numbers and ports using 4-bit data bus
void SetPinout4Bits(uint8_t data_port, uint8_t setting_port, uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	DATA_BUS = GetPortAddress(data_port);
	SETTING_BUS = GetPortAddress(setting_port);
	RS = rs;
	E = e;
	D4 = d4; D5 = d5; D6 = d6; D7 = d7;
	DL = 0;
	_SFR_IO8(SETTING_BUS - 1) |= (1 << RS) | (1 << E);
	_SFR_IO8(DATA_BUS - 1) |= (1 << D7) | (1 << D6) | (1 << D5) | (1 << D4);
}

//Set pin numbers and ports using 8-bit data bus
void SetPinout8Bits(uint8_t data_port, uint8_t setting_port, uint8_t rs, uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	DATA_BUS = GetPortAddress(data_port);
	SETTING_BUS = GetPortAddress(setting_port);
	RS = rs;
	E = e;
	D0 = d0; D1 = d1; D2 = d2; D3 = d3; D4 = d4; D5 = d5; D6 = d6; D7 = d7;
	DL = 1;
	_SFR_IO8(SETTING_BUS - 1) |= (1 << RS) | (1 << E);
	_SFR_IO8(DATA_BUS - 1) |= (1 << D7) | (1 << D6) | (1 << D5) | (1 << D4) | (1 << D3) | (1 << D2) | (1 << D1) | (1 << D0);
}

void SendNibble(uint8_t data, uint8_t rs)
{
	SET_BIT(_SFR_IO8(SETTING_BUS), RS, rs);
	SET_BIT(_SFR_IO8(DATA_BUS), D7, GET_BIT(data, D7));
	SET_BIT(_SFR_IO8(DATA_BUS), D6, GET_BIT(data, D6));
	SET_BIT(_SFR_IO8(DATA_BUS), D5, GET_BIT(data, D5));
	SET_BIT(_SFR_IO8(DATA_BUS), D4, GET_BIT(data, D4));

	SET_BIT(_SFR_IO8(SETTING_BUS), E, 1);
	SET_BIT(_SFR_IO8(SETTING_BUS), E, 0);
	_delay_us(DELAY0);
}

void SendByte(uint8_t data, uint8_t rs)
{
	if (DL == 0)
	{
		SendNibble(data, rs);
		SendNibble(data << 4, rs);
	}
	else
	{
		SET_BIT(_SFR_IO8(SETTING_BUS), RS, rs);
		SET_BIT(_SFR_IO8(DATA_BUS), D7, GET_BIT(data, D7));
		SET_BIT(_SFR_IO8(DATA_BUS), D6, GET_BIT(data, D6));
		SET_BIT(_SFR_IO8(DATA_BUS), D5, GET_BIT(data, D5));
		SET_BIT(_SFR_IO8(DATA_BUS), D4, GET_BIT(data, D4));
		SET_BIT(_SFR_IO8(DATA_BUS), D3, GET_BIT(data, D3));
		SET_BIT(_SFR_IO8(DATA_BUS), D2, GET_BIT(data, D2));
		SET_BIT(_SFR_IO8(DATA_BUS), D1, GET_BIT(data, D1));
		SET_BIT(_SFR_IO8(DATA_BUS), D0, GET_BIT(data, D0));

		SET_BIT(_SFR_IO8(SETTING_BUS), E, 1);
		SET_BIT(_SFR_IO8(SETTING_BUS), E, 0);
		_delay_us(DELAY0);
	}
}

//Clear all display data and reset AC(address counter)
void ClearDisplay()
{
	AC = 0;
	SendByte(0x1, 0);
	_delay_us(DELAY1);
}

//Reset AC(address counter). Return cursor to its original site
void ReturnHome()
{
	SendByte(0x2, 0);
	_delay_us(DELAY1);
}

//I_D - (1: cursor moves right and DDRAM address increased by 1, 1: cursor moves left and DDRAM address decreased by 1)
//SH - shifting enable
void EntryModeSet(uint8_t I_D, uint8_t SH)
{
	SendByte(0x4 | I_D << 1 | SH, 0);
}

//Display/Cursor/Blink == 1 then turn on else turn off
void Display_On_Off(uint8_t Display, uint8_t Cursor, uint8_t Blink)
{
	SendByte(0x8 | Display << 2 | Cursor << 1 | Blink, 0);
}

//S_C - (0: moves cursor, 1: moves all the display)
//R_L - (0: left, 1: right)
void CursourOrDisplayShift(uint8_t S_C, uint8_t R_L)
{
	SendByte(0x10 | S_C << 3 | R_L << 2, 0);
}

//DL - (0: 4 bits for data bus, 1: 8 bits for data bits)
//N - (0: 1 line, 1: 2 lines)
//F - (0: 5x8 character matrix, 1: 5x11 character matrix)
void FunctionSet(uint8_t DL, uint8_t N, uint8_t F)
{
	SendByte(0x20 | DL << 4 | N << 3 | F << 2, 0);
}

//Set CGRAM address to AC
void SetCGRAMAddress(uint8_t address)
{
	SendByte(0x40 | address, 0);
}

//Set DDRAM address to AC
void SetDDRAMAddress(uint8_t address)
{
	SendByte(0x80 | address, 0);
}

//Write binary 8-bit data to DDRAM/CGRAM
void WriteDataToRAM(uint8_t data)
{
	SendByte(data, 1);
}

/*-----Write character pattern to CGRAM-------------
Parameters:
pattern - array of bytes(In each byte 5 lower bits are significant)
address - number[0, 7].
*/
void CreatePattern(uint8_t * pattern, uint8_t address)
{
	SetCGRAMAddress(address << 3);

	for (uint8_t i = 0; i < 8; i++)
	{
		WriteDataToRAM(pattern[i]);
	}
}

/*-----Print custom pattern to display--------------
Parameters:
n - number of custom pattern.
NOTE: Set any DDRAM address before call this function.
*/
void PrintCustomPattern(uint8_t n)
{
	WriteDataToRAM(n);
}

/*-----Shift all display data left on 1 cell------*/
void ShiftLeft()
{
	CursourOrDisplayShift(1, 0);
}

/*-----Shift all display data right on 1 cell-----*/
void ShiftRight()
{
	CursourOrDisplayShift(1, 1);
}

/*-----Set position(row, column) for output---------
Parameters:
row - number[0, 1],
col - number[0, 39].
*/
void SetPosition(char row, char col)
{
	AC = 0x40 * row + col;
	SetDDRAMAddress(AC);
}

//Display Initialization
void InitLCD()
{
	if (DL == 0)
	{
		_delay_ms(15);
		SendNibble(0x30, 0);
		_delay_us(4100);
		SendNibble(0x30, 0);
		_delay_us(100);
		SendNibble(0x30, 0);
		SendNibble(0x20, 0);
		FunctionSet(0,1,0);
		Display_On_Off(0,0,0);
		ClearDisplay();
		EntryModeSet(1,0);
	}
	else
	{
		_delay_ms(15);
		FunctionSet(1,0,0);
		_delay_us(4100);
		FunctionSet(1,0,0);
		_delay_us(100);
		FunctionSet(1,0,0);
		FunctionSet(1,1,0);
		Display_On_Off(0,0,0);
		ClearDisplay();
		EntryModeSet(1,0);
	}

	//turning on display because by default he is turned off
	Display_On_Off(1,0,0);
}

int IndexOf(uint8_t * array, uint8_t item)
{
	for (int i = 0; array[i] != '\0'; i++)
	{
		if (item == array[i])
		{
			return i;
		}
	}
	return -1;
}

/*-----Print text to display------------------------
Parameters:
string - array of symbols.
NOTE: register AC shouldn't contain CGRAM address.
Set any DDRAM address before call this function.
*/
#ifdef RUSSIAN
void PrintText(char * string)
{
	for (uint8_t i = 0; string[i] != '\0'; i++)
	{
		char c = string[i];
		if ((c >= 192 && c <= 255) || c == 168 || c == 184)
		{
			int8_t enEquInd = IndexOf(commonCharacters, c);

			if (enEquInd != -1)
			{
				WriteDataToRAM("ABEKMHOPCTYXaeuopcmyx"[enEquInd]);
			}
			else
			{
				uint8_t r = IndexOf(onlyRussianCharacters, c);
				int8_t ind = IndexOf(CGRAM_Buffer, r);
				if (ind == -1)
				{
					ind  = buf_cntr;
					CreatePattern(RUSSIAN_PATTERNS[r], buf_cntr);
					CGRAM_Buffer[buf_cntr++] = r;
					SetDDRAMAddress(AC);
				}

				PrintCustomPattern(ind);
			}
		}
		else
		{
			WriteDataToRAM(c);
		}
		AC++;
	}
}
#else
void PrintText(char * string)
{
	for (uint8_t i = 0; string[i] != '\0'; i++)
	{
		WriteDataToRAM(string[i]);
	}
}
#endif // RUSSIAN