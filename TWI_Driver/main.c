/*
 * main.c
 *
 *  Created on: May 31, 2022
 *      Author: Ahmed Hany
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "GIE_Interface.h"
#include "LCD_Interface.h"
#include "TWI_int.h"
#include "UART_int.h"
#include <util/delay.h>
#define size	255
#define KEY		'H'
#define DEL		'~'
#define DUM		'D'


void EEPROM_vWriteByte(u8 A_u8Byte, u16 A_u16Address)
{
	u8 L_u8Add = 0b01010000;
	u8 L_u8Mask = (A_u16Address & 0x300) >> 8;
	L_u8Add |= L_u8Mask;

	MTWI_u8SendStartCondition();
	MTWI_u8SendSlaveAddressRW(L_u8Add,TWI_WRITE);
	MTWI_u8SendByte((u8)A_u16Address);
	MTWI_u8SendByte(A_u8Byte);
	MTWI_u8SendStopCondition();
}

void EEPROM_vWriteString(char A_pu8Str[], u16 A_u16Address)
{
	u8* L_str = (u8*)A_pu8Str;
	u16 L_u16Addcounter = A_u16Address;
	while(*L_str != '\0')
	{
		EEPROM_vWriteByte(*L_str,L_u16Addcounter);
		_delay_ms(50);
		L_str++;
		L_u16Addcounter++;
	}
	EEPROM_vWriteByte(DEL,L_u16Addcounter);
	L_u16Addcounter++;
	_delay_ms(50);
	EEPROM_vWriteByte(DUM,L_u16Addcounter);

}

u8 EEPROM_u8ReadByte(u16 A_u16Address)
{
	u8 L_u8Add = 0b01010000;
	u8 L_u8Mask = (A_u16Address & 0x300) >> 8;
	L_u8Add |= L_u8Mask;


	u8* local_u8Byte;
	MTWI_u8SendStartCondition();
	MTWI_u8SendSlaveAddressRW(L_u8Add,TWI_WRITE);
	MTWI_u8SendByte((u8)A_u16Address);
	MTWI_u8SendRepeatedStartCondition();
	MTWI_u8SendSlaveAddressRW(L_u8Add,TWI_READ);
	MTWI_u8ReceiveByte(local_u8Byte,TWI_NOT_ACK);
	MTWI_u8SendStopCondition();

	return *local_u8Byte;
}


int main(void)
{
	MUART_vInit();
	MTWI_vInit();
	u8 L_choice = EEPROM_u8ReadByte(0);
	//MUART_vTransmit(L_choice);

	if(L_choice == KEY)
	{
		MUART_vSendString("The message is :\r\r");
		u8* x;
		MTWI_u8SendStartCondition();
		MTWI_u8SendSlaveAddressRW(0b01010000,TWI_WRITE);
		MTWI_u8SendByte(1);
		MTWI_u8SendRepeatedStartCondition();
		MTWI_u8SendSlaveAddressRW(0b01010000,TWI_READ);
		MTWI_u8ReceiveByte(x,TWI_ACK);
		while(*x != DEL)
		{
			MUART_vTransmit(*x);
			MTWI_u8ReceiveByte(x,TWI_ACK);
		}
		MTWI_u8ReceiveByte(x,TWI_NOT_ACK);
		MTWI_u8SendStopCondition();
	}
	else
	{
		char mess[size];
		MUART_vSendString("Write Your Message To the World\r\r");
		MUART_vSendString("This Message will Be opened After 99 Years\r\r");
		MUART_vSendString("->");
		MUART_vReceiveString(mess,size);
		MUART_vSendString("\r\r");
		MUART_vSendString("The Message saved is \r\r");
		MUART_vSendString(mess);
		MUART_vSendString("\r\r");

		EEPROM_vWriteByte(KEY,0);
		EEPROM_vWriteString(mess,1);

	}
	while(1)
	{

	}
	return 0;
}





