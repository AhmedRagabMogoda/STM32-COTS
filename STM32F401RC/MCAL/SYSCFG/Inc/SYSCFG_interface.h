/*
 *  SYSCFG_interface.h
 *
 *  Created on: Dec 3, 2024
 *  Author: Ahmed Ragab
 */

#ifndef SYSCFG_INTERFACE_H_
#define SYSCFG_INTERFACE_H_

typedef enum{
	EXTI_PORTA=0,
	EXTI_PORTB,
	EXTI_PORTC,
	EXTI_PORTD,
	EXTI_PORTE,
	EXTI_PORTH
}SYSCFG_Port_t;

typedef enum{
	EXTI_PIN0=0,
	EXTI_PIN1,
	EXTI_PIN2,
	EXTI_PIN3,
	EXTI_PIN4,
	EXTI_PIN5,
	EXTI_PIN6,
	EXTI_PIN7,
	EXTI_PIN8,
	EXTI_PIN9,
	EXTI_PIN10,
	EXTI_PIN11,
	EXTI_PIN12,
	EXTI_PIN13,
	EXTI_PIN14,
	EXTI_PIN15
}SYSCFG_Pin_t;
/*============================================================================*/
/**
 * @brief Configures the external interrupt (EXTI) port for a given pin.
 *
 * @param Port The SYSCFG port (e.g., GPIOA, GPIOB).
 * @param PinNum The pin number.
**/
void SYSCFG_VoidSetEXTIPort(SYSCFG_Port_t Port, SYSCFG_Pin_t PinNum);

#endif /* SYSCFG_INTERFACE_H_ */
