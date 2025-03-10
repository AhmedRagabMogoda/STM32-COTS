/*
 *  EXTI_program.c
 *
 *  Created on: Dec 3, 2024
 *  Author: Ahmed Ragab
 */

#include "stm32f401xx.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"
#include "ErrorState.h"

/**
 * @brief Array of callback functions for each EXTI line.
 *        Initialized to NULL to store user-defined ISR functions.
**/
static void (*EXIT_CallBackFunc[EXTI_LINE_NUM])(void)={NULL};


uint8_t EXTI_u8Init(EXTI_Config_t* CopyConfig)
{
	uint8_t Local_u8ErrorState=OK;
	if(CopyConfig!=NULL)
	{
		switch(CopyConfig->TrigSrc)
		{
		case FALLING_TRIG :
			EXTI->FTSR |= (FTSR_MASK << CopyConfig->PinNum);
			EXTI->RTSR &= ~(RTSR_MASK << CopyConfig->PinNum);
			break;
		case RISING_TRIG :
			EXTI->RTSR |= (RTSR_MASK << CopyConfig->PinNum);
			EXTI->FTSR &= ~(FTSR_MASK << CopyConfig->PinNum);
			break;
		case FALLING_RISING_TRIG :
			EXTI->FTSR |= (FTSR_MASK << CopyConfig->PinNum);
			EXTI->RTSR |= (RTSR_MASK << CopyConfig->PinNum);
			break;
		default :
			Local_u8ErrorState=NOT_OK;
			break;
		}

		if(CopyConfig->InitState==EXTI_ENABLE)
		{
			EXTI->IMR |= (IMR_MASK << CopyConfig->PinNum);
		}
		else if(CopyConfig->InitState==EXTI_DISABLE)
		{
			EXTI->IMR &= ~(IMR_MASK << CopyConfig->PinNum);
		}
		else
		{
			Local_u8ErrorState=NOT_OK;
		}

		if(CopyConfig->CallBackFunc!=NULL)
		{
			EXIT_CallBackFunc[CopyConfig->PinNum] = CopyConfig->CallBackFunc;
		}
		else
		{
				Local_u8ErrorState=NULL_PTR_ERR;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t EXTI_u8SetTrigSrc(EXTI_TrigSrc_t TrigSrc,EXTI_LineNum_t PinNum)
{
	uint8_t Local_u8ErrorState=OK;
	switch(TrigSrc)
	{
		case FALLING_TRIG :
			EXTI->FTSR |= (FTSR_MASK << PinNum);
			EXTI->RTSR &= ~(RTSR_MASK << PinNum);
			break;
		case RISING_TRIG :
			EXTI->RTSR |= (RTSR_MASK << PinNum);
			EXTI->FTSR &= ~(FTSR_MASK << PinNum);
			break;
		case FALLING_RISING_TRIG :
			EXTI->FTSR |= (FTSR_MASK << PinNum);
			EXTI->RTSR |= (RTSR_MASK << PinNum);
			break;
		default :
			Local_u8ErrorState=NOT_OK;
			break;
	}
	return Local_u8ErrorState;
}

void EXTI_voidEnableInit(EXTI_InitState_t InitState,EXTI_LineNum_t PinNum)
{
	EXTI->IMR |= (IMR_MASK << PinNum);
}

void EXTI_voidDisableInit(EXTI_InitState_t InitState,EXTI_LineNum_t PinNum)
{
	EXTI->IMR &= ~(IMR_MASK << PinNum);
}

void EXTI_voidClearPandingFlag(EXTI_LineNum_t PinNum)
{
	EXTI->PR = (PR_MASK << PinNum);
}

uint8_t EXTI_8uGetPandingFlag(EXTI_LineNum_t PinNum,uint8_t* CopyFlagState)
{
	uint8_t Local_u8ErrorState=OK;
	if(CopyFlagState!=NULL)
	{
		*CopyFlagState = ((EXTI->PR >> PinNum) & PR_MASK);
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
