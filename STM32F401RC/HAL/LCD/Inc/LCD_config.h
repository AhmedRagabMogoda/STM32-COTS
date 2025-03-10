/*
 *  LCD_config.h
 *
 *  Created on: Dec 11, 2024
 *  Author: Ahmed Ragab
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define FOUR_BITS_MODE                   /* Mode is EIGHT_BITS_MODE or FOUR_BITS_MODE */
#define PORT_CTRL         PORTA          /* Control port */
#define PORT_DATA         PORTA          /* Data port */
#define PIN_START_DATA    PIN0           /* First Pin to send data */
#define RS_PIN            PIN8           /* Register Select pin */
#define RW_PIN            PIN9           /* Read/Write pin */
#define EN_PIN            PIN10          /* Enable pin */

#endif /* LCD_CONFIG_H_ */
