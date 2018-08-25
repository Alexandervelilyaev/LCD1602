/*
 * lm016l.h
 *
 * Created: 17.08.2018
 * Author: Alexander Velilyaev
 * Contact: Alexandervelilyaev@gmail.com
 *
 * This library encapsulates most necessary 
 * functions(according to datasheet) for working with display
 */ 

#define F_CPU 8000000UL //8Mhz - frequency of CPU

#ifndef LM016L_H_
#define LM016L_H_

//Set pin numbers and ports using 4-bit data bus
void SetPinout4Bits(unsigned char data_port, unsigned char setting_port, unsigned char rs, unsigned char e, unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7);

//Set pin numbers and ports using 8-bit data bus
void SetPinout8Bits(unsigned char data_port, unsigned char setting_port, unsigned char rs, unsigned char e, unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7);

//Clear all display data and reset AC(address counter)
void ClearDisplay();

//Reset AC(address counter). Return cursor to its original site
void ReturnHome();

//I_D - (1: cursor moves right and DDRAM address increased by 1, 1: cursor moves left and DDRAM address decreased by 1)
//SH - shifting enable
void EntryModeSet(unsigned char I_D, unsigned char SH);

//Display/Cursor/Blink == 1 then turn on else turn off
void Display_On_Off(unsigned char Display, unsigned char Cursor, unsigned char Blink);

//S_C - (0: moves cursor, 1: moves all the display)
//R_L - (0: left, 1: right)
void CursourOrDisplayShift(unsigned char S_C, unsigned char R_L);

//Set CGRAM address to AC
void SetCGRAMAddress(unsigned char address);

//Set DDRAM address to AC
void SetDDRAMAddress(unsigned char address);

//Write binary 8-bit data to DDRAM/CGRAM
void WriteDataToRAM(unsigned char data);

//Display Initialization
void InitLCD();

#endif /* LM016L_H_ */