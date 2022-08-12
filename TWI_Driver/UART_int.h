/*
 * UART_int.h
 *
 *  Created on: Jul 28, 2022
 *      Author: Ahmed Hany
 */

#ifndef UART_INT_H_
#define UART_INT_H_

void MUART_vInit(void);
void MUART_vTransmit(u8 A_u8Byte);
u8 MUART_u8Recieve(void);

void MUART_vSendString(char* str);
void MUART_vReceiveString(char str[], u32 size);


void MUART_vSetBaudRate(u32 A_u32BaudRate);

#endif /* UART_INT_H_ */
