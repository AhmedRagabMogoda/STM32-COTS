/*
 * NVIC_interface.h
 *
 *  Created on: Nov 30, 2024
 *  Author: Ahmed Ragab
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_


/**
 * @brief Enum for STM32F401RC Interrupt Numbers.
 *        This enum defines all the peripheral interrupt numbers as per NVIC table.
 **/
typedef enum {
    WWDG_Interrupt = 0,                /** Window Watchdog Interrupt */
    PVD_Interrupt,                     /** PVD through EXTI Line detection */
    TAMP_STAMP_Interrupt,              /** Tamper and TimeStamp interrupts through EXTI Line */
    RTC_WKUP_Interrupt,                /** RTC Wakeup interrupt through EXTI Line */
    FLASH_Interrupt,                   /** Flash global interrupt */
	RCC_Interrupt,                     /** RCC global interrupt */
    EXTI0_Interrupt,                   /** EXTI Line0 interrupt */
    EXTI1_Interrupt,                   /** EXTI Line1 interrupt */
    EXTI2_Interrupt,                   /** EXTI Line2 interrupt */
    EXTI3_Interrupt,                   /** EXTI Line3 interrupt */
    EXTI4_Interrupt,                   /** EXTI Line4 interrupt */
    DMA1_Stream0_Interrupt,            /** DMA1 Stream0 global interrupt */
    DMA1_Stream1_Interrupt,            /** DMA1 Stream1 global interrupt */
    DMA1_Stream2_Interrupt,            /** DMA1 Stream2 global interrupt */
    DMA1_Stream3_Interrupt,            /** DMA1 Stream3 global interrupt */
    DMA1_Stream4_Interrupt,            /** DMA1 Stream4 global interrupt */
    DMA1_Stream5_Interrupt,            /** DMA1 Stream5 global interrupt */
    DMA1_Stream6_Interrupt,            /** DMA1 Stream6 global interrupt */
    ADC_Interrupt,                     /** ADC1 global interrupt */
    EXTI9_5_Interrupt = 23,            /** EXTI Line[9:5] interrupts */
    TIM1_BRK_TIM9_Interrupt,           /** TIM1 Break interrupt and TIM9 global interrupt */
    TIM1_UP_TIM10_Interrupt,           /** TIM1 Update interrupt and TIM10 global interrupt */
    TIM1_TRG_COM_TIM11_Interrupt,      /** TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
    TIM1_CC_Interrupt,                 /** TIM1 Capture Compare interrupt */
    TIM2_Interrupt,                    /** TIM2 global interrupt */
    TIM3_Interrupt,                    /** TIM3 global interrupt */
    TIM4_Interrupt,                    /** TIM4 global interrupt */
    I2C1_EV_Interrupt,                 /** I2C1 event interrupt */
    I2C1_ER_Interrupt,                 /** I2C1 error interrupt */
    I2C2_EV_Interrupt,                 /** I2C2 event interrupt */
    I2C2_ER_Interrupt,                 /** I2C2 error interrupt */
    SPI1_Interrupt,                    /** SPI1 global interrupt */
    SPI2_Interrupt,                    /** SPI2 global interrupt */
    USART1_Interrupt,                  /** USART1 global interrupt */
    USART2_Interrupt,                  /** USART2 global interrupt */
    EXTI15_10_Interrupt,               /** EXTI Line[15:10] interrupts */
    RTC_Alarm_Interrupt,               /** RTC Alarms (A and B) through EXTI Line */
    OTG_FS_WKUP_Interrupt,             /** USB OTG FS Wakeup through EXTI line */
    DMA1_Stream7_Interrupt,            /** DMA1 Stream7 global interrupt */
    SDIO_Interrupt,                    /** SDIO global interrupt */
    TIM5_Interrupt,                    /** TIM5 global interrupt */
    SPI3_Interrupt_Interrupt,                    /** SPI3 global interrupt */
    DMA2_Stream0_Interrupt,            /** DMA2 Stream0 global interrupt */
    DMA2_Stream1_Interrupt,            /** DMA2 Stream1 global interrupt */
    DMA2_Stream2_Interrupt,            /** DMA2 Stream2 global interrupt */
    DMA2_Stream3_Interrupt,            /** DMA2 Stream3 global interrupt */
    DMA2_Stream4_Interrupt,            /** DMA2 Stream4 global interrupt */
    OTG_FS_Interrupt,                  /** USB OTG FS global interrupt */
    DMA2_Stream5_Interrupt,            /** DMA2 Stream5 global interrupt */
    DMA2_Stream6_Interrupt,            /** DMA2 Stream6 global interrupt */
    DMA2_Stream7_Interrupt,            /** DMA2 Stream7 global interrupt */
    USART6_Interrupt,                  /** USART6 global interrupt */
    I2C3_EV_Interrupt,                 /** I2C3 event interrupt */
    I2C3_ER_Interrupt,                 /** I2C3 error interrupt */
    FPU_Interrupt,                     /** FPU global interrupt */
    SPI4_Interrupt = 84,               /** SPI4 global interrupt */
}Interrupt_t;

