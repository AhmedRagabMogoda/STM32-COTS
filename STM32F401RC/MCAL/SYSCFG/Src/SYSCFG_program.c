/*
 * SYSCFG_program.c
 *
 *  Created on: Dec 3, 2024
 *      Author: Ahmed Ragab
 */
#include "stm32f401xx.h"
#include "SYSCFG_private.h"
#include "SYSCFG_interface.h"

void SYSCFG_VoidSetEXTIPort(SYSCFG_Port_t Port,SYSCFG_Pin_t PinNum)
{
	uint8_t RegNum = PinNum / SYSCFG_PIN_SHIFTING;
	uint8_t BitNum = PinNum % SYSCFG_PIN_SHIFTING;
	SYSCFG->EXTICR[RegNum] &= ~(SYSCFG_MASK << (BitNum*SYSCFG_PIN_ACCESS));
	SYSCFG->EXTICR[RegNum] |= (Port << (BitNum*SYSCFG_PIN_ACCESS));
}
