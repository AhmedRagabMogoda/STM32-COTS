# Repository Overview

This repository provides firmware and driver code for two STM32 microcontroller targets (STM32F401RC and STM32F103C8).

# The repository Structure

The repository is organized into two main microcontroller targets, each with its own directory and sub‑folders:

```text
.
├── STM32F401RC
│   ├── APP
│   │   ├── Bootloader_APP
│   │   └── Smart Lighting and Time Control
│   ├── HAL
│   │   ├── Keypad
│   │   └── LCD
│   ├── MCAL
│   │   ├── CAN
│   │   ├── CRC
│   │   ├── DMA
│   │   ├── EXTI
│   │   ├── FLASH
│   │   ├── GPIO
│   │   ├── NVIC
│   │   ├── RCC
│   │   ├── SCB
│   │   ├── SPI
│   │   ├── SYSCFG
│   │   ├── SysTick
│   │   ├── UART
│   │   └── Stack_PSP
│   ├── Library
│   │   ├── ErrorState.h
│   │   └── stm32f401xx.h
│   ├── Linkerscript
│   │   └── LinkerScript_stm32f401xx.ld
│   └── Startup
│       └── startup_stm32f401xx.c
└── STM32F103C8
    └── MCAL
        └── CAN
```

---

## 📁 STM32F401RC

Contains the primary application and hardware abstraction layers for the STM32F401RC MCU.

- **APP**
  - `Bootloader_APP`: Bootloader implementation for firmware updates.
  - `Smart Lighting and Time Control`: Example user application.

- **HAL** (Hardware Abstraction Layer)
  - `Keypad`: Driver for keypad input.
  - `LCD`: Driver for LCD display control.

- **MCAL** (Microcontroller Abstraction Layer)
   - `CRC`: Cyclic Redundancy Check peripheral driver.
   - `DMA`: Direct Memory Access driver.
   - `EXTI`: External Interrupt configuration.
   - `FLASH`: Internal flash programming driver.
   - `GPIO`: General Purpose I/O driver.
   - `NVIC`: Nested Vectored Interrupt Controller.
   - `RCC`: Reset and Clock Control.
   - `SCB`: System Control Block settings.
   - `SPI`: Serial Peripheral Interface driver.
   - `SYSCFG`: System Configuration Controller.
   - `SysTick`: System tick timer management.
   - `UART`: UART/USART serial communication.
   - `Stack_PSP`: Stack Pointer related configurations.

- **Library**
  - `ErrorState.h`: Common error status definitions.
  - `stm32f401xx.h`: Device header.

- **Linkerscript**
  - `LinkerScript_stm32f401xx.ld`: Memory mapping script.

- **Startup**
  - `startup_stm32f401xx.c`: Vector table and reset handler.

---

## 📁 STM32F103C8

Contains the primary application and hardware abstraction layers for the STM32F103C8 MCU.

- **MCAL**
  - `CAN`: Controller Area Network peripheral driver.

---
