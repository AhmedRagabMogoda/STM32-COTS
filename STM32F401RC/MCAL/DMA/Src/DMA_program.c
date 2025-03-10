/*
 *  DMA_program.c
 *
 *  Created on: Dec 8, 2024
 *  Author: Ahmed Ragab
 */

/*************************  Includes *************************************/
#include "stm32f401xx.h"
#include "ErrorState.h"
#include "DMA_interface.h"
#include "DMA_private.h"

/************************* Global Variable *******************************/
static DMA_RegDef_t* DMA[MAX_NUMBER_DMA] = {DMA1,DMA2};

/************************  Implementation Function  **********************/

uint8_t DMA_u8Init(const DMA_Config_t *Copy_DMAConfig)
{
	uint8_t Local_u8ErrorState=OK;
	if(Copy_DMAConfig !=  NULL)
	{
		/* Disable the stream before configuration */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR &= ~(ENABLE_STREAM_MASK << ENABLE_STREAM_PIN_ACCESS);
		/*  Configure the channel */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR &= ~(CHANNEL_STREAM_MASK << CHANNEL_STREAM_PIN_ACCESS);
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR |= (Copy_DMAConfig->Channel_Number << CHANNEL_STREAM_PIN_ACCESS);
		/* Configure the priority */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR &= ~(PRIORITY_STREAM_MASK << PRIORITY_STREAM_PIN_ACCESS);
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR |= (Copy_DMAConfig->Priority << PRIORITY_STREAM_PIN_ACCESS);
		/* Configure the direction */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR &= ~(DIRECTION_STREAM_MASK << DIRECTION_STREAM_PIN_ACCESS);
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR |= (Copy_DMAConfig->Direction << DIRECTION_STREAM_PIN_ACCESS);
		/* Configure the mode (Normal or Circular) */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR &= ~(CIRCULAR_STREAM_MASK << CIRCULAR_STREAM_PIN_ACCESS);
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR |= (Copy_DMAConfig->Circular_Mode << CIRCULAR_STREAM_PIN_ACCESS);
		/* Configure FIFO mode */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].FCR &= ~(DIRECT_MODE_STREAM_MASK << DIRECT_MODE_STREAM_PIN_ACCESS);
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].FCR |= (Copy_DMAConfig->FIFO_Mode << DIRECT_MODE_STREAM_PIN_ACCESS);
		/* Configure FIFO Threshold Selection Mode */
		if (Copy_DMAConfig->FIFO_Mode == DMA_FIFO_Enable)
		{
		    DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].FCR &= ~(FIFO_THRESHOLD_STREAM_MASK << FIFO_THRESHOLD_STREAM_PIN_ACCESS);
		    DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].FCR |= (Copy_DMAConfig->FIFO_Threshold << FIFO_THRESHOLD_STREAM_PIN_ACCESS);
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t DMA_u8Start(const DMA_Config_t *Copy_DMAConfig,uint32_t Copy_u32PeripheralAddress,uint32_t Copy_u32MemoryAddress,uint16_t Copy_u16DataLenght)
{
	uint8_t Local_u8ErrorState=OK;
	if(Copy_DMAConfig !=  NULL)
	{
		/* Peripheral address */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].PAR = Copy_u32PeripheralAddress;
		/* Memory address */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].M0AR = Copy_u32MemoryAddress;
		/* Set the number of data items to transfer */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].NDTR = Copy_u16DataLenght;
		/* Enable the stream before configuration */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR |= (ENABLE_STREAM_MASK << ENABLE_STREAM_PIN_ACCESS);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

static uint8_t DMA_u8GetFlagBitPosition(DMA_StreamNumber_t StreamNumber, DMA_StatusID_t StatusID)
{
	uint8_t BaseBitPosition;
	switch(StreamNumber)
	{
	case Stream0 : case Stream4 : BaseBitPosition=0;  break;
	case Stream1 : case Stream5 : BaseBitPosition=6;  break;
	case Stream2 : case Stream6 : BaseBitPosition=16; break;
	case Stream3 : case Stream7 : BaseBitPosition=22; break;
	default : break;
	}
	return BaseBitPosition + StatusID;
}

uint8_t DMA_u8PollForTransfer(const DMA_Config_t *Copy_DMAConfig)
{
	uint8_t Local_u8ErrorState=OK;
	uint32_t Time=TIMEOUT;
	if(Copy_DMAConfig !=  NULL)
	{
		/* Determine the register (LISR or HISR) based on the stream number */
		uint8_t RegNum = Copy_DMAConfig->Stream_Number / ISR_REG_SHIFTING;
		/* Determine the bit position of the Transfer Complete Flag (TCIF) */
		uint8_t TCIF_BitPosition = DMA_u8GetFlagBitPosition(Copy_DMAConfig->Stream_Number,TCIF);
		/* Polling for transfer completion */
		while( !((DMA[Copy_DMAConfig->DMA_Number]->ISR[RegNum] >> TCIF_BitPosition ) & ONE) && (--Time));
		/* If timeout expires, return timeout error */
		if (Time == TIME_FINISHED)
		    {
		    	Local_u8ErrorState=TIME_OUT;
		    }
		/* Clear the Transfer Complete Flag */
		DMA[Copy_DMAConfig->DMA_Number]->IFCR[RegNum] |= (ONE << TCIF_BitPosition);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t DMA_u8Start_IT(const DMA_Config_t *Copy_DMAConfig,uint32_t Copy_u32PeripheralAddress,uint32_t Copy_u32MemoryAddress,uint16_t Copy_u16DataLenght)
{
	uint8_t Local_u8ErrorState=OK;
	if(Copy_DMAConfig !=  NULL)
	{
		/* Peripheral address */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].PAR = Copy_u32PeripheralAddress;
		/* Memory address */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].M0AR = Copy_u32MemoryAddress;
		/* Set the number of data items to transfer */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].NDTR = Copy_u16DataLenght;
		/* Enable interrupt for transfer complete or error */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR |= (TCIE_MASK << TCIE_PIN_ACCESS) | (TEIE_MASK << TEIE_PIN_ACCESS);
		/* Enable the stream */
		DMA[Copy_DMAConfig->DMA_Number]->STREAM[Copy_DMAConfig->Stream_Number].CR |= (ENABLE_STREAM_MASK << ENABLE_STREAM_PIN_ACCESS);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t DMA_u8GetStatus(const DMA_Config_t *Copy_DMAConfig,DMA_StatusID_t StatusID,uint8_t *Copy_u8Status)
{
	uint8_t Local_u8ErrorState=OK;
	if(Copy_DMAConfig !=  NULL)
	{
		/* Determine the register (LISR or HISR) based on the stream number */
		uint8_t RegNum = Copy_DMAConfig->Stream_Number / ISR_REG_SHIFTING;
		/* Determine the bit position of the desired flag */
		uint8_t BitPosition = DMA_u8GetFlagBitPosition(Copy_DMAConfig->Stream_Number,StatusID);
		/* Extract the status flag and store the result */
		*Copy_u8Status = ((DMA[Copy_DMAConfig->DMA_Number]->ISR[RegNum] >> BitPosition ) & ONE);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
