/*
 *  LCD_program.c
 *
 *  Created on: Dec 11, 2024
 *  Author: Ahmed Ragab
 */

/*************************  Includes *************************************/
#include "stm32f401xx.h"
#include "ErrorState.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "SYSTICK_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


/************************  Implementation Function  **********************/

uint8_t LCD_u8Init(void)
{
	uint8_t Local_u8ErrorState=OK;
	SysTick_u8DelayMilliSecond(200);
	/* Initialize control pins as output */
	RCC_AHB1ENABLECLK(PORT_CTRL);
	GPIO_U8PinInit(&(GPIO_PinConfig_t){.Port=PORT_CTRL, .PinNum=RS_PIN, .Mode=OUTPUT , .OutputType = PUSH_PULL});
	GPIO_U8PinInit(&(GPIO_PinConfig_t){.Port=PORT_CTRL, .PinNum=RW_PIN, .Mode=OUTPUT , .OutputType = PUSH_PULL});
	GPIO_U8PinInit(&(GPIO_PinConfig_t){.Port=PORT_CTRL, .PinNum=EN_PIN, .Mode=OUTPUT , .OutputType = PUSH_PULL});
#ifdef EIGHT_BITS_MODE
	uint8_t Count;
	RCC_AHB1ENABLECLK(PORT_DATA);
	for(Count = PIN_START_DATA ; Count < (PIN_START_DATA+8) ; Count++)
	{
		GPIO_U8PinInit(&(GPIO_PinConfig_t){.Port=PORT_DATA, .PinNum=Count, .Mode=OUTPUT , .OutputType = PUSH_PULL});
	}
    LCD_u8SendCmd(FUNCTION_SET_EIGHT_BITS);          /* Function set */
    SysTick_u8DelayMilliSecond(1);
    LCD_u8SendCmd(CLR_SCREEN);                       /* Clear screen */
    SysTick_u8DelayMilliSecond(10);
    LCD_u8SendCmd(CURSOR_ON_DISPLAY_ON);             /* Cursor on, display on */
    SysTick_u8DelayMilliSecond(1);
    LCD_u8SendCmd(ENTRY_MODE);                       /* Set entry mode */
    SysTick_u8DelayMilliSecond(1);
#elif defined FOUR_BITS_MODE
	uint8_t Count;
	RCC_AHB1ENABLECLK(PORT_DATA);
	for (Count = PIN_START_DATA; Count < (PIN_START_DATA + 4); Count++) {
	    GPIO_U8PinInit(&(GPIO_PinConfig_t){.Port = PORT_DATA, .PinNum = Count, .Mode = OUTPUT , .OutputType = PUSH_PULL});
	}
	LCD_u8SendCmd(RETURN_HOME);                     /*4_bits_mode //return home */
	SysTick_u8DelayMilliSecond(2);
    LCD_u8SendCmd(FUNCTION_SET_FOUR_BITS);          /* Function set */
    SysTick_u8DelayMilliSecond(1);
    LCD_u8SendCmd(CLR_SCREEN);                      /* Clear screen */
    SysTick_u8DelayMilliSecond(10);
    LCD_u8SendCmd(CURSOR_ON_DISPLAY_ON);            /* Cursor on, display on */
    SysTick_u8DelayMilliSecond(1);
    LCD_u8SendCmd(ENTRY_MODE);                      /* Set entry mode */
    SysTick_u8DelayMilliSecond(1);
#else
	Local_u8ErrorState=NOT_OK;
#endif
	return Local_u8ErrorState;
}

/**
 * @brief Toggles the Enable (EN) pin to latch data or commands into the LCD.
 */
static void LCD_Enable(void)
{
    GPIO_U8SetPinVal(PORT_CTRL, EN_PIN, HIGH);
    SysTick_u8DelayMilliSecond(2);
    GPIO_U8SetPinVal(PORT_CTRL, EN_PIN, LOW);
    SysTick_u8DelayMilliSecond(2);
}

