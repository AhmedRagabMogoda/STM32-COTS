/*
 *  TaskHandlers.c
 *
 *  Created on: Feb 11, 2025
 *  Author: Ahmed Ragab Mogoda
 */

#include "main.h"

#define HH_STATE    0
#define MM_STATE    1
#define SS_STATE    2

#define DAY_STATE    0
#define MONTH_STATE  1
#define YOUR_STATE   2

static void proccessCMD(Command_t* Copy_Command);
static void ExtractCommand(Command_t* Copy_Command);

const char* MsgInvaild = "-------> invaild Option <--------\r\n ";

void MenuTask(void * pvParameters)
{
	const char* MsgMenu = "\r\n======================================\r\n"
			           "                Menu                  \r\n"
	                   "======================================\r\n"
	                   "Led Effect       ------------> 0      \r\n"
                       "Data and Time    ------------> 1      \r\n"
                       "Exit             ------------> 2      \r\n"
                       "Enter your choose here : ";
	Command_t* Local_CMD;
	uint32_t Local_u32CmdAddress;
	while(1)
	{
		xQueueSend(Q_Print,(void*)&MsgMenu,portMAX_DELAY);

		xTaskNotifyWait(0,0,&Local_u32CmdAddress,portMAX_DELAY);
		Local_CMD = (Command_t*)Local_u32CmdAddress;

		if(Local_CMD->Len == 1)
		{
			switch(Local_CMD->Payload[0])
			{
			case '0': Current_State=LedEffectState; xTaskNotify(HandleLedTask,0,eNoAction); break;
			case '1': Current_State=RTCMenuState;   xTaskNotify(HandleRTCTask,0,eNoAction); break;
			case '2': break;
			default : xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY); continue;
			}
		}
		else
		{
			xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
			continue;
		}
		/* wait to run again*/
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
	}
}
void CMDTask(void * pvParameters)
{
	BaseType_t Local_RetVal;
	Command_t CMD;
	while(1)
	{
		Local_RetVal = xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		if(Local_RetVal == pdTRUE)
		{
			proccessCMD(&CMD);
		}
	}
}

static void proccessCMD(Command_t* Copy_Command)
{
	ExtractCommand(Copy_Command);

	switch(Current_State)
	{
	case MainMenuState   : xTaskNotify(HandleMenuTask,(uint32_t)Copy_Command,eSetValueWithOverwrite); break;
	case LedEffectState  : xTaskNotify(HandleLedTask,(uint32_t)Copy_Command,eSetValueWithOverwrite); break;
	case RTCDataCfgState :
	case RTCTimeCfgState :
	case RTCMenuState    :
		xTaskNotify(HandleRTCTask,(uint32_t)Copy_Command,eSetValueWithOverwrite); break;
	default: break;
	}
}

static void ExtractCommand(Command_t* Copy_Command)
{
	UBaseType_t Local_NumberOfMessages;
	uint8_t u8Loop;
	Local_NumberOfMessages = uxQueueMessagesWaiting(Q_Data);
	for(u8Loop=0;u8Loop<Local_NumberOfMessages;u8Loop++)
	{
		xQueueReceive(Q_Data,(void*)&Copy_Command->Payload[u8Loop],0);
		if((char)Copy_Command->Payload[u8Loop]=='\r')
		{
			break;
		}
	}
	Copy_Command->Payload[u8Loop]='\0';
	Copy_Command->Len = u8Loop;
}

