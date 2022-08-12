/*
 * TWI_prg.c
 *
 *  Created on: Aug 9, 2022
 *      Author: Ahmed Hany
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"



#include "TWI_int.h"
#include "TWI_prv.h"
#include "TWI_cfg.h"



void MTWI_vInit(void)
{
	/*  Interrupt enable or disable*/
	CLR_BIT(TWCR, TWIE);
	/*  bit rate */
	TWBR = 10;
}

u8 MTWI_u8SendStartCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)))
	;

	/* check status code  */

	return (TWSR & 0xF8);
}

u8 MTWI_u8SendRepeatedStartCondition(void)
{
	// same as above for documentaion porpose

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)))
	;

	/* check status code  */

	return (TWSR & 0xF8);
}

u8 MTWI_u8SendSlaveAddressRW(u8 A_u8Sla, u8 A_u8RW)
{
	TWDR = (A_u8Sla<< 1) | (A_u8RW);
	TWCR = (1<<TWINT) | (1<<TWEN);	// it starts the sending
	CLR_BIT(TWCR, TWSTA);

	while (!(TWCR & (1<<TWINT)))
	;

	/* check status code  */

	return (TWSR & 0xF8);
}

u8 MTWI_u8SendByte(u8 A_u8Byte)
{
	TWDR = A_u8Byte;
	TWCR = (1<<TWINT) | (1<<TWEN);	// it starts the sending
	CLR_BIT(TWCR, TWSTA);

	while (!(TWCR & (1<<TWINT)))
	;

	/* check status code  */

	return (TWSR & 0xF8);
}

u8 MTWI_u8ReceiveByte(u8* A_pu8Byte, u8 A_u8Ack)
{
	switch(A_u8Ack)
	{
	case TWI_ACK:
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
		break;
	case TWI_NOT_ACK:
		TWCR = (1<<TWINT)|(1<<TWEN);
		CLR_BIT(TWCR,TWEA);
		break;
	}

	while (!(TWCR & (1<<TWINT)))
	;

	*A_pu8Byte = TWDR;

	/* check status code  */
	return (TWSR & 0xF8);
}

u8 MTWI_u8SendStopCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	/* check status code  */
	return (TWSR & 0xF8);
}

u8 MTWI_u8GetStatus(void)
{
	return (TWSR & 0xF8);
}












