/*
 *  RCC_interface.h
 *
 *  Created on: Nov 23, 2024
 *  Author: Ahmed Ragab
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/************************include*****************************************/
#include "STM32F401XX.h"
/************************************************************************/

/**********************CLOCK STATUS**************************************/
typedef enum{
	RCC_OFF,
	RCC_ON
}CLKState_t;
/************************************************************************/

/*********************CLOCK TYPE*****************************************/
typedef enum{
	HSI,
	HSE,
	PLL
}CLKType_t;
/************************************************************************/

/*********************HSE clock bypass***********************************/
typedef enum{
	not_bypassed,
	bypassed
}Bypass_t;
/************************************************************************/

/*********************AHB1***********************************************/
typedef enum{
	RCC_GPIOA,
	RCC_GPIOB,
	RCC_GPIOC,
	RCC_GPIOD,
	RCC_GPIOE,
	RCC_GPIOH=7,
	RCC_CRCl=12,
	RCC_DMA1=21,
	RCC_DMA2
}AHB1_Peripheral_t;
/************************************************************************/

/*********************APB1***********************************************/
typedef enum{
	RCC_TIM2,RCC_TIM3,RCC_TIM4,RCC_TIM5,RCC_WWDG=11,RCC_SPI2=14,RCC_SPI3,RCC_USART2=17,RCC_I2C1=21,RCC_I2C2,RCC_I2C3,RCC_PWR=28
}APB1_Peripheral_t;
/************************************************************************/

/*********************APB2***********************************************/
typedef enum{
	RCC_TIM1,RCC_USART1=4,RCC_USART6,RCC_ADC1=8,RCC_SDIO=11,RCC_SPI1,RCC_SPI4,RCC_SYSCFG,RCC_TIM9=16,RCC_TIM10,RCC_TIM11
}APB2_Peripheral_t;
/************************************************************************/

/**
 * @brief Enum for PLLM (Division factor for the PLL input clock).
 */
typedef enum {
    PLLM_2 = 2,   /*!< PLLM = 2 */
    PLLM_3 = 3,   /*!< PLLM = 3 */
    PLLM_4 = 4,   /*!< PLLM = 4 */
    PLLM_5 = 5,   /*!< PLLM = 5 */
    PLLM_6 = 6,   /*!< PLLM = 6 */
    PLLM_7 = 7,   /*!< PLLM = 7 */
    PLLM_8 = 8,   /*!< PLLM = 8 */
    PLLM_9 = 9,   /*!< PLLM = 9 */
    PLLM_10 = 10, /*!< PLLM = 10 */
    PLLM_11 = 11, /*!< PLLM = 11 */
    PLLM_12 = 12, /*!< PLLM = 12 */
    PLLM_13 = 13, /*!< PLLM = 13 */
    PLLM_14 = 14, /*!< PLLM = 14 */
    PLLM_15 = 15, /*!< PLLM = 15 */
    PLLM_16 = 16, /*!< PLLM = 16 */
    PLLM_17 = 17, /*!< PLLM = 17 */
    PLLM_18 = 18, /*!< PLLM = 18 */
    PLLM_19 = 19, /*!< PLLM = 19 */
    PLLM_20 = 20, /*!< PLLM = 20 */
    PLLM_21 = 21, /*!< PLLM = 21 */
    PLLM_22 = 22, /*!< PLLM = 22 */
    PLLM_23 = 23, /*!< PLLM = 23 */
    PLLM_24 = 24, /*!< PLLM = 24 */
    PLLM_25 = 25, /*!< PLLM = 25 */
    PLLM_26 = 26, /*!< PLLM = 26 */
    PLLM_27 = 27, /*!< PLLM = 27 */
    PLLM_28 = 28, /*!< PLLM = 28 */
    PLLM_29 = 29, /*!< PLLM = 29 */
    PLLM_30 = 30, /*!< PLLM = 30 */
    PLLM_31 = 31, /*!< PLLM = 31 */
    PLLM_32 = 32, /*!< PLLM = 32 */
    PLLM_33 = 33, /*!< PLLM = 33 */
    PLLM_34 = 34, /*!< PLLM = 34 */
    PLLM_35 = 35, /*!< PLLM = 35 */
    PLLM_36 = 36, /*!< PLLM = 36 */
    PLLM_37 = 37, /*!< PLLM = 37 */
    PLLM_38 = 38, /*!< PLLM = 38 */
    PLLM_39 = 39, /*!< PLLM = 39 */
    PLLM_40 = 40, /*!< PLLM = 40 */
    PLLM_41 = 41, /*!< PLLM = 41 */
    PLLM_42 = 42, /*!< PLLM = 42 */
    PLLM_43 = 43, /*!< PLLM = 43 */
    PLLM_44 = 44, /*!< PLLM = 44 */
    PLLM_45 = 45, /*!< PLLM = 45 */
    PLLM_46 = 46, /*!< PLLM = 46 */
    PLLM_47 = 47, /*!< PLLM = 47 */
    PLLM_48 = 48, /*!< PLLM = 48 */
    PLLM_49 = 49, /*!< PLLM = 49 */
    PLLM_50 = 50, /*!< PLLM = 50 */
    PLLM_51 = 51, /*!< PLLM = 51 */
    PLLM_52 = 52, /*!< PLLM = 52 */
    PLLM_53 = 53, /*!< PLLM = 53 */
    PLLM_54 = 54, /*!< PLLM = 54 */
    PLLM_55 = 55, /*!< PLLM = 55 */
    PLLM_56 = 56, /*!< PLLM = 56 */
    PLLM_57 = 57, /*!< PLLM = 57 */
    PLLM_58 = 58, /*!< PLLM = 58 */
    PLLM_59 = 59, /*!< PLLM = 59 */
    PLLM_60 = 60, /*!< PLLM = 60 */
    PLLM_61 = 61, /*!< PLLM = 61 */
    PLLM_62 = 62, /*!< PLLM = 62 */
    PLLM_63 = 63  /*!< PLLM = 63 */
}RCC_PLLM_t;


