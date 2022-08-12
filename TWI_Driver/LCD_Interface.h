/*
 * LCD_Interface.h
 *
 *  Created on: May 19, 2022
 *      Author: Ahmed Hany
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


#define DISPLAY_CLEAR 	0b00000001

#define DATA_PORT PORTD
#define CONTROL_PORT PORTC

#define LCD_LINE_1 1
#define LCD_LINE_2 2

void HLCD_voidSendCommand(u8 A_u8Cmd);
void HLCD_voidSendData(u8 A_u8Data);
void HLCD_voidInit(void);
void HLCD_voidInitNoCursor(void);
void HLCD_voidSendString(u8 *A_u8PtrString);
void HLCD_voidGoToPosition(u8 A_u8RowNum, u8 A_u8ColNum);
void HLCD_voidGoToPosition_Assaf(u8 A_u8RowNum, u8 A_u8ColNum);
void HLCD_voidWriteCustomCh (u8 A_u8PatternIdx, u8 *A_u8PatternValue);
void HLCD_voidDisplayNumber(s32 A_s32Number);
#endif /* LCD_INTERFACE_H_ */
