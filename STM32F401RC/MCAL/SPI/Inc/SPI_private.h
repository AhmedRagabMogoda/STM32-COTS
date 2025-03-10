/*
 *  SPI_private.h
 *
 *  Created on: Dec 10, 2024
 *  Author: Ahmed Ragab
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define TIMEOUT                0xffffff
#define TIME_FINISHED          0
#define SPI_NUM_MAX            4u
#define CLEAR                  0
#define ONE                    1u

#define TXE_PIN_ACCESS         1u
#define RXNE_PIN_ACCESS        0

#define TXDMAEN_MASK           1u
#define TXDMAEN_PIN_ACCESS     1u
#define RXDMAEN_MASK           1u
#define RXDMAEN_PIN_ACCESS     0

#define ENABLE_MASK            1u
#define ENABLE_PIN_ACCESS      6u

#define BIDIMODE_MASK          1u
#define BIDIMODE_PIN_ACCESS    15u

#define BIDIOE_MASK            1u
#define BIDIOE_PIN_ACCESS      14u

#define CRCEN_MASK             1u
#define CRCEN_PIN_ACCESS       13u

#define DFF_MASK               1u
#define DFF_PIN_ACCESS         11u

#define RXONLY_MASK            1u
#define RXONLY_PIN_ACCESS      10u

#define SSM_MASK               1u
#define SSM_PIN_ACCESS         9u

#define SSI_MASK               1u
#define SSI_PIN_ACCESS         8u

#define LSBFIRST_MASK          1u
#define LSBFIRST_PIN_ACCESS    7u

#define BR_MASK                0b111
#define BR_PIN_ACCESS          3u

#define MSTR_MASK              1u
#define MSTR_PIN_ACCESS        2u

#define CPOL_MASK              1u
#define CPOL_PIN_ACCESS        1u

#define CPHA_MASK              1u
#define CPHA_PIN_ACCESS        0


#endif /* SPI_PRIVATE_H_ */
