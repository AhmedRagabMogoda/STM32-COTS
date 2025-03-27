/*
 *  CRC_program.c
 *
 *  Created on: Mar 24, 2025
 *  Author: Ahmed Ragab
 */


#include "stm32f401xx.h"
#include "ErrorState.h"
#include "CRC_interface.h"


uint8_t CRC_Init(CRC_Config_t *Config)
{
	uint8_t Local_u8ErrorState=OK;
	if (Config != NULL)
	{
	    /* Reset CRC peripheral */
	    CRC->CR = 1;
	    /* Set initial value */
	    CRC->DR = 0;
	    /* Update state */
	    Config->State = CRC_STATE_READY;
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t CRC_RESET(CRC_Config_t *Config)
{
	uint8_t Local_u8ErrorState=OK;
	if (Config != NULL)
	{
	    /* Reset CRC peripheral */
	    CRC->CR = 1;
	    /* Reset last result */
	    Config->CRCResult = 0;
	    /* Update state */
	    Config->State = CRC_STATE_RESET;
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint32_t CRC_Accumulate(CRC_Config_t *Config, uint32_t pBuffer[], uint32_t BufferLength)
{
	uint32_t Result = 0;
	if (Config != NULL)
	{
	    /* Set CRC to busy state */
	    Config->State = CRC_STATE_BUSY;
	    /* Feed data to CRC register */
	    uint32_t Count = 0;
	    for (Count = 0; Count < BufferLength; Count++)
	    {
	        CRC->DR = pBuffer[Count];
	    }
	    /* Read final CRC result */
	    Config->CRCResult = CRC->DR;
	    /* Set CRC to ready state */
	    Config->State = CRC_STATE_READY;
	    Result = Config->CRCResult;
	}
	return Result;
}

