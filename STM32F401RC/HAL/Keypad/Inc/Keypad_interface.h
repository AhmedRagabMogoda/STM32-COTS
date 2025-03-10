/*
 * Keypad_interface.h
 *
 *  Created on: Dec 13, 2024
 *      Author: Ahmed Ragab
 */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_



#define NOT_pressed    0xff


/**
 * @brief Initializes the keypad hardware.
 * Configures row pins as outputs and column pins as inputs with pull-up resistors.
 */
void Keypad_VoidInit(void);

/**
 * @brief Checks which key is pressed on the keypad.
 * This function scans the keypad by activating one row at a time
 * and reading the column pins to determine the pressed key.
 *
 * @return uint8_t The ASCII value of the pressed key or `NOT_pressed` if no key is pressed.
 */
uint8_t Keypad_u8CheckPress(void);



#endif /* KEYPAD_INTERFACE_H_ */
