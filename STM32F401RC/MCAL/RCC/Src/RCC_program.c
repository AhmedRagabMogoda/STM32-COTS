/**
 ******************************************************************************
 * @file           : RCC_program.c
 * @author         : Ahmed Ragab Mogoda
 * @brief          : RCC Driver Implementation
 * @date           : Nov 23, 2024
 ******************************************************************************
 * @details
 * This file contains the implementation of all RCC-related functions,
 * allowing configuration and management of system clocks and peripheral
 * clocks for the STM32F401RC microcontroller.
 ******************************************************************************
 **/

/**********************include*******************************************/
#include "ErrorState.h"
#include "RCC_interface.h"
#include "RCC_private.h"

/************************************************************************/

/*****************RCC SET CLocK******************************************/
uint8_t RCC_SETCLK(CLKType_t CLKtype,CLKState_t CLKstate)
{
	uint8_t Local_u8ErrorState=OK;
    uint32_t TIME = TIMEOUT;         /* Timeout counter*/
    switch (CLKtype)
    {
		case HSI:
		{
			if (CLKstate == RCC_ON)
			{
				RCC->CR |= (CR_MASK << HSION); /* Enable HSI */
				while (((RCC->CR & (CR_MASK << HSIRDY)) == RCC_OFF) && (--TIME)); /* Wait for HSI to stabilize*/
			}
			else if (CLKstate == RCC_OFF)
			{
				RCC->CR &= ~(CR_MASK << HSION); /* Disable HSI */
			}
			else
			{
				Local_u8ErrorState=NOT_OK;
			}
			break;
		}
		case HSE:
		{
			if (CLKstate == RCC_ON)
			{
				RCC->CR |= (CR_MASK << HSEON); /* Enable HSE*/
				while (((RCC->CR & (CR_MASK << HSERDY)) == RCC_OFF) && (--TIME)); /* Wait for HSI to stabilize*/
			}
			else if (CLKstate == RCC_OFF)
			{
				RCC->CR &= ~(CR_MASK << HSEON); /* Disable HSE*/
			}
			else
			{
				Local_u8ErrorState=NOT_OK;
			}
			break;
		}
		case PLL:
		{
			if (CLKstate == RCC_ON)
			{
				RCC->CR |= (CR_MASK << PLLON); /* Enable PLL*/
				while (((RCC->CR & (CR_MASK << PLLRDY)) == RCC_OFF) && (--TIME)); /* Wait for HSI to stabilize*/
			}
			else if (CLKstate == RCC_OFF)
			{
				RCC->CR &= ~(CR_MASK << PLLON); /* Disable PLL*/
			}
			else
			{
				Local_u8ErrorState=NOT_OK;
			}
			break;
		}
		default:
			Local_u8ErrorState=NOT_OK; /* Invalid clock type*/
    }
    /* Check if timeout occurred*/
    if (TIME == TIME_FINISHED)
    {
    	Local_u8ErrorState=TIME_OUT;
    }

    return Local_u8ErrorState;
}
/************************************************************************/

/********************RCC SET system CLocK********************************/
uint8_t RCC_SETSYSCLK(CLKType_t CLKTYPE)
{
	uint8_t Local_u8ErrorState=OK;
	uint32_t TIME=TIMEOUT;
	RCC->CFGR &= ~(SW_MASK << SW_PIN_ACCESS);
	RCC->CFGR |= (CLKTYPE << SW_PIN_ACCESS);
	while(((SWS_MASK & SW_MASK) != CLKTYPE) && --TIME);
	/* Check if timeout occurred*/
	if (TIME == TIME_FINISHED)
	{
		Local_u8ErrorState=TIME_OUT;
	}
	return Local_u8ErrorState;
}
/************************************************************************/

/****************RCC HSECONFIG*******************************************/
void RCC_HSEConfig(Bypass_t CONFIG)
{
	RCC->CR=(RCC->CR & ~(CR_MASK << HSEBYP)) | (CONFIG << HSEBYP);
}
/************************************************************************/

/*********************RCC PLLCONFIG**************************************/

uint8_t RCC_u8PLLConfig(CLKType_t Source, RCC_PLLM_t PLLM, RCC_PLLN_t PLLN, RCC_PLLP_t PLLP)
{
	uint8_t Local_u8ErrorState=OK;
	uint32_t TIME=TIMEOUT;
    /* Disable the PLL */
    RCC->CR &= ~(CR_MASK << PLLON);
    /* Wait until PLL is disabled */
    while ( (RCC->CR & (CR_MASK << PLLRDY)));
    /* Configure the PLL source (HSI or HSE) */
    if (Source == HSI)
    {
    	RCC->PLLCFGR &= ~(PLLSRC_MASK << PLLSRC_PIN_ACCESS);
    }
    else if (Source == HSE)
    {
    	RCC->PLLCFGR |= (PLLSRC_MASK << PLLSRC_PIN_ACCESS);
    }
    else
    {
    	Local_u8ErrorState=NOT_OK;
    }
    /* Configure (PLLM) PLL multiplication factor */
	RCC->PLLCFGR &= ~(PLLM_MASK << PLLM_PIN_ACCESS);
	RCC->PLLCFGR |= (PLLM << PLLM_PIN_ACCESS);
    /* Configure PLLN */
	RCC->PLLCFGR &= ~(PLLN_MASK << PLLN_PIN_ACCESS);
	RCC->PLLCFGR |= (PLLN << PLLN_PIN_ACCESS);
    /* Configure PLLP */
	RCC->PLLCFGR &= ~(PLLP_MASK << PLLP_PIN_ACCESS);
	RCC->PLLCFGR |= (((PLLP/2)-1) << PLLP_PIN_ACCESS);
    /* Enable the PLL */
	RCC->CR |= (CR_MASK << PLLON);
	/* Wait for HSI to stabilize*/
	while (((RCC->CR & (CR_MASK << PLLRDY)) == RCC_OFF) && (--TIME));
	if (TIME == TIME_FINISHED)
	{
		Local_u8ErrorState=TIME_OUT;
	}
	return Local_u8ErrorState;
}
/************************************************************************/

/****************RCC AHP ENABLE CLK**************************************/
void RCC_AHB1ENABLECLK(AHB1_Peripheral_t peripheral)
{
	RCC->AHB1ENR |= (AHB1ENR_MASK << peripheral);
}
/************************************************************************/

/****************RCC AHP DISABLE CLK**************************************/
void RCC_AHB1DISABLECLK(AHB1_Peripheral_t peripheral)
{
	RCC->AHB1ENR &= ~(AHB1ENR_MASK << peripheral);
}
/************************************************************************/

/****************RCC APB1 ENABLE CLK**************************************/
void RCC_APB1ENABLECLK(APB1_Peripheral_t peripheral)
{
	RCC->APB1ENR |= (APB1ENR_MASK << peripheral);
}
/************************************************************************/

/****************RCC APB1 DISABLE CLK**************************************/
void RCC_APB1DISABLECLK(APB1_Peripheral_t peripheral)
{
	RCC->APB1ENR &= ~(APB1ENR_MASK << peripheral);
}
/************************************************************************/

/****************RCC APB2 ENABLE CLK**************************************/
void RCC_APB2ENABLECLK(APB2_Peripheral_t peripheral)
{
	RCC->APB2ENR |= (APB1ENR_MASK << peripheral);
}
/************************************************************************/

/****************RCC APB2 DISABLE CLK**************************************/
void RCC_APB2DISABLECLK(APB2_Peripheral_t peripheral)
{
	RCC->APB2ENR &= ~(APB1ENR_MASK << peripheral);
}
/************************************************************************/
