/*
 * SYSTICK_private.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Ahmed Ragab
 */

#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_

#define HIS_CLK              16000000UL
#define SYSTICK_TIME_CLK     HIS_CLK
#define MACRO_SECOND         1000000u
#define MILLI_SECOND         1000u

#define CTRL_MASK            1u
#define EXCEPTION_PIN_ACCESS 1u
#define CLKSOURCE_PIN_ACCESS 2u
#define ENABLE_PIN_ACCESS    0u
#define COUNTFLAG_PIN_ACCESS 16u
#define CLEAR                0u


/**
 * @brief   Initializes SysTick for polling-based delay.
 * @param   Reload: The reload value for the timer (must be ≤ MAX_VALUE).
 * @note    Uses system clock as the clock source.
 * @retval  None
 */
static void SysTick_VoidPolling(uint32_t Reload);

#endif /* SYSTICK_PRIVATE_H_ */
