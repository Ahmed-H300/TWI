/*******************************************************************************************
* ! Author : Ahmed Hany Farouk
* ! Title : Led Animation Program
* ! File Name : main.c
* ! Description : This file has the implementation code for switching on led
* ! Version : V1.0
********************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "LCD_Interface.h"
#include <util/delay.h>


void HLCD_voidSendCommand(u8 A_u8Cmd)
{
	/* Control RS and RW Pins */
	MDIO_voidSetPinValue(CONTROL_PORT,PIN0,LOW);
	MDIO_voidSetPinValue(CONTROL_PORT,PIN1,LOW);

	/* Write Command on the data pins */
	MDIO_voidSetPortValue(DATA_PORT,A_u8Cmd);

	/* Pulse on the enable pin */
	MDIO_voidSetPinValue(CONTROL_PORT,PIN2,HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue(CONTROL_PORT,PIN2,LOW);
	_delay_ms(1);
}

void HLCD_voidSendData(u8 A_u8Data)
{
	/* Control RS and RW Pins */
	MDIO_voidSetPinValue(CONTROL_PORT,PIN0,HIGH);
	MDIO_voidSetPinValue(CONTROL_PORT,PIN1,LOW);

	/* Write Command on the data pins */
	MDIO_voidSetPortValue(DATA_PORT,A_u8Data);

	/* Pulse on the enable pin */
	MDIO_voidSetPinValue(CONTROL_PORT,PIN2,HIGH);
	_delay_ms(1);
	MDIO_voidSetPinValue(CONTROL_PORT,PIN2,LOW);
	_delay_ms(1);
}

#define FINCTION_SET 	0b00111100
#define DISPLAY_CONTROL 0b00001111
#define DISPLAY_CONTROL2 0b00001100
#define DISPLAY_CLEAR 	0b00000001
#define ENTRY_MODE 		0b00000110

void HLCD_voidInit(void)
{
	// wait for more than 30ms
	_delay_ms(35);

	//Function Set 0b00111100
	HLCD_voidSendCommand(FINCTION_SET);

	// wait for more than 39 us
	_delay_ms(1);

	// Display on/off Control 0b00001111
	HLCD_voidSendCommand(DISPLAY_CONTROL);

	// wait for more than 39 us
	_delay_ms(1);

	// Display CLEAR 0b00001111
	HLCD_voidSendCommand(DISPLAY_CLEAR);

	// wait for more than 1.53 Ms
	_delay_ms(2);

	// ENTRY MODE SET
	HLCD_voidSendCommand(ENTRY_MODE);
}


void HLCD_voidInitNoCursor(void)
{
	// wait for more than 30ms
	_delay_ms(35);

	//Function Set 0b00111100
	HLCD_voidSendCommand(FINCTION_SET);

	// wait for more than 39 us
	_delay_ms(1);

	// Display on/off Control 0b00001100
	HLCD_voidSendCommand(DISPLAY_CONTROL2);

	// wait for more than 39 us
	_delay_ms(1);

	// Display CLEAR 0b00001111
	HLCD_voidSendCommand(DISPLAY_CLEAR);

	// wait for more than 1.53 Ms
	_delay_ms(2);

	// ENTRY MODE SET
	HLCD_voidSendCommand(ENTRY_MODE);
}

void HLCD_voidSendString(u8 *A_u8PtrString)
{
	while(*A_u8PtrString > 0) // Check end of String
	{
		//Send Char then Move Pointer to next Char
		HLCD_voidSendData(*A_u8PtrString++);
	}
}

#define LCD_ROW_1 127
#define LCD_ROW_2 191

void HLCD_voidGoToPosition(u8 A_u8RowNum, u8 A_u8ColNum)
{
	switch (A_u8RowNum)
	{
	case LCD_LINE_1: HLCD_voidSendCommand(LCD_ROW_1+A_u8ColNum); break;
	case LCD_LINE_2: HLCD_voidSendCommand(LCD_ROW_2+A_u8ColNum); break;
	}

	//wait for more than 39 us
	_delay_ms(1);
}


#define MAX_IDX_OF_ROWS 1
// make MAX_IDX_OF_COL 39 not 15 to include invisible range
#define MAX_IDX_OF_COL 15

#define FIRST_ROW_IDX 0

#define FIRST_ROW_START 0x00
#define SEC_ROW_START 0x40

#define SET_AC_MASK 0x80

void HLCD_voidGoToPosition_Assaf(u8 A_u8RowNum, u8 A_u8ColNum)
{
	u8 L_u8DdramAddress;
	u8 L_u8Command;

	//Data validation   /* Valid Range*/
	if	((A_u8RowNum <= MAX_IDX_OF_ROWS) && (A_u8ColNum <= MAX_IDX_OF_COL))
	{

		if	(A_u8RowNum == FIRST_ROW_IDX)
		{
			L_u8DdramAddress = FIRST_ROW_START + A_u8ColNum;
		}
		else
		{
			L_u8DdramAddress = SEC_ROW_START + A_u8ColNum;
		}
		L_u8Command = L_u8DdramAddress | SET_AC_MASK;

		HLCD_voidSendCommand(L_u8Command);

	}
	else
	{
		/* Do Nothing
		 *
		 *  till now
		 *
		 *	later you will do logging as switching led or do something
		 *
		 * */
	}

}



void HLCD_voidDisplayNumber(s32 A_s32Number)
{
	u32 local_u32Number = 1;
	if (A_s32Number == 0)
	{
		HLCD_voidSendData('0');
	}
	if (A_s32Number < 0)
	{
		HLCD_voidSendData('-');
		A_s32Number *= -1;
	}
	while (A_s32Number != 0)
	{
		local_u32Number = ((local_u32Number * 10) + (A_s32Number % 10));
		A_s32Number /= 10;
	}

	while (local_u32Number != 1)
	{
		HLCD_voidSendData((local_u32Number % 10) + 48);
		local_u32Number /= 10;
	}
}


void HLCD_voidWriteCustomCh (u8 A_u8PatternIdx, u8 *A_u8PatternValue)
{
	u8 L_u8LoopIterator;

	/*  Step 1: Set AC on CGRAM */
	switch (A_u8PatternIdx)
	{
		case 0 : HLCD_voidSendCommand(0x40); break;
		case 1 : HLCD_voidSendCommand(0x48); break;
		case 2 : HLCD_voidSendCommand(0x50); break;
		case 3 : HLCD_voidSendCommand(0x58); break;
		case 4 : HLCD_voidSendCommand(0x60); break;
		case 5 : HLCD_voidSendCommand(0x68); break;
		case 6 : HLCD_voidSendCommand(0x70); break;
		case 7 : HLCD_voidSendCommand(0x78); break;
	//	default : /* Report ERROR */     ; break;
	}
	/*  Step 2: Write Pattern 	*/
	for	(L_u8LoopIterator = 0; L_u8LoopIterator < 8; L_u8LoopIterator++)
	{
		HLCD_voidSendData(A_u8PatternValue[L_u8LoopIterator]);
	}
}