void LedTask(void * pvParameters)
{
	const char* MsgLedEffect = "\r\n======================================\r\n"
							   "                Menu                  \r\n"
	                  	       "======================================\r\n"
	                   	       "( none , e1 , e2 , e3 , e4 )          \r\n"
			                   "Enter your choose here : ";
	Command_t* Local_CMD;
	uint32_t Local_u32CmdAddress;
	while(1)
	{
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

		xQueueSend(Q_Print,(void*)&MsgLedEffect,portMAX_DELAY);

		xTaskNotifyWait(0,0,&Local_u32CmdAddress,portMAX_DELAY);
		Local_CMD = (Command_t*)Local_u32CmdAddress;
		if(Local_CMD->Len <= 4)
		{
			if(strcmp((char*)Local_CMD->Payload,"none") == 0)
			{
				LedEffectStop();
			}
			else if(strcmp((char*)Local_CMD->Payload,"e1") == 0)
			{
				LedEffectStart(1);
			}
			else if(strcmp((char*)Local_CMD->Payload,"e2") == 0)
			{
				LedEffectStart(2);
			}
			else if(strcmp((char*)Local_CMD->Payload,"e3") == 0)
			{
				LedEffectStart(3);
			}
			else if(strcmp((char*)Local_CMD->Payload,"e4") == 0)
			{
				LedEffectStart(4);
			}
			else
			{
				xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
			}
		}
		else
		{
			xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
		}
		Current_State = MainMenuState;
		xTaskNotify(HandleMenuTask,0,eNoAction);
	}
}

void RTCTask(void * pvParameters)
{
	const char* MsgRTC1 = "\r\n======================================\r\n"
					   "                Menu                  \r\n"
		               "======================================\r\n";
	const char* MsgRTC2 =
			"\r\n\nconfige time     ------------>0\r\n"
			"confige data       ------------>1\r\n"
			"enable reporting   ------------>2\r\n"
			"Exit               ------------>3\r\n"
			"Enter your choose here : ";
	const char* MsgRTCHour = "\r\nEnter the Hour(1 - 12) : ";
	const char* MsgRTCMin = "\r\nEnter the Minutes(0 - 59) : ";
	const char* MsgRTCSec = "\r\nEnter the Second(0 - 59) : ";
	const char* MsgRTCDay = "\r\nEnter the day(1 - 31) : ";
	const char* MsgRTCMonth = "\r\nEnter the month(1 - 12) : ";
	const char* MsgRTCYour = "\r\nEnter the Your(0 - 99) : ";
	const char* MsgRTCConfigSuccess = "\r\nConfiguration Successful\r\n";
	const char* MsgRTCEnReporting = "\r\nEnable time & data reporting [y/n]\r\n";
	Command_t* Local_CMD;
	uint32_t Local_u32CmdAddress;
	static uint8_t RTCCfgState=0;
	uint8_t Local_u8Hour,Local_u8Min,Local_u8Sec;
	uint8_t Local_u8Day,Local_u8Month,Local_u8Your;
	while(1)
	{
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		xQueueSend(Q_Print,&MsgRTC1,portMAX_DELAY);
		RTC_voidShowTimeDate();
		xQueueSend(Q_Print,&MsgRTC2,portMAX_DELAY);

		while(Current_State != MainMenuState)
		{
			xTaskNotifyWait(0,0,&Local_u32CmdAddress,portMAX_DELAY);
			Local_CMD=(Command_t*)Local_u32CmdAddress;
			switch(Current_State)
			{
			case RTCMenuState :
				if(Local_CMD->Len == 1)
				{
					switch(Local_CMD->Payload[0])
					{
					case '0': Current_State = RTCTimeCfgState; xQueueSend(Q_Print,&MsgRTCHour,portMAX_DELAY); break;
					case '1': Current_State = RTCDataCfgState; xQueueSend(Q_Print,&MsgRTCDay,portMAX_DELAY); break;
					case '2': Current_State = RTCReportstate;  xQueueSend(Q_Print,&MsgRTCEnReporting,portMAX_DELAY); break;
					case '3': Current_State = MainMenuState; break;
					default :
						Current_State = MainMenuState;
						xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
						break;
					}
				}
				else
				{
					Current_State = MainMenuState;
					xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
				}
				break;

			case RTCTimeCfgState :
				if(Local_CMD->Len <= 2)
				{
					switch(RTCCfgState)
					{
					case HH_STATE :
						Local_u8Hour = u8GetNumber((char*)Local_CMD->Payload,Local_CMD->Len);
						xQueueSend(Q_Print,(void*)&MsgRTCMin,portMAX_DELAY);
						RTCCfgState = MM_STATE;
						break;
					case MM_STATE :
						Local_u8Min = u8GetNumber((char*)Local_CMD->Payload,Local_CMD->Len);
						xQueueSend(Q_Print,(void*)&MsgRTCSec,portMAX_DELAY);
						RTCCfgState = SS_STATE;
						break;
					case SS_STATE :
						Local_u8Sec = u8GetNumber((char*)Local_CMD->Payload,Local_CMD->Len);
						if(RTC_u8IsRTCTimeCigValid(Local_u8Hour,Local_u8Min,Local_u8Sec))
						{
							RTC_ConfigTime(Local_u8Hour,Local_u8Min,Local_u8Sec);
							xQueueSend(Q_Print,(void*)&MsgRTCConfigSuccess,portMAX_DELAY);
							RTC_voidShowTimeDate();
						}
						else
						{
							xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
						}
						RTCCfgState =0;
						Current_State = MainMenuState;
						break;
					}
				}
				else
				{
					Current_State = MainMenuState;
					xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
				}
				break;

			case RTCDataCfgState :
				if(Local_CMD->Len <= 2)
				{
					switch(RTCCfgState)
					{
					case DAY_STATE :
						Local_u8Day = u8GetNumber((char*)Local_CMD->Payload,Local_CMD->Len);
						xQueueSend(Q_Print,(void*)&MsgRTCMonth,portMAX_DELAY);
						RTCCfgState = MONTH_STATE;
						break;
					case MONTH_STATE :
						Local_u8Month = u8GetNumber((char*)Local_CMD->Payload,Local_CMD->Len);
						xQueueSend(Q_Print,(void*)&MsgRTCYour,portMAX_DELAY);
						RTCCfgState = YOUR_STATE;
						break;
					case YOUR_STATE :
						Local_u8Your = u8GetNumber((char*)Local_CMD->Payload,Local_CMD->Len);
						if(RTC_u8IsRTCDataCigValid(Local_u8Day,Local_u8Month,Local_u8Your))
						{
							RTC_ConfigData(Local_u8Day,Local_u8Month,Local_u8Your);
							xQueueSend(Q_Print,(void*)&MsgRTCConfigSuccess,portMAX_DELAY);
							RTC_voidShowTimeDate();
						}
						else
						{
							xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
						}
						RTCCfgState =0;
						Current_State = MainMenuState;
						break;
					}
				}
				else
				{
					Current_State = MainMenuState;
					xQueueSend(Q_Print,(void*)&MsgInvaild,portMAX_DELAY);
				}
				break;
			}
		}
		xTaskNotify(HandleMenuTask,0,eNoAction);
	}
}

