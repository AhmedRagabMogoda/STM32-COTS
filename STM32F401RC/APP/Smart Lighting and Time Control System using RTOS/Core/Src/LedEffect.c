/*
 *  LedEffect.c
 *
 *  Created on: Feb 12, 2025
 *  Author: Ahmed Ragab
 */
#include "main.h"

GPIO_TypeDef* LEDPort[4] = {LED1_PORT,LED2_PORT,LED3_PORT,LED4_PORT};
uint16_t LEDPin[4] = {LED1_PIN,LED2_PIN,LED3_PIN,LED4_PIN};

void LedEffectStop(void)
{
	uint8_t Local_u8Count;
	for(Local_u8Count=0;Local_u8Count<4;Local_u8Count++)
	{
		xTimerStop(HandleLedTimer[Local_u8Count],portMAX_DELAY);
	}
}

void LedEffectStart(uint8_t Copy_u8EffNum)
{
	LedEffectStop();
	xTimerStart(HandleLedTimer[Copy_u8EffNum-1],portMAX_DELAY);
}

void LedEffectAction1(void)
{
	uint8_t Local_u8Count;
	for(Local_u8Count=0;Local_u8Count<4;Local_u8Count++)
	{
		HAL_GPIO_TogglePin(LEDPort[Local_u8Count], LEDPin[Local_u8Count]);
	}
}

void LedEffectAction2(void)
{
	static uint8_t Local_u8Flag=0;
	if(Local_u8Flag==0)
	{
		TurnOnEvenLed();
	}
	else
	{
		TurnOnOddLed();
	}
	Local_u8Flag ^= 1;
}

void LedEffectAction3(void)
{
	/* shift left*/
	static uint8_t Local_u8PinNum=0;
	LedControl(1<<Local_u8PinNum);
	Local_u8PinNum++;
	Local_u8PinNum %=4;
}

void LedEffectAction4(void)
{
	/* shift right */
	static uint8_t Local_u8PinNum=0;
	LedControl(8>>Local_u8PinNum);
	Local_u8PinNum++;
	Local_u8PinNum %=4;
}

void LedControl(uint8_t Copy_u8LedNum)
{
	uint8_t Local_u8Count;
	for(Local_u8Count=0;Local_u8Count<4;Local_u8Count++)
	{
		HAL_GPIO_WritePin(LEDPort[Local_u8Count], LEDPin[Local_u8Count],(Copy_u8LedNum>>Local_u8Count)&1);
	}
}

void TurnOnEvenLed(void)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_RESET);
}

void TurnOnOddLed(void)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_SET);
}


void LedEffectCallBackFun(TimerHandle_t xTimer )
{
	uint8_t Local_u8ID;
	Local_u8ID = pvTimerGetTimerID(xTimer);
	switch(Local_u8ID)
	{
	case 1 : LedEffectAction1(); break;
	case 2 : LedEffectAction2(); break;
	case 3 : LedEffectAction3(); break;
	case 4 : LedEffectAction4(); break;
	}
}
