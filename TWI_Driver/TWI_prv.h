/*
 * TWI_prv.h
 *
 *  Created on: Aug 9, 2022
 *      Author: Ahmed Hany
 */

#ifndef TWI_PRV_H_
#define TWI_PRV_H_


#define TWIE		0
#define TWINT		7
#define TWSTA		5
#define TWEN		2
#define TWSTO		4
#define TWEA		6

#define TWBR		*((volatile u8*)(0x20))
#define TWCR		*((volatile u8*)(0x56))
#define TWSR		*((volatile u8*)(0x21))
#define TWDR		*((volatile u8*)(0x23))
#define TWAR		*((volatile u8*)(0x22))

#endif /* TWI_PRV_H_ */
