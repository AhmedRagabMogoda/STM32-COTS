/*
 *  RTC.c
 *
 *  Created on: Feb 12, 2025
 *  Author: Ahmed Ragab
 */
#include "main.h"


void RTC_voidShowTimeDate(void)
{
	RTC_DateTypeDef Local_RTCDate;
	RTC_TimeTypeDef Local_RTCTime;

	static char ShowDate[50];
	static char ShowTime[50];

	char* Local_pData = ShowDate;
	char* Local_pTime = ShowTime;

	char* Local_pTimeformat;

	HAL_RTC_GetTime(&hrtc, &Local_RTCTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &Local_RTCDate,RTC_FORMAT_BIN);

	if(Local_RTCTime.TimeFormat==RTC_HOURFORMAT12_AM)
	{
		 Local_pTimeformat="AM";
	}
	else
	{
		 Local_pTimeformat="PM";
	}

	sprintf((char*)ShowDate,"%s : %02d : %02d : %02d ",
		"\r\ncurrent data",Local_RTCDate.Date,Local_RTCDate.Month,((Local_RTCDate.Year)+2000));
	xQueueSend(Q_Print, &Local_pData, portMAX_DELAY);

	sprintf((char*)ShowTime,"%s : %02d : %02d : %02d [%s]",
			"\r\ncurrent time",Local_RTCTime.Hours,Local_RTCTime.Minutes,Local_RTCTime.Seconds,Local_pTimeformat);
	xQueueSend(Q_Print, &Local_pTime, portMAX_DELAY);
}

void RTC_ConfigTime(uint8_t Copy_u8Hour,uint8_t Copy_u8Min,uint8_t Copy_u8Sec)
{
	RTC_TimeTypeDef Local_RTCTime;
	Local_RTCTime.Hours=Copy_u8Hour;
	Local_RTCTime.Minutes=Copy_u8Min;
	Local_RTCTime.Seconds=Copy_u8Sec;
	HAL_RTC_SetTime(&hrtc, &Local_RTCTime,RTC_FORMAT_BIN);
}

void RTC_ConfigData(uint8_t Copy_u8Day,uint8_t Copy_u8Month,uint8_t Copy_u8Your)
{
	RTC_DateTypeDef Local_RTCDate;
	Local_RTCDate.Date=Copy_u8Day;
	Local_RTCDate.Month=Copy_u8Month;
	Local_RTCDate.Year=Copy_u8Your;
	HAL_RTC_SetDate(&hrtc, &Local_RTCDate,RTC_FORMAT_BIN);
}

uint8_t RTC_u8IsRTCTimeCigValid(uint8_t Copy_u8Hour,uint8_t Copy_u8Min,uint8_t Copy_u8Sec)
{
	uint8_t Local_u8ValidState;
	if((Copy_u8Hour>12) || (Copy_u8Min>59) || (Copy_u8Sec>59))
	{
		Local_u8ValidState=0;
	}
	else
	{
		Local_u8ValidState=1;
	}
	return Local_u8ValidState;
}

uint8_t RTC_u8IsRTCDataCigValid(uint8_t Copy_u8Day,uint8_t Copy_u8Month,uint8_t Copy_u8Your)
{
	uint8_t Local_u8ValidState;
	if((Copy_u8Day>31) || (Copy_u8Month>12) || (Copy_u8Your>99))
	{
		Local_u8ValidState=0;
	}
	else
	{
		Local_u8ValidState=1;
	}
	return Local_u8ValidState;
}



