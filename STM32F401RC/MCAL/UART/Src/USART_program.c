/*
 * USART_program.c
 *
 * Created on: Dec 9, 2024
 * Author: Ahmed Ragab Mogoda
 *
 * Description:
 * This file contains the implementation of UART functionalities for STM32F401RC.
 * It includes initialization, data transmission, and reception using both polling and DMA modes.
 */

/*************************  Includes *************************************/
#include "stm32f401xx.h"
#include "ErrorState.h"
#include "USART_Interface.h"
#include "USART_Private.h"

/************************* Global Variable *******************************/
static USART_RegDef_t* USART[USART_NUM_MAX]={USART1,USART2,USART6};

/************************  Implementation Function  **********************/

uint8_t UART_u8Init(UART_Config_t *Copy_UARTConfig)
{
	uint8_t Local_u8ErrorState = OK;
	if(Copy_UARTConfig!=NULL)
	{
		/* Configure mode (TX/RX) */
		USART[Copy_UARTConfig->UARTNumber]->CR1 &= ~(TX_RX_MASK << TX_RX_PIN_ACCESS);
		USART[Copy_UARTConfig->UARTNumber]->CR1 |= (Copy_UARTConfig->Mode << TX_RX_PIN_ACCESS);
		/* Configure word length */
		USART[Copy_UARTConfig->UARTNumber]->CR1 &= ~(WORDLENGHT_MASK << WORDLENGHT_PIN_ACCESS);
		USART[Copy_UARTConfig->UARTNumber]->CR1 |= (Copy_UARTConfig->WordLength << WORDLENGHT_PIN_ACCESS);
		/* Configure Parity */
		USART[Copy_UARTConfig->UARTNumber]->CR1 &= ~(PARITY_MASK << PARITY_PIN_ACCESS);
		USART[Copy_UARTConfig->UARTNumber]->CR1 |= (Copy_UARTConfig->Parity << PARITY_PIN_ACCESS);
		/* Configure Parity Type */
		if(Copy_UARTConfig->Parity==PARITY_ENABLE)
		{
			USART[Copy_UARTConfig->UARTNumber]->CR1 &= ~(PARITYTYPE_MASK << PARITYTYPE_PIN_ACCESS);
			USART[Copy_UARTConfig->UARTNumber]->CR1 |= (Copy_UARTConfig->ParityType << PARITYTYPE_PIN_ACCESS);
		}
		/* Configure Over sampling mode */
		USART[Copy_UARTConfig->UARTNumber]->CR1 &= ~(OVERSAMPLING_MASK << OVERSAMPLING_PIN_ACCESS);
		USART[Copy_UARTConfig->UARTNumber]->CR1 |= (Copy_UARTConfig->OverSampling << OVERSAMPLING_PIN_ACCESS);
		/* Configure stop bits */
		USART[Copy_UARTConfig->UARTNumber]->CR2 &= ~(STOPBIT_MASK << STOPBIT_PIN_ACCESS);
		USART[Copy_UARTConfig->UARTNumber]->CR2 |= (Copy_UARTConfig->StopBits << STOPBIT_PIN_ACCESS);
		/* Configure hardware flow control */
		USART[Copy_UARTConfig->UARTNumber]->CR3 &= ~(CTS_RTS_MASK << CTS_RTS_PIN_ACCESS);
		USART[Copy_UARTConfig->UARTNumber]->CR3 |= (Copy_UARTConfig->HW_FlowControl << CTS_RTS_PIN_ACCESS);
		/* Configure baud rate */
		uint32_t Result = (F_CLK) / (8 * (2 - Copy_UARTConfig->OverSampling) * Copy_UARTConfig->BaudRate);
		uint16_t DIV_Mantissa = Result;        /* Mantissa part */
		uint8_t DIV_Fraction = 0;
		if (Copy_UARTConfig->OverSampling == OVERSAMPLING_16)
		{
		    DIV_Fraction = (uint8_t)(((Result - DIV_Mantissa) * 16) + 0.5);  /* Calculate fraction (4 bits) */
		    if (DIV_Fraction > 15) { DIV_Mantissa += 1; DIV_Fraction = 0;}   /* Clamp to max 15 */
		}
		else if (Copy_UARTConfig->OverSampling == OVERSAMPLING_8)
		{
		    DIV_Fraction = (uint8_t)(((Result - DIV_Mantissa) * 8) + 0.5);   /* Calculate fraction (3 bits) */
		    if (DIV_Fraction > 7) { DIV_Mantissa += 1; DIV_Fraction = 0; }   /* Clamp to max 7 */
		}
		else
		{
		    Local_u8ErrorState = NOT_OK;
		}
		/* Write to BRR register: Mantissa in higher bits, Fraction in lower bits */
		USART[Copy_UARTConfig->UARTNumber]->BRR = (DIV_Mantissa << DIV_MANTISSA_PIN_ACCESS) | (DIV_Fraction << DIV_FRACTION_PIN_ACCESS);
		/*
		uint32_t Result = (F_CLK*1000u) / (8*(2-Copy_UARTConfig->OverSampling)*Copy_UARTConfig->BaudRate);
		uint16_t DIV_Mantissa = Result/1000u;
		uint8_t DIV_Fraction=0;
		if(Copy_UARTConfig->OverSampling==OVERSAMPLING_16)     {DIV_Fraction = (((Result%1000)*16)+500u) / 1000u;}
		else if(Copy_UARTConfig->OverSampling==OVERSAMPLING_8) {DIV_Fraction = (((Result%1000)*8)+500u) / 1000u;}
		else {Local_u8ErrorState = NOT_OK;}
		USART[Copy_UARTConfig->UARTNumber]->BRR = (DIV_Mantissa << DIV_MANTISSA_PIN_ACCESS) | (DIV_Fraction << DIV_FRACTION_PIN_ACCESS);
		*/
		/* Enable USART */
		USART[Copy_UARTConfig->UARTNumber]->CR1 &= ~(ENABLE_MASK << ENABLE_PIN_ACCESS);
		USART[Copy_UARTConfig->UARTNumber]->CR1 |= (Copy_UARTConfig->UARTEnable << ENABLE_PIN_ACCESS);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t UART_u8Send(UART_Config_t *Copy_UARTConfig,uint8_t *Data, uint32_t DataLength)
{
	uint8_t Local_u8ErrorState = OK;
	if(Data != NULL && Copy_UARTConfig != NULL)
	{
		uint32_t Time;
		uint32_t Count;
		for(Count=CLEAR;Count<DataLength;Count++)
		{
			Time = TIMEOUT;
			/* Wait until Data register is empty */
			while( !((USART[Copy_UARTConfig->UARTNumber]->SR >> TXE_PIN_ACCESS) & ONE) && --Time);
			if (Time == TIME_FINISHED)
			{
				Local_u8ErrorState=TIME_OUT;
				break;
		    }
			USART[Copy_UARTConfig->UARTNumber]->DR = Data[Count];
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t UART_u8Receive(UART_Config_t *Copy_UARTConfig,uint8_t *Data, uint32_t DataLength)
{
	uint8_t Local_u8ErrorState = OK;
	if(Data != NULL && Copy_UARTConfig != NULL)
	{
		uint32_t Time;
		uint32_t Count;
		for(Count=CLEAR;Count<DataLength;Count++)
		{
			Time = TIMEOUT;
			/* Wait until Data register is  not empty and Received data is ready */
			while( !((USART[Copy_UARTConfig->UARTNumber]->SR >> RXNE_PIN_ACCESS) & ONE) && --Time);
			if (Time == TIME_FINISHED)
			{
				Local_u8ErrorState=TIME_OUT;
				break;
		    }
			Data[Count] = USART[Copy_UARTConfig->UARTNumber]->DR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t UART_u8Send_DMA(UART_Config_t *Copy_UARTConfig)
{
	uint8_t Local_u8ErrorState = OK;
	if(Copy_UARTConfig != NULL)
	{
		/* Enable DMA for USART transmission */
		USART[Copy_UARTConfig->UARTNumber]->CR3 |= (DMAT_MASK << DMAT_PIN_ACCESS);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t UART_u8Receive_DMA(UART_Config_t *Copy_UARTConfig)
{
	uint8_t Local_u8ErrorState = OK;
	if(Copy_UARTConfig != NULL)
	{
		/* Enable DMA for USART Receive */
		USART[Copy_UARTConfig->UARTNumber]->CR3 |= (DMAR_MASK << DMAR_PIN_ACCESS);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

