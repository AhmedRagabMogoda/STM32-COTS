/*
 *  LCD_interface.h
 *
 *  Created on: Dec 11, 2024
 *  Author: Ahmed Ragab
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/**
 * @brief Initializes the LCD in either 4-bit or 8-bit mode.
 *        Configures control and data pins, and sends initial commands to prepare the LCD.
 * @return uint8_t OK if successful, NOT_OK if an error occurs.
 */
uint8_t LCD_u8Init(void);

/**
 * @brief Sends a command to the LCD in either 4-bit or 8-bit mode.
 * @param Cmd Command to send to the LCD.
 * @return uint8_t OK if successful, NOT_OK if an error occurs.
 */
uint8_t LCD_u8SendCmd(uint8_t Cmd);

/**
 * @brief Sends data (characters) to the LCD for display.
 * @param Data Data byte to send.
 * @return uint8_t OK if successful, NOT_OK if an error occurs.
 */
uint8_t LCD_u8SendData(uint8_t Data);

/**
 * @brief Sends a string to the LCD for display.
 * @param Str Pointer to the string to send.
 * @return uint8_t OK if successful, NULL_PTR_ERR if the string pointer is NULL.
 */
uint8_t LCD_u8SendString(const uint8_t *Str);

/**
 * @brief Clears the LCD screen by sending the clear command.
 */
void LCD_VoidClearScreen(void);

/**
 * @brief Moves the cursor to a specific position on the LCD.
 * @param Row Row number (e.g., FIRST_ROW, SCOND_ROW).
 * @param Coloum Column number.
 * @return uint8_t OK if successful, NOT_OK if the position is invalid.
 */
uint8_t LCD_u8MoveCursor(uint8_t Row, uint8_t Coloum);

#endif /* LCD_INTERFACE_H_ */
