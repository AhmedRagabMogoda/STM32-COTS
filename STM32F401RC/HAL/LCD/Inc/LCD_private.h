/*
 *  LCD_private.h
 *
 *  Created on: Dec 11, 2024
 *  Author: Ahmed Ragab
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/*********************** LCD Configuration Macros ***********************/
#define CLR_SCREEN               0x01
#define CURSOR_ON_DISPLAY_ON     0x0E
#define CURSOR_OFF_DISPLAY_ON    0x0C
#define RETURN_HOME              0x02
#define ENTRY_MODE               0x06
#define FUNCTION_SET_EIGHT_BITS  0x38  /* 8-bit mode, 2 lines, 5x7 dots */
#define FUNCTION_SET_FOUR_BITS   0x28  /* 4-bit mode, 2 lines, 5x7 dots */

/************************* Configuration Macros ***********************/
#define ONE                      1u
#define CLEAR                    0
#define FIRST_ROW                1u
#define SCOND_ROW                2u
#define LAST_COLOUM              16u
#define BAIS_ADDRESS_FIRST_ROW   0x80
#define BAIS_ADDRESS_SCOND_ROW   0xC0


#endif /* LCD_PRIVATE_H_ */
