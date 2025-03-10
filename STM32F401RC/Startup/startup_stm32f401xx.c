/**
 * @file   : startup.c
 * @author : Ahmed Ragab Mogoda
 * @date   : 2025-01-04
 * @brief  : Startup code and vector table for ARM Cortex-M microcontroller.
 *
 * This file contains the startup code, vector table, and memory initialization
 * required to boot an ARM Cortex-M application.
 */

#include <stdint.h>

#define SRAM_START      0x20000000U
#define SRAM_SIZE       (128 * 1024)  /* 128 KB SRAM */
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))
#define STACK_START     SRAM_END

extern uint32_t _erodata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void main (void);

/* Function prototypes for interrupt handlers */
void Reset_Handler(void);
void Default_Handler(void);

/* Weak aliases for all interrupt handlers */
void NMI_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)               __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)           __attribute__((weak, alias("Default_Handler")));

/* Peripheral interrupt handlers */
void WWDG_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void ADC_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void SDIO_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void USART6_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void FPU_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void SPI4_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));

/* Vector table */
uint32_t Vectors[] __attribute__((section(".isr_vector"))) = 
{
    STACK_START,                      /* Initial stack pointer */
    (uint32_t)&Reset_Handler,         /* Reset handler */
    (uint32_t)&NMI_Handler,           /* NMI handler */
    (uint32_t)&HardFault_Handler,     /* Hard fault handler */
    (uint32_t)&MemManage_Handler,     /* Memory management fault handler */
    (uint32_t)&BusFault_Handler,      /* Bus fault handler */
    (uint32_t)&UsageFault_Handler,    /* Usage fault handler */
    0,                                /* Reserved */
    0,                                /* Reserved */
    0,                                /* Reserved */
    0,                                /* Reserved */
    (uint32_t)&SVC_Handler,           /* SVCall handler */
    (uint32_t)&DebugMon_Handler,      /* Debug monitor handler */
    0,                                /* Reserved */
    (uint32_t)&PendSV_Handler,        /* PendSV handler */
    (uint32_t)&SysTick_Handler,       /* SysTick handler */

    /* Peripheral interrupt handlers */
    (uint32_t)&WWDG_IRQHandler,       /* Window Watchdog interrupt */
    (uint32_t)&PVD_IRQHandler,        /* PVD through EXTI Line detection interrupt */
    (uint32_t)&TAMP_STAMP_IRQHandler, /* Tamper and TimeStamp interrupts */
    (uint32_t)&RTC_WKUP_IRQHandler,   /* RTC Wakeup interrupt */
    (uint32_t)&FLASH_IRQHandler,      /* Flash global interrupt */
    (uint32_t)&RCC_IRQHandler,        /* RCC global interrupt */
    (uint32_t)&EXTI0_IRQHandler,      /* EXTI Line 0 interrupt */
    (uint32_t)&EXTI1_IRQHandler,      /* EXTI Line 1 interrupt */
    (uint32_t)&EXTI2_IRQHandler,      /* EXTI Line 2 interrupt */
    (uint32_t)&EXTI3_IRQHandler,      /* EXTI Line 3 interrupt */
    (uint32_t)&EXTI4_IRQHandler,      /* EXTI Line 4 interrupt */
    (uint32_t)&DMA1_Stream0_IRQHandler, /* DMA1 Stream 0 global interrupt */
    (uint32_t)&DMA1_Stream1_IRQHandler, /* DMA1 Stream 1 global interrupt */
    (uint32_t)&DMA1_Stream2_IRQHandler, /* DMA1 Stream 2 global interrupt */
    (uint32_t)&DMA1_Stream3_IRQHandler, /* DMA1 Stream 3 global interrupt */
    (uint32_t)&DMA1_Stream4_IRQHandler, /* DMA1 Stream 4 global interrupt */
    (uint32_t)&DMA1_Stream5_IRQHandler, /* DMA1 Stream 5 global interrupt */
    (uint32_t)&DMA1_Stream6_IRQHandler, /* DMA1 Stream 6 global interrupt */
    (uint32_t)&ADC_IRQHandler,         /* ADC1 global interrupt */
    (uint32_t)&EXTI9_5_IRQHandler,     /* External Line[9:5] interrupts */
    (uint32_t)&TIM1_BRK_TIM9_IRQHandler, /* TIM1 Break interrupt and TIM9 global interrupt */
    (uint32_t)&TIM1_UP_TIM10_IRQHandler, /* TIM1 Update interrupt and TIM10 global interrupt */
    (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler, /* TIM1 Trigger/Commutation interrupts and TIM11 global interrupt */
    (uint32_t)&TIM1_CC_IRQHandler,     /* TIM1 Capture Compare interrupt */
    (uint32_t)&TIM2_IRQHandler,        /* TIM2 global interrupt */
    (uint32_t)&TIM3_IRQHandler,        /* TIM3 global interrupt */
    (uint32_t)&TIM4_IRQHandler,        /* TIM4 global interrupt */
    (uint32_t)&I2C1_EV_IRQHandler,     /* I2C1 event interrupt */
    (uint32_t)&I2C1_ER_IRQHandler,     /* I2C1 error interrupt */
    (uint32_t)&I2C2_EV_IRQHandler,     /* I2C2 event interrupt */
    (uint32_t)&I2C2_ER_IRQHandler,     /* I2C2 error interrupt */
    (uint32_t)&SPI1_IRQHandler,        /* SPI1 global interrupt */
    (uint32_t)&SPI2_IRQHandler,        /* SPI2 global interrupt */
    (uint32_t)&USART1_IRQHandler,      /* USART1 global interrupt */
    (uint32_t)&USART2_IRQHandler,      /* USART2 global interrupt */
    (uint32_t)&USART3_IRQHandler,      /* USART3 global interrupt */
    (uint32_t)&EXTI15_10_IRQHandler,   /* External Line[15:10] interrupts */
    (uint32_t)&RTC_Alarm_IRQHandler,   /* RTC Alarm (A and B) through EXTI Line interrupt */
    (uint32_t)&OTG_FS_WKUP_IRQHandler, /* USB OTG FS Wakeup through EXTI Line interrupt */
    (uint32_t)&DMA1_Stream7_IRQHandler, /* DMA1 Stream 7 global interrupt */
    (uint32_t)&SDIO_IRQHandler,        /* SDIO global interrupt */
    (uint32_t)&TIM5_IRQHandler,        /* TIM5 global interrupt */
    (uint32_t)&SPI3_IRQHandler,        /* SPI3 global interrupt */
    (uint32_t)&DMA2_Stream0_IRQHandler, /* DMA2 Stream 0 global interrupt */
    (uint32_t)&DMA2_Stream1_IRQHandler, /* DMA2 Stream 1 global interrupt */
    (uint32_t)&DMA2_Stream2_IRQHandler, /* DMA2 Stream 2 global interrupt */
    (uint32_t)&DMA2_Stream3_IRQHandler, /* DMA2 Stream 3 global interrupt */
    (uint32_t)&DMA2_Stream4_IRQHandler, /* DMA2 Stream 4 global interrupt */
    (uint32_t)&OTG_FS_IRQHandler,      /* USB OTG FS global interrupt */
    (uint32_t)&DMA2_Stream5_IRQHandler, /* DMA2 Stream 5 global interrupt */
    (uint32_t)&DMA2_Stream6_IRQHandler, /* DMA2 Stream 6 global interrupt */
    (uint32_t)&DMA2_Stream7_IRQHandler, /* DMA2 Stream 7 global interrupt */
    (uint32_t)&USART6_IRQHandler,      /* USART6 global interrupt */
    (uint32_t)&I2C3_EV_IRQHandler,     /* I2C3 event interrupt */
    (uint32_t)&I2C3_ER_IRQHandler,     /* I2C3 error interrupt */
    (uint32_t)&FPU_IRQHandler,         /* FPU global interrupt */
    (uint32_t)&SPI4_IRQHandler         /* SPI4 global interrupt */
};

void Reset_Handler(void)
{
	/* 1- copy .data section from FLASH to SRAM */
	uint32_t Size = (uint32_t)&_edata - (uint32_t)&_sdata;
	uint8_t* SrcPtr = (uint8_t*)&_erodata;
	uint8_t* DestPtr = (uint8_t*)&_sdata;
	uint32_t Count;
	for(Count=0 ; Count<Size ; Count++)
	{
		*DestPtr = *SrcPtr;
		DestPtr++;
		SrcPtr++;
	}
	/* 2- initialise .bss section in SRAM to zero */
	Size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	DestPtr = (uint8_t*)&_sbss;
	for(Count=0 ; Count<Size ; Count++)
	{
		*DestPtr = 0u;
		DestPtr++;
	}
	/* 3- call init function of standard library */

	/* 4- call main */
	main();
	while(1);
}


void Default_Handler(void)
{
	while(1);
}
