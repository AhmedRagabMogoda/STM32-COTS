/**
 ******************************************************************************
 * @file           : STM32F401xx Microcontroller - Register Definitions Header File
 * @author         : Ahmed Ragab Mogoda
 * @date           : Nov 25, 2024
 ******************************************************************************
 * @Descriptionr:
 * This header file defines base addresses for peripherals 
 * and structures for registers for STM32F401RC.
 ******************************************************************************
 **/
#ifndef STM32F401XX_H
#define STM32F401XX_H

/*****************  Various Memories Base Addresses  *****************/

#define FLASH_BASE_ADDRESS           0x08000000UL
#define SRAM_BASE_ADDRESS            0x20000000UL
#define ROM_BASE_ADDRESS             0x1FFF0000UL

/*****************  Core Peripheral Base Addresses  *****************/
#define STK_BASE_ADDRESS             0xE000E010UL
#define NVIC_BASE_ADDRESS            0xE000E100UL
#define SCB_BASE_ADDRESS             0xE000ED00UL

/*****************  AHB1 Peripheral Base Addresses  *****************/
#define GPIOA_BASE_ADDRESS           0x40020000UL
#define GPIOB_BASE_ADDRESS           0x40020400UL
#define GPIOC_BASE_ADDRESS           0x40020800UL
#define GPIOD_BASE_ADDRESS           0x40020C00UL
#define GPIOE_BASE_ADDRESS           0x40021000UL
#define GPIOH_BASE_ADDRESS           0x40021C00UL
#define RCC_BASE_ADDRESS             0x40023800UL
#define DMA1_BASE_ADDRESS            0x40026000UL
#define DMA2_BASE_ADDRESS            0x40026400UL

/*****************  AHB2 Peripheral Base Addresses  *****************/


/*****************  AHB3 Peripheral Base Addresses  *****************/


/*****************  APB1 Peripheral Base Addresses  *****************/
#define USART2_BASE_ADDRESS          0x40004400UL
#define SPI2_BASE_ADDRESS            0x40003800UL
#define SPI3_BASE_ADDRESS            0x40003C00UL

/*****************  APB2 Peripheral Base Addresses  *****************/
#define SYSCFG_BASE_ADDRESS          0x40013800UL
#define EXTI_BASE_ADDRESS            0x40013C00UL
#define USART1_BASE_ADDRESS          0x40011000UL
#define USART6_BASE_ADDRESS          0x40011400UL
#define SPI1_BASE_ADDRESS            0x40013000UL
#define SPI4_BASE_ADDRESS            0x40013400UL

/******************  STD Types **************************************/
typedef unsigned char 	        uint8_t;
typedef signed char   	        int8_t;
typedef unsigned short	        uint16_t;
typedef signed short 	        int16_t;
typedef unsigned long 	    	uint32_t;
typedef signed long      		int32_t;
typedef unsigned long long      uint64_t;
typedef signed long long        int64_t;
typedef float                   float32_t;
typedef double                  double64_t;

/******************  Definitions ************************************/
#define NULL                    (void*)0

/****************** RCC Register Definition Structure ***************/
typedef struct {
    volatile uint32_t CR;           // Clock Control Register
    volatile uint32_t PLLCFGR;      // PLL Configuration Register
    volatile uint32_t CFGR;         // Clock Configuration Register
    volatile uint32_t CIR;          // Clock Interrupt Register
    volatile uint32_t AHB1RSTR;     // AHB1 Peripheral Reset Register
    volatile uint32_t AHB2RSTR;     // AHB2 Peripheral Reset Register
    volatile uint32_t Reserved1;    // Reserved space
    volatile uint32_t Reserved2;    // Reserved space
    volatile uint32_t APB1RSTR;     // APB1 Peripheral Reset Register
    volatile uint32_t APB2RSTR;     // APB2 Peripheral Reset Register
    volatile uint32_t Reserved3;    // Reserved space
    volatile uint32_t Reserved4;    // Reserved space
    volatile uint32_t AHB1ENR;      // AHB1 Peripheral Clock Enable Register
    volatile uint32_t AHB2ENR;      // AHB2 Peripheral Clock Enable Register
    volatile uint32_t Reserved5;    // Reserved space
    volatile uint32_t Reserved6;    // Reserved space
    volatile uint32_t APB1ENR;      // APB1 Peripheral Clock Enable Register
    volatile uint32_t APB2ENR;      // APB2 Peripheral Clock Enable Register
    volatile uint32_t Reserved7;    // Reserved space
    volatile uint32_t Reserved8;    // Reserved space
    volatile uint32_t AHB1LPENR;    // AHB1 Low Power Enable Register
    volatile uint32_t AHB2LPENR;    // AHB2 Low Power Enable Register
    volatile uint32_t Reserved9;    // Reserved space
    volatile uint32_t Reserved10;   // Reserved space
    volatile uint32_t APB1LPENR;    // APB1 Low Power Enable Register
    volatile uint32_t APB2LPENR;    // APB2 Low Power Enable Register
    volatile uint32_t Reserved11;   // Reserved space
    volatile uint32_t Reserved12;   // Reserved space
    volatile uint32_t BDCR;         // Backup Domain Control Register
    volatile uint32_t CSR;          // Clock Control & Status Register
    volatile uint32_t Reserved13;   // Reserved space
    volatile uint32_t Reserved14;   // Reserved space
    volatile uint32_t SSCGR;        // Spread Spectrum Clock Generation Register
    volatile uint32_t PLLI2SCFGR;   // PLLI2S Configuration Register
    volatile uint32_t Reserved15;   // Reserved space
    volatile uint32_t DCKCFGR;      // Dedicated Clocks Configuration Register
} RCC_RegDef_t;