/**
 * @brief Enum for PLLN (Multiplication factor for the PLL VCO).
 */
typedef enum {
	PLLN_0 = 0, /*!< PLLN = 0 */
	PLLN_1 = 1, /*!< PLLN = 1 */
	PLLN_2 = 2, /*!< PLLN = 2 */
	/*...*/
	PLLN_336 = 336, /*!< PLLN = 336 */
	/*...*/
    PLLN_192 = 192, /*!< PLLN = 192 */
    PLLN_193 = 193, /*!< PLLN = 193 */
    PLLN_194 = 194, /*!< PLLN = 194 */
	/*...*/
    PLLN_432 = 432 /*!< PLLN = 432 */
	/*...*/
}RCC_PLLN_t;


/**
 * @brief Enum for PLLP (Main PLL division factor for system clock).
 */
typedef enum {
    PLLP_2 = 0b00, /*!< PLLP = 2 */
    PLLP_4 = 0b01, /*!< PLLP = 4 */
    PLLP_6 = 0b10, /*!< PLLP = 6 */
    PLLP_8 = 0b11  /*!< PLLP = 8 */
}RCC_PLLP_t;


/************************************************************************/
/**
 * @brief : Configures and manages the RCC clock sources.
 * @param : CLKtype: The type of clock to configure (HSI, HSE, or PLL).
 * @param : CLKstatus: The desired status of the clock (RCC_ON or RCC_OFF).
 * @retval: RCC_ERRORSTATUS_OK if successful,
 *          RCC_ERRORSTATUS_NOT_OK if an invalid clock type is provided,
 *          RCC_ERRORSTATUS_TIME_OUT if a timeout occurs.
 **/
/*======================================================================*/
uint8_t RCC_SETCLK(CLKType_t CLKtype,CLKState_t CLKstatus);
/************************************************************************/

/************************************************************************/
/**
 * @brief : Set the system clock source.
 * @param : CLK_TYPE: The clock source (HSI, HSE, or PLL).
 * @retval: RCC_ERRORSTATUS_OK if successful,
 *          RCC_ERRORSTATUS_TIME_OUT if a timeout occurs.
 **/
