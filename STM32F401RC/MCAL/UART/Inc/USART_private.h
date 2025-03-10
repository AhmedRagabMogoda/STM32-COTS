/*
 *  USART_private.h
 *
 *  Created on: Dec 9, 2024
 *  Author: Ahmed Ragab
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define F_CLK                       16000000u
#define USART_NUM_MAX               3u
#define CLEAR                       0
#define ONE                         1u
#define TIMEOUT                     0xffffff
#define TIME_FINISHED               0

#define TXE_PIN_ACCESS              7u
#define RXNE_PIN_ACCESS             5u

#define DMAT_MASK                   1u
#define DMAT_PIN_ACCESS             7u
#define DMAR_MASK                   1u
#define DMAR_PIN_ACCESS             6u

#define ENABLE_MASK                 1u
#define ENABLE_PIN_ACCESS           13u

#define TX_RX_MASK                  0b11
#define TX_RX_PIN_ACCESS            2u

#define WORDLENGHT_MASK             1u
#define WORDLENGHT_PIN_ACCESS       12u

#define PARITY_MASK                 1u
#define PARITY_PIN_ACCESS           10u

#define PARITYTYPE_MASK             1u
#define PARITYTYPE_PIN_ACCESS       9u

#define OVERSAMPLING_MASK           1u
#define OVERSAMPLING_PIN_ACCESS     15u

#define STOPBIT_MASK                0b11
#define STOPBIT_PIN_ACCESS          12u

#define CTS_RTS_MASK                0b11
#define CTS_RTS_PIN_ACCESS          8u

#define OVERSAMPLING_MASK           1u
#define OVERSAMPLING_PIN_ACCESS     15u

#define DIV_FRACTION_PIN_ACCESS     0
#define DIV_MANTISSA_PIN_ACCESS     4u


#endif /* UART_PRIVATE_H_ */
