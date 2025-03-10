/*
 *  NVIC_program.c
 *
 *  Created on: Nov 30, 2024
 *  Author: Ahmed Ragab
 */
#include "stm32f401xx.h"
#include "NVIC_private.h"
#include "NVIC_interface.h"

void NVIC_EnableInterrupt(Interrupt_t InterruptNum)
{
	uint8_t RegNum = (InterruptNum / PIN_SHIFTING);
	uint8_t BitNum = (InterruptNum % PIN_SHIFTING);
	NVIC->ISER[RegNum] = (ISER_MASK << BitNum);
}

void NVIC_DisableInterrupt(Interrupt_t InterruptNum)
{
	uint8_t RegNum = (InterruptNum / PIN_SHIFTING);
	uint8_t BitNum = (InterruptNum % PIN_SHIFTING);
	NVIC->ICER[RegNum] = (ICER_MASK << BitNum);
}

void NVIC_SETPendingInterrupt(Interrupt_t InterruptNum)
{
	uint8_t RegNum = (InterruptNum / PIN_SHIFTING);
	uint8_t BitNum = (InterruptNum % PIN_SHIFTING);
	NVIC->ISPR[RegNum] = (ISPR_MASK << BitNum);
}

void NVIC_CLRPendingInterrupt(Interrupt_t InterruptNum)
{
	uint8_t RegNum = (InterruptNum / PIN_SHIFTING);
	uint8_t BitNum = (InterruptNum % PIN_SHIFTING);
	NVIC->ICPR[RegNum] = (ICPR_MASK << BitNum);
}

uint8_t NVIC_GetActiveFlagInterrupt(Interrupt_t InterruptNum)
{
	uint8_t RegNum = (InterruptNum / PIN_SHIFTING);
	uint8_t BitNum = (InterruptNum % PIN_SHIFTING);
	uint8_t RetVal = ((NVIC->IABR[RegNum] >> BitNum) & IABR_MASK);
	return RetVal;
}

void NVIC_SETPriorityInterrupt(Interrupt_t InterruptNum,Priority_t Priority)
{
	NVIC->IPR[InterruptNum] = (Priority << IPR_PIN_ACCESS);
}


