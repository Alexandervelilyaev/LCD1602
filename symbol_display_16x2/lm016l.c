﻿#include <avr/io.h>
#include "access_to_bits.h"
#include "lm016l.h"

#define DELAY0 38
#define DELAY1 1520

unsigned char DATA_BUS, SETTING_BUS, RS, E, D0, D1, D2, D3, D4,D5, D6, D7;

unsigned char GetPortAddress(unsigned char c)
{
	switch(c)
	{
		case 'B':
		case 'b': return 0x05;
		case 'C':
		case 'c': return 0x08;
		case 'D':
		case  'd': return 0x0B;
		default: return 0;
	}
}

void SetPinout(unsigned char data_port, unsigned char setting_port, unsigned char rs, unsigned char e, unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7)
{
	DATA_BUS = GetPortAddress(data_port);
	SETTING_BUS = GetPortAddress(setting_port);
	RS = rs;
	E = e;
	D0 = d0;
	D1 = d1;
	D2 = d2;
	D3 = d3;
	D4 = d4;
	D5 = d5;
	D6 = d6;
	D7 = d7;

	_SFR_IO8(SETTING_BUS - 1) |= (1 << RS) | (1 << E);
	_SFR_IO8(DATA_BUS - 1) |= (1 << D7) | (1 << D6) | (1 << D5) | (1 << D4) | (1 << D3) | (1 << D2) | (1 << D1) | (1 << D0);
}

void SendNibble(unsigned char data, unsigned char rs)
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

void SendByte(unsigned char data, unsigned char rs)
{
	SendNibble(data, rs);
	SendNibble(data << 4, rs);
}

void ClearDisplay()
{
	SendByte(0x1, 0);
	_delay_us(DELAY1);
}

void ReturnHome()
{
	SendByte(0x2, 0);
	_delay_us(DELAY1);
}

//I_D - (1: cursor moves right and DDRAM address increased by 1, 1: cursor moves left and DDRAM address decreased by 1)
//SH - shifting enable
void EntryModeSet(unsigned char I_D, unsigned char SH)
{
	SendByte(0x4 | I_D << 1 | SH, 0);
}

//Display/Cursor/Blink == 1 then turn on else turn off
void Display_On_Off(unsigned char Display, unsigned char Cursor, unsigned char Blink)
{
	SendByte(0x8 | Display << 2 | Cursor << 1 | Blink, 0);
}

//S_C - (0: moves cursor, 1: moves all the display)
//R_L - (0: left, 1: right)
void CursourOrDisplayShift(unsigned char S_C, unsigned char R_L)
{
	SendByte(0x10 | S_C << 3 | R_L << 2, 0);
}

//DL - (0: 4 bits for data bus, 1: 8 bits for data bits)
//N - (0: 1 line, 1: 2 lines)
//F - (0: 5x8 character matrix, 1: 5x11 character matrix)
void FunctionSet(unsigned char DL, unsigned char N, unsigned char F)
{
	SendByte(0x20 | DL << 4 | N << 3 | F << 2, 0);
}

void SetCGRAMAddress(unsigned char address)
{
	SendByte(0x40 | address, 0);
}

void SetDDRAMAddress(unsigned char address)
{
	SendByte(0x80 | address, 0);
}

void WriteDataToRAM(unsigned char data)
{
	SendByte(data, 1);
}

void InitLCD()
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