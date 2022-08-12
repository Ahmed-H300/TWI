/*
 * GIE_Program.c
 *
 *  Created on: Jun 2, 2022
 *      Author: abdelrahmanhossam
 */



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define GIE_SREG_REG    *((volatile u8 *) 0X5F)


void MGIE_voidEnable(void)
{
	SET_BIT(GIE_SREG_REG,7);
}
void MGIE_voidDisable(void)
{
	CLR_BIT(GIE_SREG_REG,7);
}