/****************** GPIO Register Definition Structure ***************/
typedef struct {
    volatile uint32_t MODER;        // Mode Register
    volatile uint32_t OTYPER;       // Output Type Register
    volatile uint32_t OSPEEDR;      // Output Speed Register
    volatile uint32_t PUPDR;        // Pull-Up/Pull-Down Register
    volatile uint32_t IDR;          // Input Data Register
    volatile uint32_t ODR;          // Output Data Register
    volatile uint32_t BSRR;         // Bit Set/Reset Register
    volatile uint32_t LCKr;         // Configuration Lock Register
    volatile uint32_t AFR[2];       // Alternate Function Registers (Low and High)
} GPIO_RegDef_t;

/****************** SysTick Register Definition Structure ***************/
typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
}STK_RegDef_t;

/****************** NVIC Register Definition Structure ***************/
typedef struct{
	volatile uint32_t ISER[8];
	volatile uint32_t Reserved1[24];
	volatile uint32_t ICER[8];
	volatile uint32_t Reserved2[24];
	volatile uint32_t ISPR[8];
	volatile uint32_t Reserved3[24];
	volatile uint32_t ICPR[8];
	volatile uint32_t Reserved4[24];
	volatile uint32_t IABR[8];
	volatile uint32_t Reserved5[56];
	volatile uint8_t  IPR[240];
	volatile uint32_t Reserved6[580];
	volatile uint32_t STIR;
}NVIC_RegDef_t;

/******************  SCB Register Definition Structure ***************/
typedef struct{
	volatile uint32_t CPUID;
	volatile uint32_t ICSR;
	volatile uint32_t VTOR;
	volatile uint32_t AIRCR;
	volatile uint32_t SCR;
	volatile uint32_t CCR;
	volatile uint32_t SHPR1;
	volatile uint32_t SHPR2;
	volatile uint32_t SHPR3;
	volatile uint32_t SHCSR;
	volatile uint8_t  CFSR;
	volatile uint32_t HFSR;
	volatile uint32_t MMAR;
	volatile uint32_t BFAR;
	volatile uint32_t AFSR;
}SCB_RegDef_t;
/******************  SYSCFG Register Definition Structure ***************/
typedef struct{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t Reserved[2];
	volatile uint32_t CMPCR;
}SYSCFG_RegDef_t;
/******************  EXTI Register Definition Structure ***************/
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegDef_t;

/******************  DMA Register Definition Structure ***************/
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
	volatile uint32_t M0AR;
	volatile uint32_t M1AR;
	volatile uint32_t FCR;
}DMA_Stream_RegDef_t;

typedef struct{
	volatile uint32_t ISR[2];
	volatile uint32_t IFCR[2];
	volatile DMA_Stream_RegDef_t STREAM[8];
}DMA_RegDef_t;

/******************  USART Register Definition Structure ***************/
typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_RegDef_t;

/******************  SPI Register Definition Structure ***************/
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_RegDef_t;

/*****************  RCC Peripheral Definition  ***************************/
#define RCC           ((RCC_RegDef_t*)(RCC_BASE_ADDRESS))

/*****************  GPIO Peripheral Definitions **************************/
#define GPIOA         ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB         ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC         ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD         ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE         ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOH         ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)

/*****************  SysTick Peripheral Definition ****************************/
#define STK           ((STK_RegDef_t*)(STK_BASE_ADDRESS))

/*****************  NVIC Peripheral Definition *******************************/
#define NVIC          ((NVIC_RegDef_t*)NVIC_BASE_ADDRESS)

/*****************  SCB Peripheral Definition ********************************/
#define SCB           ((SCB_RegDef_t*)SCB_BASE_ADDRESS)

/*****************  SYSCFG Peripheral Definition *************************/
#define SYSCFG        ((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)

/*****************  SYSCFG Peripheral Definition *************************/
#define EXTI          ((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)

/*****************  DMA Peripheral Definition  ***************************/
#define DMA1          ((DMA_RegDef_t*)(DMA1_BASE_ADDRESS))
#define DMA2          ((DMA_RegDef_t*)(DMA2_BASE_ADDRESS))

/*****************  USART Peripheral Definitions **************************/
#define USART1         ((USART_RegDef_t*)USART1_BASE_ADDRESS)
#define USART2         ((USART_RegDef_t*)USART2_BASE_ADDRESS)
#define USART6         ((USART_RegDef_t*)USART6_BASE_ADDRESS)

/*****************  SPI Peripheral Definitions **************************/
#define SPI1           ((SPI_RegDef_t*)SPI1_BASE_ADDRESS)
#define SPI2           ((SPI_RegDef_t*)SPI2_BASE_ADDRESS)
#define SPI3           ((SPI_RegDef_t*)SPI3_BASE_ADDRESS)
#define SPI4           ((SPI_RegDef_t*)SPI4_BASE_ADDRESS)

#endif //STM32F401XX_H