typedef enum{
	 ZERO,ONE,TWO,THREE,FOUR,FIVE
}Priority_t;


/*================================================================================================*/
/**
 * *********************************************
 * @brief Enable a specific interrupt in the NVIC.
 * @details Sets the corresponding bit in the Interrupt Set-Enable Register (ISER)
 *          to enable the desired interrupt.
 * @param InterruptNum The interrupt number to be enabled (0-240 depending on the MCU).
 *********************************************
 **/
void NVIC_EnableInterrupt(Interrupt_t InterruptNum);

/**
 * *********************************************
 * @brief Disable a specific interrupt in the NVIC.
 * @details Clears the corresponding bit in the Interrupt Clear-Enable Register (ICER)
 *          to disable the desired interrupt.
 * @param InterruptNum The interrupt number to be disabled (0-240 depending on the MCU).
 ***********************************************
 **/
void NVIC_DisableInterrupt(Interrupt_t InterruptNum);

/**
 * *********************************************
 * @brief Set a pending flag for a specific interrupt.
 * @details Sets the corresponding bit in the Interrupt Set-Pending Register (ISPR),
 *          indicating that the interrupt is pending.
 * @param InterruptNum The interrupt number to set as pending (0-240 depending on the MCU).
 *********************************************
 **/
void NVIC_SETPendingInterrupt(Interrupt_t InterruptNum);

/**
 * *********************************************
 * @brief Clear a pending flag for a specific interrupt.
 * @details Clears the corresponding bit in the Interrupt Clear-Pending Register (ICPR),
 *          removing the pending state of the interrupt.
 * @param InterruptNum The interrupt number to clear from pending (0-240 depending on the MCU).
 *********************************************
**/
void NVIC_CLRPendingInterrupt(Interrupt_t InterruptNum);

/**
 * *********************************************
 * @brief Get the active state of a specific interrupt.
 * @details Checks the corresponding bit in the Interrupt Active Bit Register (IABR),
 *          indicating if the interrupt is active.
 * @param InterruptNum The interrupt number to check the active state (0-240 depending on the MCU).
 * @return uint8_t 1 if the interrupt is active, 0 otherwise.
 *********************************************
 **/
uint8_t NVIC_GetActiveFlagInterrupt(Interrupt_t InterruptNum);

/**
 * *********************************************
 * @brief Set the priority of a specific interrupt.
 * @details Configures the priority of an interrupt by modifying the appropriate field
 *          in the Interrupt Priority Register (IPR).
 * @param InterruptNum The interrupt number to configure (0-240 depending on the MCU).
 * @param Priority The priority value to set (typically 0-15, MCU-specific).
 *********************************************
**/
void NVIC_SETPriorityInterrupt(Interrupt_t InterruptNum,Priority_t Priority);


#endif /* NVIC_INTERFACE_H_ */
