/*
 *  Keypad_program.c
 *
 *  Created on: Dec 13, 2024
 *  Author: Ahmed Ragab
 */

/*************************  Includes *************************************/
#include "stm32f401xx.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "Keypad_interface.h"
#include "Keypad_config.h"
#include "Keypad_private.h"


/************************  Implementation Function  **********************/

void Keypad_VoidInit(void)
{
	uint8_t Count;
	RCC_AHB1ENABLECLK(PORT_ROW);
	RCC_AHB1ENABLECLK(PORT_COLUMN);
	for(Count = PIN_START_ROW ; Count < (PIN_START_ROW+ROWS) ; Count++)
	{
		GPIO_U8PinInit(&(GPIO_PinConfig_t){.Port=PORT_ROW, .PinNum=Count, .Mode=OUTPUT , .OutputType = PUSH_PULL});
	}
	for(Count = PIN_START_COLUMN ; Count < (PIN_START_COLUMN+COLUMNS) ; Count++)
	{
		GPIO_U8PinInit(&(GPIO_PinConfig_t){.Port=PORT_COLUMN, .PinNum=Count, .Mode=INPUT , .PullType = PULL_UP});
	}
}

uint8_t Keypad_u8CheckPress(void)
{
	uint8_t Arr_OutVal[ROWS][COLUMNS] = {{'7', '8', '9', '/'},
                                         {'4', '5', '6', '*'},
                                         {'1', '2', '3', '-'},
                                         {'A', '0', '=', '+'}};
	PinVal_t PinVal=HIGH;
	uint8_t RetVal = NOT_pressed; /* Default value for no key pressed */
	uint8_t Row, Column;
    for (Row = PIN_START_ROW ; Row < (PIN_START_ROW+ROWS) ; Row++)
    {
        /* Set all row pins to HIGH initially */
    	GPIO_U8SetPinVal(PORT_ROW, PIN_START_ROW  , HIGH);
        GPIO_U8SetPinVal(PORT_ROW, PIN_START_ROW+1, HIGH);
        GPIO_U8SetPinVal(PORT_ROW, PIN_START_ROW+2, HIGH);
        GPIO_U8SetPinVal(PORT_ROW, PIN_START_ROW+3, HIGH);
        /* Set the current row pin to LOW */
        GPIO_U8SetPinVal(PORT_ROW, Row, LOW);
        /* Check each column */
        for (Column = PIN_START_COLUMN ; Column < (PIN_START_COLUMN+COLUMNS) ; Column++)
        {
        	GPIO_U8ReadPinVal(PORT_COLUMN, Column , &PinVal);
        	/* If the column pin reads LOW, a key is pressed */
        	if (PinVal == LOW)
        	{
        		RetVal = Arr_OutVal[Row-PIN_START_ROW][Column-PIN_START_COLUMN];
        		break;
        	}
        }
    	if (PinVal == LOW)
    	{
    		break;
    	}
    }
    return RetVal;
}
