/*
 *  SCB_program.c
 *
 *  Created on: Nov 30, 2024
 *  Author: Ahmed Ragab
 */
#include "stm32f401xx.h"
#include "SCB_private.h"
#include "SCB_interface.h"

void SCB_SetPriorityGroup(PriorityGroup_t PriorityGroup)
{
    SCB->AIRCR =(VECTKEY << VECTKEY_PIN_ACCESS) | (PriorityGroup << PRIGROUP_PIN_ACCESS);
}

void SCB_EnableMemoryManagementFault(void)
{
    SCB->SHCSR |= (SHCSR_MASK << MEMFAULT_ENABLE);
}

void SCB_EnableBusFault(void)
{
    SCB->SHCSR |= (SHCSR_MASK << BUSFAULT_ENABLE);
}

void SCB_EnableUsageFault(void)
{
    SCB->SHCSR |= (SHCSR_MASK << USGFAULT_ENABLE);
}

void HardFault_Handler(void)
{
	while(1);
}

void MemManage_Handler(void)
{
	while(1);
}

void BusFault_Handler(void)
{
	while(1);
}

void UsageFault_Handler(void)
{
	while(1);
}