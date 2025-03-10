/*
 * SYSTICK_interface.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Ahmed Ragab
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

/* Function: SysTick_voidInit
 * Description: Initializes the SysTick timer to generate periodic interrupts at a specified frequency.
 * Parameters: Copy_u32TickHZ - The desired tick frequency in Hertz.
 * Return: None
 */
void SysTick_voidInit(uint32_t Copy_u32TickHZ);

/**
 * @brief   Implements a millisecond delay using SysTick.
 * @param   Time: Delay duration in milliseconds (must be > 0).
 * @retval  Error state (OK or NOT_OK).
 * @note    Assumes a system clock of 16 MHz.
 *          0x3E80=16000 == one MilliSecond && Reload = (CLK_DEFAULT_HSI*Time)/1000
 */
uint8_t SysTick_u8DelayMilliSecond(uint32_t Time);

/**
 * @brief   Implements a microsecond delay using SysTick.
 * @param   Time: Delay duration in microseconds (must be > 0).
 * @retval  Error state (OK or NOT_OK).
 * @note    Assumes a system clock of 16 MHz
 *          0x10=16 == one MicroSecond && Reload = (CLK_DEFAULT_HSI*Time)/1000000 .
 */
uint8_t SysTick_u8DelayMicroSecond(uint32_t Time);



#endif /* SYSTICK_INTERFACE_H_ */
