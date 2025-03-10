/*
 *  Stack_PSP.c
 *
 *  Created on: Nov 28, 2024
 *  Author: Ahmed Ragab
 */
#include "stm32f401xx.h"

__attribute__((naked)) void SetUP_PSP(void)
{
    /* Define a constant in assembly. */
    __asm volatile (".equ ENABLE_PSP, 0x02");
    __asm volatile (".equ SRAM_END, (0x20000000U + (128*1024))");
    __asm volatile (".equ PSP_END, (SRAM_END - 512)");
    /* Load the End PSP Address into the PSP register (Process Stack Pointer). */
    __asm volatile ("LDR R0, =PSP_END");
    __asm volatile ("MSR PSP, R0");
    /* Set the CONTROL register to switch to PSP for Thread Mode.
       CONTROL[1] = 1: Use PSP instead of MSP for stack operations. */
    __asm volatile ("LDR R0, =ENABLE_PSP");
    __asm volatile ("MSR CONTROL, R0");
    /* Return from the function by branching to the address in the Link Register (LR). */
    __asm volatile ("bx LR");
}
