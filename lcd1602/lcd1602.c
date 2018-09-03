#include "lcd1602.h"

#define DELAY0 38
#define DELAY1 1520
#define SET_BIT(PORT, POS, VALUE) PORT = (PORT & ~(1 << POS)) | (VALUE << POS)
#define GET_BIT(PORT, POS) (PORT & (1 << POS)) >> POS

uint8_t DATA_BUS, SETTING_BUS;
uint8_t RS, E, D0, D1, D2, D3, D4,D5, D6, D7;
uint8_t DL;//Data Length: (1 - 8 bit DATA_BUS, 0 - 4 bit DATA_BUS)

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