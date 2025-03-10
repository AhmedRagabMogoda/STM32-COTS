/**
 * @file   : GPIO_program.c
 * @author : Ahmed Ragab Mogoda
 * @date   : Nov 25, 2024
 * @brief  : This file contains the implementation of GPIO driver functions for STM32F401xx microcontroller.
 *          It provides APIs for configuring GPIO pins, setting their values, toggling states, and reading pin values.
 **/

/*************************  Includes *************************************/
#include "stm32f401xx.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "ErrorState.h"

/************************* Global Variable********************************/
/* Array of pointers to GPIO peripheral base addresses */
static GPIO_RegDef_t* GPIOPort[GPIO_PERIPHERAL_NUM]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,RESERVED,RESERVED,GPIOH};


/************************  Implementation Function  **********************/

uint8_t GPIO_U8PinInit(const GPIO_PinConfig_t * PinConfig)
{
	uint8_t Local_u8ErrorState=OK;
	if (PinConfig != NULL)
	{
		if((PinConfig->Port <= PORTH) && (PinConfig->PinNum <= PIN15))
		{
			/* Configure GPIO Mode */
			GPIOPort[PinConfig->Port]->MODER &= ~(MODER_MASK << ((PinConfig->PinNum)*MODER_PIN_ACCESS));
			GPIOPort[PinConfig->Port]->MODER |= (PinConfig->Mode << ((PinConfig->PinNum)*MODER_PIN_ACCESS));
			/* Configure Pull-up/Pull-down Resistor */
			GPIOPort[PinConfig->Port]->PUPDR &= ~(PUPDR_MASK << ((PinConfig->PinNum)*PUPDR_PIN_ACCESS));
			GPIOPort[PinConfig->Port]->PUPDR |= (PinConfig->PullType << ((PinConfig->PinNum)*PUPDR_PIN_ACCESS));
			/* if the pin is OUTPUT or ALTERNATE_FUNCTION, configure additional settings */
			if((PinConfig->Mode == OUTPUT) || (PinConfig->Mode == ALTERNATE_FUNCTION))
			{
				/* Configure Output Type Pin Push Pull UP Or Open Drain */
				GPIOPort[PinConfig->Port]->OTYPER &= ~(OTYPER_MASK << (PinConfig->PinNum));
				GPIOPort[PinConfig->Port]->OTYPER |= (PinConfig->OutputType << (PinConfig->PinNum));
				/* Configure Output Speed */
				GPIOPort[PinConfig->Port]->OSPEEDR &= ~(OSPEEDR_MASK << ((PinConfig->PinNum)*OSPEEDR_PIN_ACCESS));
				GPIOPort[PinConfig->Port]->OSPEEDR |= (PinConfig->Speed << ((PinConfig->PinNum)*OSPEEDR_PIN_ACCESS));
				/* Configure Alternate Function if required */
				if (PinConfig->Mode == ALTERNATE_FUNCTION)
				{
					uint8_t Local_u8RegNum = (PinConfig->PinNum / AFR_PIN_SHIFTING);
					uint8_t Local_u8BitNum = (PinConfig->PinNum % AFR_PIN_SHIFTING);
					GPIOPort[PinConfig->Port]->AFR[Local_u8RegNum] &= ~(AFR_MASK << (Local_u8BitNum*AFR_PIN_ACCESS));
					GPIOPort[PinConfig->Port]->AFR[Local_u8RegNum] |= (PinConfig->AltFunc << (Local_u8BitNum*AFR_PIN_ACCESS));
				}
			}
		}
		else
		{
			Local_u8ErrorState=NOT_OK;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t GPIO_U8SetPinVal(Port_t Port,Pin_t PinNum,PinVal_t PinVal)
{
	uint8_t Local_u8ErrorState=OK;
	if((Port <= PORTH) && (PinNum <= PIN15))
	{
		if(PinVal==LOW)
		{
			GPIOPort[Port]->ODR &= ~(ODR_MASK << PinNum);
			/*GPIOPort[Port]->BSRR |= (BSRR_MASK << (BSRR_PIN_ACCESS+PinNum)); */
		}
		else if(PinVal==HIGH)
		{
			GPIOPort[Port]->ODR |= (ODR_MASK << PinNum);
			/*GPIOPort[Port]->BSRR |= (BSRR_MASK << (PinNum)); */
		}
		else
		{
			Local_u8ErrorState=NOT_OK;
		}
	}
	else
	{
		Local_u8ErrorState=NOT_OK;
	}
	return Local_u8ErrorState;
}



uint8_t GPIO_U8TogglePinVal(Port_t Port,Pin_t PinNum)
{
	uint8_t Local_u8ErrorState=OK;
	if((Port <= PORTH) && (PinNum <= PIN15))
	{
		GPIOPort[Port]->ODR ^= (ODR_MASK << PinNum);
	}
	else
	{
		Local_u8ErrorState=NOT_OK;
	}
	return Local_u8ErrorState;
}

uint8_t GPIO_U8ReadPinVal(Port_t Port,Pin_t PinNum,PinVal_t *PinVal)
{
	uint8_t Local_u8ErrorState=OK;
	if(PinVal != NULL)
	{
		if((Port <= PORTH) && (PinNum <= PIN15))
		{
			*PinVal=((GPIOPort[Port]->IDR >> PinNum) & IDR_MASK);
		}
		else
		{
			Local_u8ErrorState=NOT_OK;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