uint8_t LCD_u8SendCmd(uint8_t Cmd)
{
	uint8_t Local_u8ErrorState=OK;
#ifdef EIGHT_BITS_MODE
	GPIO_U8SetPinVal(PORT_CTRL, RS_PIN, LOW);  /* RS = 0 for command */
	GPIO_U8SetPinVal(PORT_CTRL, RW_PIN, LOW);  /* RW = 0 for write */
	uint8_t Count;
	for(Count = PIN_START_DATA ; Count < (PIN_START_DATA+8) ; Count++)
	{
		GPIO_U8SetPinVal(PORT_DATA, Count, (Cmd >> Count) & ONE);
	}
	LCD_Enable();
	SysTick_u8DelayMilliSecond(1);
#elif defined FOUR_BITS_MODE
	GPIO_U8SetPinVal(PORT_CTRL, RS_PIN, LOW);  /* RS = 0 for command */
	GPIO_U8SetPinVal(PORT_CTRL, RW_PIN, LOW);  /* RW = 0 for write */
	uint8_t Count;
	/* Send the higher nibble */
	for (Count = PIN_START_DATA; Count < (PIN_START_DATA + 4); Count++) {
	    GPIO_U8SetPinVal(PORT_DATA, Count, (Cmd >> (4 + Count - PIN_START_DATA)) & ONE);
	}
	LCD_Enable();
	/* Send the lower nibble */
	for (Count = PIN_START_DATA; Count < (PIN_START_DATA + 4); Count++) {
	    GPIO_U8SetPinVal(PORT_DATA, Count, (Cmd >> (Count - PIN_START_DATA)) & ONE);
	}
	LCD_Enable();
	SysTick_u8DelayMilliSecond(1);
#else
	Local_u8ErrorState=NOT_OK;
#endif
	return Local_u8ErrorState;
}

uint8_t LCD_u8SendData(uint8_t Data)
{
	uint8_t Local_u8ErrorState=OK;
#ifdef EIGHT_BITS_MODE
	GPIO_U8SetPinVal(PORT_CTRL, RS_PIN, HIGH);  /* RS = 1 for data */
	GPIO_U8SetPinVal(PORT_CTRL, RW_PIN, LOW);   /* RW = 0 for write */
	uint8_t Count;
	for(Count = PIN_START_DATA ; Count < (PIN_START_DATA+8) ; Count++)
	{
		GPIO_U8SetPinVal(PORT_DATA, Count, (Data >> Count) & ONE);
	}
	LCD_Enable();
	SysTick_u8DelayMilliSecond(1);
#elif defined FOUR_BITS_MODE
	GPIO_U8SetPinVal(PORT_CTRL, RS_PIN, HIGH);  /* RS = 1 for data */
	GPIO_U8SetPinVal(PORT_CTRL, RW_PIN, LOW);   /* RW = 0 for write */
	uint8_t Count;
	/* Send the higher nibble */
	for (Count = PIN_START_DATA; Count < (PIN_START_DATA + 4); Count++) {
	    GPIO_U8SetPinVal(PORT_DATA, Count, (Data >> (4 + Count - PIN_START_DATA)) & ONE);
	}
	LCD_Enable();
	/* Send the lower nibble */
	for (Count = PIN_START_DATA; Count < (PIN_START_DATA + 4); Count++) {
	    GPIO_U8SetPinVal(PORT_DATA, Count, (Data >> (Count - PIN_START_DATA)) & ONE);
	}
	LCD_Enable();
	SysTick_u8DelayMilliSecond(1);
#else
	Local_u8ErrorState=NOT_OK;
#endif
	return Local_u8ErrorState;
}

uint8_t LCD_u8SendString(const uint8_t *Str)
{
	uint8_t Local_u8ErrorState=OK;
	if(Str != NULL)
	{
	    while (*Str != CLEAR)
	    {
	        LCD_u8SendData(*Str);
	        Str++;
	    }
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

void LCD_VoidClearScreen(void)
{
    LCD_u8SendCmd(CLR_SCREEN);
    SysTick_u8DelayMilliSecond(10);
}

uint8_t LCD_u8MoveCursor(uint8_t Row, uint8_t Coloum)
{
	uint8_t Local_u8ErrorState=OK;
    uint8_t Address;
    if ((Row == FIRST_ROW) && (Coloum <= LAST_COLOUM))
    {
        Address = BAIS_ADDRESS_FIRST_ROW + (Coloum - ONE);
    }
    else if ((Row == SCOND_ROW)  && (Coloum <= LAST_COLOUM))
    {
        Address = BAIS_ADDRESS_SCOND_ROW + (Coloum - ONE);
    }
    else
    {
        Address = BAIS_ADDRESS_FIRST_ROW;  /* Default to row 1, column 1 */
        Local_u8ErrorState=NOT_OK;
    }
    LCD_u8SendCmd(Address);
    return Local_u8ErrorState;
}

