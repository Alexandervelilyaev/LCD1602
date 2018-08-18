#include <avr/io.h>
#include <util/delay.h>

#ifndef LM016L_H_
#define LM016L_H_

void SetPinout(unsigned char data_port, unsigned char setting_port, unsigned char rs, unsigned char e, unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4, unsigned char d5, unsigned char d6, unsigned char d7);

void ClearDisplay();

void ReturnHome();

//I_D - (1: cursor moves right and DDRAM address increased by 1, 1: cursor moves left and DDRAM address decreased by 1)
//SH - shifting enable
void EntryModeSet(unsigned char I_D, unsigned char SH);

//Display/Cursor/Blink == 1 then turn on else turn off
void Display_On_Off(unsigned char Display, unsigned char Cursor, unsigned char Blink);

//S_C - (0: moves cursor, 1: moves all the display)
//R_L - (0: left, 1: right)
void CursourOrDisplayShift(unsigned char S_C, unsigned char R_L);

void SetCGRAMAddress(unsigned char address);
void SetDDRAMAddress(unsigned char address);
void WriteDataToRAM(unsigned char data);
void InitLCD();

#endif /* LM016L_H_ */