/*
 *  Stack_PSP.h
 *
 *  Created on: Nov 28, 2024
 *  Author: Ahmed Ragab
 */

#ifndef STACK_PSP_H_
#define STACK_PSP_H_



/**
 * @brief  Initializes the Process Stack Pointer (PSP) for Thread Mode.
 * @param  None
 * @retval None
 *
 * This function sets up the Process Stack Pointer (PSP), which is used in Thread Mode
 * for application-level tasks. It defines constants for stack pointer configuration,
 * calculates the PSP starting address, and updates the CONTROL register to enable
 * the PSP. It ensures that the processor switches from using the Main Stack Pointer (MSP)
 * to the PSP in Thread Mode, which is critical for applications requiring multitasking or RTOS.
 *
 * @note This function uses naked attribute to prevent automatic stack management
 *       by the compiler.
 **/
void SetUP_PSP(void);

#endif /* STACK_PSP_H_ */