uint8_t u8GetNumber(const char* Copy_ASCILNum,uint8_t Copy_u8Len)
{
	uint8_t Local_u8DecimalNum;
	if(Copy_u8Len == 1)
	{
		Local_u8DecimalNum = Copy_ASCILNum[0]-'0';
	}
	else if(Copy_u8Len == 2)
	{
		Local_u8DecimalNum = (Copy_ASCILNum[0]-'0')*10 + (Copy_ASCILNum[1]-'0');
	}
	else
	{

	}
	return Local_u8DecimalNum;
}

void PrintTask(void * pvParameters)
{
	uint32_t* local_pu32Msg;
	while(1)
	{
		xQueueReceive(Q_Print, &local_pu32Msg, portMAX_DELAY);
		HAL_UART_Transmit(&huart6, (uint8_t*)local_pu32Msg,strlen((char*)local_pu32Msg), HAL_MAX_DELAY);
	}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if( ! xQueueIsQueueFullFromISR(Q_Data))
	{
		/* Queue is not full */
		xQueueSendFromISR(Q_Data,(void*)&UserData,NULL);

	}
	else
	{
		/* Queue is full */
		if(UserData=='\r')
		{
			//uint8_t DUMMY;
			//xQueueReceiveFromISR(Q_Data,(void*)&DUMMY,NULL);
			//xQueueSendFromISR(Q_Data,(void*)&UserData,NULL);
			xQueueOverwriteFromISR(Q_Data,(void*)&UserData,NULL);
		}
		else
		{
			/* ignore the data */
		}
	}
	if(UserData=='\r')
	{
		/* command is finished */
		xTaskNotifyFromISR(HandleCMDTask,0,eNoAction,NULL);
	}
	/* enable uart receving in interrupt mode */
	  HAL_UART_Receive_IT(&huart6,(uint8_t *)&UserData, 1);
}
