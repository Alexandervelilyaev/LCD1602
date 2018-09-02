/*
* lcd1602_base.h
*
* Created: 17.08.2018
* Author: Alexander Velilyaev
* Contact: Alexandervelilyaev@gmail.com
*
* This library encapsulates most necessary
* functions(according to datasheet) for working with display
*/

#ifndef LCD1602_BASE_H_
#define LCD1602_BASE_H_

#define F_CPU 8000000UL //8Mhz - frequency of CPU
#include <avr/io.h>
#include <util/delay.h>

//Set pin numbers and ports using 4-bit data bus
void SetPinout4Bits(uint8_t data_port, uint8_t setting_port, uint8_t rs, uint8_t e, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

//Set pin numbers and ports using 8-bit data bus
void SetPinout8Bits(uint8_t data_port, uint8_t setting_port, uint8_t rs, uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

//Clear all display data and reset AC(address counter)
void ClearDisplay();

//Reset AC(address counter). Return cursor to its original site
void ReturnHome();

//I_D - (1: cursor moves right and DDRAM address increased by 1, 1: cursor moves left and DDRAM address decreased by 1)
//SH - shifting enable
void EntryModeSet(uint8_t I_D, uint8_t SH);

//Display/Cursor/Blink == 1 then turn on else turn off
void Display_On_Off(uint8_t Display, uint8_t Cursor, uint8_t Blink);

//S_C - (0: moves cursor, 1: moves all the display)
//R_L - (0: left, 1: right)
void CursourOrDisplayShift(uint8_t S_C, uint8_t R_L);

//Set CGRAM address to AC
void SetCGRAMAddress(uint8_t address);

//Set DDRAM address to AC
void SetDDRAMAddress(uint8_t address);

//Write binary 8-bit data to DDRAM/CGRAM
void WriteDataToRAM(uint8_t data);

//Display Initialization
void InitLCD();

#endif /* LCD1602_BASE_H_ */