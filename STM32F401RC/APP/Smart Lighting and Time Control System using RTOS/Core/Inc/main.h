/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "SEGGER_SYSVIEW.h"
#include "task.h"
#include "queue.h"
#include <string.h>
#include <stdio.h>
#include "timers.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct{
	uint8_t Payload[10];
	uint8_t Len;
}Command_t;

typedef enum{
	MainMenuState,
	LedEffectState,
	RTCMenuState,
	RTCTimeCfgState,
	RTCDataCfgState,
	RTCReportstate
}State_t;

extern TaskHandle_t HandleMenuTask;
extern TaskHandle_t HandleCMDTask;
extern TaskHandle_t HandleLedTask;
extern TaskHandle_t HandleRTCTask;
extern TaskHandle_t HandlePrintTask;

extern QueueHandle_t Q_Print;
extern QueueHandle_t Q_Data;

extern State_t Current_State;
extern volatile char UserData;

extern TimerHandle_t HandleLedTimer[4];

extern RTC_HandleTypeDef hrtc;

extern UART_HandleTypeDef huart6;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

void LedEffectStop(void);
void LedEffectStart(uint8_t Copy_u8EffNum);
void LedEffectCallBackFun(TimerHandle_t xTimer );
void LedEffectAction1(void);
void LedEffectAction2(void);
void LedEffectAction3(void);
void LedEffectAction4(void);
void LedControl(uint8_t Copy_u8LedNum);
void TurnOnEvenLed(void);
void TurnOnOddLed(void);
void RTC_voidShowTimeDate(void);
void RTC_ConfigTime(uint8_t Copy_u8Hour,uint8_t Copy_u8Min,uint8_t Copy_u8Sec);
void RTC_ConfigData(uint8_t Copy_u8Day,uint8_t Copy_u8Month,uint8_t Copy_u8Your);
uint8_t RTC_u8IsRTCTimeCigValid(uint8_t Copy_u8Hour,uint8_t Copy_u8Min,uint8_t Copy_u8Sec);
uint8_t RTC_u8IsRTCDataCigValid(uint8_t Copy_u8Hour,uint8_t Copy_u8Min,uint8_t Copy_u8Sec);
uint8_t u8GetNumber(const char* Copy_ASCILNum,uint8_t Copy_u8Len);


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

#define DWT_CTRL  *((volatile uint32_t*)0xE0001000)

#define LED1_PORT  GPIOC
#define LED2_PORT  GPIOC
#define LED3_PORT  GPIOC
#define LED4_PORT  GPIOC

#define LED1_PIN  GPIO_PIN_6
#define LED2_PIN  GPIO_PIN_7
#define LED3_PIN  GPIO_PIN_8
#define LED4_PIN  GPIO_PIN_9

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
