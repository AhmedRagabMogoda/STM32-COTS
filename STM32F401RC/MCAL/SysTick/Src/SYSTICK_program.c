/*
 *  SYSTICK_program.c
 *
 *  Created on: Nov 27, 2024
 *  Author: Ahmed Ragab
 */

#include "stm32f401xx.h"
#include "ErrorState.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"

void SysTick_voidInit(uint32_t Copy_u32TickHZ)
{
	/* calculate the required number of ticks */
	uint32_t Local_u32RelodVal = (SYSTICK_TIME_CLK/Copy_u32TickHZ);
	/* decrement by one to consider the multi-shot timer */
	Local_u32RelodVal -=1;
	/* Load the specified reload value into the SysTick timer */
	STK->LOAD = Local_u32RelodVal;
	/* Clear the current value register to start counting from zero */
	STK->VAL = CLEAR;
	/* Enable SysTick Exception and select the clock source and SysTick timer */
	STK->CTRL |= (CTRL_MASK << EXCEPTION_PIN_ACCESS);
	STK->CTRL |= (CTRL_MASK << CLKSOURCE_PIN_ACCESS);
	STK->CTRL |= (CTRL_MASK << ENABLE_PIN_ACCESS);
}

uint8_t SysTick_u8DelayMilliSecond(uint32_t Time)
{
    uint8_t Local_u8ErrorState = OK;
    if (Time > CLEAR)
    {
    	/* Reload value corresponds to 1 millisecond */
    	uint32_t Reload = SYSTICK_TIME_CLK / MILLI_SECOND;
    	Reload -=1;
        /* Perform Time repetitions of 1 millisecond delays */
        while (Time > CLEAR)
        {
            SysTick_VoidPolling(Reload);
            Time--;
        }
    }
    else
    {
        Local_u8ErrorState = NOT_OK;
    }
    return Local_u8ErrorState;
}

uint8_t SysTick_u8DelayMicroSecond(uint32_t Time)
{
    uint8_t Local_u8ErrorState = OK;
    if (Time > CLEAR)
    {
    	/* Reload value corresponds to 1 microsecond */
    	uint32_t Reload = SYSTICK_TIME_CLK / MACRO_SECOND;
    	Reload -=1;
        /* Perform Time repetitions of 1-microsecond delays */
        while (Time > CLEAR)
        {
            SysTick_VoidPolling(Reload);
            Time--;
        }
    }
    else
    {
        Local_u8ErrorState = NOT_OK;
    }
    return Local_u8ErrorState;
}

static void SysTick_VoidPolling(uint32_t Reload)
{
    /* Load the specified reload value into the SysTick timer */
    STK->LOAD = Reload;
    /* Clear the current value register to start counting from zero */
    STK->VAL = CLEAR;
    /* Enable SysTick timer and select the clock source */
    STK->CTRL |= (CTRL_MASK << CLKSOURCE_PIN_ACCESS) | (CTRL_MASK << ENABLE_PIN_ACCESS);
    /* Wait until the count flag is set (timer expires) */
    while (!(STK->CTRL & (CTRL_MASK << COUNTFLAG_PIN_ACCESS)));
    /* Disable SysTick and clear the control register after completion */
    STK->CTRL = CLEAR;
}




