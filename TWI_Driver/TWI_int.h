/*
 * TWI_int.h
 *
 *  Created on: Aug 9, 2022
 *      Author: Ahmed Hany
 */

#ifndef TWI_INT_H_
#define TWI_INT_H_


#define TWI_WRITE	0
#define TWI_READ	1


#define TWI_ACK			1
#define TWI_NOT_ACK		0

void MTWI_vInit(void);

u8 MTWI_u8SendStartCondition(void);

u8 MTWI_u8SendRepeatedStartCondition(void);

u8 MTWI_u8SendSlaveAddressRW(u8 A_u8Sla, u8 A_u8RW);

u8 MTWI_u8SendByte(u8 A_u8Byte);

u8 MTWI_u8ReceiveByte(u8* A_pu8Byte, u8 A_u8Ack);

u8 MTWI_u8SendStopCondition(void);

u8 MTWI_u8GetStatus(void);

// 100k --- 400k
void MTWI_vSetBitRate(u32 A_u32BitRate);

void MTWI_vSetSlaveAddress(u8 A_u8Ownsla); // could be replaced by a MICRO

#endif /* TWI_INT_H_ */