/*======================================================================*/
uint8_t RCC_SETSYSCLK(CLKType_t CLKTYPE);
/************************************************************************/

/************************************************************************/
/**
 * @brief : Configures the HSE oscillator (enable/disable bypass mode).
 * @param : CONFIG: Configuration for HSE (0: disable bypass, 1: enable bypass).
 *         - 0: HSE oscillator directly drives the system.
 *         - 1: External clock source bypasses the HSE oscillator.
 *@retval : None
 **/
/*======================================================================*/
void RCC_HSEConfig(Bypass_t CONFIG);
/************************************************************************/

/************************************************************************/
/**
 * @brief  Configures the Phase-Locked Loop (PLL) for clock generation.
 *         This function allows you to select the PLL source (HSI or HSE),
 *         configure the PLL multiplication factor (PLLM, PLLN, PLLP),
 *         and enable the PLL after configuration.
 *         It also waits for the PLL to stabilize after enabling.
 *
 * @param  Source: PLLSRC: Clock source for PLL (0: HSI, 1: HSE).
 *
 * @param  PLLM  : The PLL multiplication factor for the input clock.
 *                 It defines the division factor for the PLL input clock.
 * @param  PLLN  : The PLL multiplication factor for the PLL.
 *                 It defines the multiplication factor for the PLL input.
 * @param  PLLP  : The PLL division factor for the output PLL clock.
 *                 The final PLL output clock will be divided by (PLLP/2).
 *
 * @retval uint8_t: The function returns an error state:
 *                  - OK: If the PLL is successfully configured.
 *                  - TIME_OUT: If the PLL failed to stabilize or timeout occurred.
 *                  - NOT_OK: If an invalid PLL source is selected.
 */
/*======================================================================*/
uint8_t RCC_u8PLLConfig(CLKType_t Source, RCC_PLLM_t PLLM, RCC_PLLN_t PLLN, RCC_PLLP_t PLLP);
/************************************************************************/

/************************************************************************/
/**
 * @brief  Enable the clock for a specific peripheral on the AHB bus.
 * @param  PERIPHERAL: The peripheral bit position in the AHB1ENR register.
 * @retval None
 **/
/*======================================================================*/
void RCC_AHB1ENABLECLK(AHB1_Peripheral_t peripheral);
/************************************************************************/

/************************************************************************/
/**
 * @brief  Disable the clock for a specific peripheral on the AHB bus.
 * @param  PERIPHERAL: The peripheral bit position in the AHB1ENR register.
 * @retval None
 **/
/*======================================================================*/
void RCC_AHB1DISABLECLK(AHB1_Peripheral_t peripheral);
/************************************************************************/

/************************************************************************/
/**
 * @brief  Enable the clock for a specific peripheral on the APB1 bus.
 * @param  PERIPHERAL: The peripheral bit position in the APB1ENR register.
 * @retval None
 **/
/*======================================================================*/
void RCC_APB1ENABLECLK(APB1_Peripheral_t peripheral);
/************************************************************************/

/************************************************************************/
/**
 * @brief  Disable the clock for a specific peripheral on the APB1 bus.
 * @param  PERIPHERAL: The peripheral bit position in the APB1ENR register.
 * @retval None
 **/
/*======================================================================*/
void RCC_APB1DISABLECLK(APB1_Peripheral_t peripheral);
/************************************************************************/

/************************************************************************/
/**
 * @brief  Enable the clock for a specific peripheral on the APB2 bus.
 * @param  PERIPHERAL: The peripheral bit position in the APB2ENR register.
 * @retval None
 **/
/*======================================================================*/
void RCC_APB2ENABLECLK(APB2_Peripheral_t peripheral);
/************************************************************************/

/************************************************************************/
/**
 * @brief  Disable the clock for a specific peripheral on the APB2 bus.
 * @param  PERIPHERAL: The peripheral bit position in the APB2ENR register.
 * @retval None
 **/
/*======================================================================*/
void RCC_APB2DISABLECLK(APB2_Peripheral_t peripheral);
/************************************************************************/

#endif /* MCAL_RCC_RCC_INTERFACE_H_ */
