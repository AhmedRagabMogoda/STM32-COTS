/*
 *  GPIO_interface.h
 *
 *  Created on: Nov 25, 2024
 *  Author: Ahmed Ragab
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef enum{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTH=7
}Port_t;

typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}Pin_t;

typedef enum{
	LOW=0,
	HIGH
}PinVal_t;

typedef enum{
	INPUT=0,
	OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
}Mode_t;

typedef enum{
	PUSH_PULL=0,
	OPEN_DRAIN
}OutputType_t;

typedef enum{
	LOW_SPEED=0,
	MEDIUM_SPEED,
	HIGH_SPEED,
    VERY_HIGH_SPEED
}OutputSpeed_t;

typedef enum{
	NOPULL=0,
	PULL_UP,
	PULL_DOWN
}PullUpDown_t;

typedef enum{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}AltFunc_t;


typedef struct{
	Port_t Port;
	Pin_t PinNum;
	Mode_t Mode;
	OutputSpeed_t Speed;
	OutputType_t OutputType;
	PullUpDown_t PullType;
	AltFunc_t AltFunc;
}GPIO_PinConfig_t;

/*================================= Function Declaration ===========================================*/

/**
 * @brief Initializes a GPIO pin based on the provided configuration.
 * @param PinConfig Pointer to the configuration structure.
 * @return Status of the operation (OK, NOT_OK, or NULL_PTR_ERR).
 **/
uint8_t GPIO_U8PinInit(const GPIO_PinConfig_t * PinConfig);

/**
 * @brief Sets the value of a GPIO pin.
 * @param Port GPIO port (A-H).
 * @param PinNum GPIO pin number (0-15).
 * @param PinVal Value to set (HIGH or LOW).
 * @return Status of the operation (OK or NOT_OK).
 **/
uint8_t GPIO_U8SetPinVal(Port_t Port,Pin_t PinNum,PinVal_t PinVal);

/**
 * @brief Toggles the value of a GPIO pin.
 * @param Port GPIO port (A-H).
 * @param PinNum GPIO pin number (0-15).
 * @return Status of the operation (OK or NOT_OK).
 **/
uint8_t GPIO_U8TogglePinVal(Port_t Port,Pin_t PinNum);

/**
 * @brief Reads the value of a GPIO pin.
 * @param Port GPIO port (A-H).
 * @param PinNum GPIO pin number (0-15).
 * @param PinVal Pointer to store the pin value (HIGH or LOW).
 * @return Status of the operation (OK, NOT_OK, or NULL_PTR_ERR).
 **/
uint8_t GPIO_U8ReadPinVal(Port_t Port,Pin_t PinNum,PinVal_t *PinVal);



#endif /* GPIO_INTERFACE_H_ */
