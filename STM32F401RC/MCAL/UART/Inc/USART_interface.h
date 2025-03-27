/*
 *  USART_interface.h
 *
 *  Created on: Dec 9, 2024
 *  Author: Ahmed Ragab
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

typedef enum{
	USART_1=0,
	USART_2,
	USART_6
}UART_Number_t;

typedef enum{
	USART_DISABLE=0,
	USART_ENABLE
}UART_Enable_t;

/* Enumeration for Configurations */
typedef enum{
	DISABLE_MODE,
    MODE_RX,            /* Transmitter mode */
    MODE_TX,            /* Receiver mode */
    MODE_TX_RX          /* Both Transmitter and Receiver mode */
}UART_Mode_t;

typedef enum{
	PARITY_DISABLE,
	PARITY_ENABLE
}UART_Parity_t;

typedef enum{
	PARITY_EVEN,
    PARITY_ODD
}UART_ParityType_t;

typedef enum{
    WORDLENGTH_8BIT,      /* 8-bit word length */
    WORDLENGTH_9BIT       /* 9-bit word length */
}UART_WordLength_t;

typedef enum{
    OVERSAMPLING_16=0,     /* Over sampling by 16 */
    OVERSAMPLING_8         /* Over sampling by 8 */
}UART_OverSampling_t;

typedef enum{
    STOPBIT_1,      /* 1 stop bits */
    STOPBIT_1_2,    /* 0.5 stop bits */
	STOPBIT_2,      /* 2 stop bits */
	STOPBIT_3_2     /* 1.5 stop bits */
}UART_StopBit_t;

typedef enum {
    HWCONTROL_NONE=0,      /* No hardware flow control */
    HWCONTROL_RTS,         /* RTS (Request To Send) enabled */
    HWCONTROL_CTS,         /* CTS (Clear To Send) enabled */
    HWCONTROL_RTS_CTS      /* Both RTS and CTS enabled */
}UART_HWFlowControl_t;

/* Structure Configuration */
typedef struct{
	UART_Number_t UARTNumber;               /* UART number (1 to 6) */
	UART_Enable_t UARTEnable;               /* Enable or Disable */
	UART_Mode_t Mode;                       /* Transmitter, Receiver, or both */
	UART_WordLength_t WordLength;           /* 8 or 9 bits */
	UART_Parity_t Parity;                   /* Enable or Disable */
	UART_ParityType_t ParityType;           /* Even, Odd */
	UART_OverSampling_t OverSampling;       /* 16 or 8 times over sampling */
    UART_StopBit_t StopBits;                /* 0.5 or 1 or 1.5 or 2 stop bits */
    UART_HWFlowControl_t HW_FlowControl;    /* None, RTS, CTS, or RTS/CTS */
    uint32_t BaudRate;                      /* Baud rate (e.g., 9600, 115200) */
}UART_Config_t;

/*==========================================================================================*/

/*
 * UART_u8Init
 *
 * Description:
 * Configures the UART peripheral based on the provided configuration structure.
 * Sets parameters such as mode (TX/RX), baud rate, word length, parity, stop bits,
 * hardware flow control, and oversampling.
 *
 * Parameters:
 * - Copy_UARTConfig: Pointer to a UART_Config_t structure with the desired UART settings.
 *
 * Return:
 * - OK: Initialization successful.
 * - NULL_PTR_ERR: Null pointer passed as configuration.
 * - NOT_OK: Invalid oversampling or other configuration error.
 */
uint8_t UART_u8Init(UART_Config_t *Copy_UARTConfig);

/*
 * UART_u8Send
 *
 * Description:
 * Transmits an array of data using polling mode.
 * Waits until the UART Data Register (DR) is empty before sending each byte/word.
 *
 * Parameters:
 * - Copy_UARTConfig: Pointer to UART_Config_t structure for UART settings.
 * - Data: Pointer to the data buffer to be sent.
 * - DataLength: Number of data elements to send.
 *
 * Return:
 * - OK: Data sent successfully.
 * - NULL_PTR_ERR: Null pointer passed for configuration or data buffer.
 * - TIME_OUT: Operation timed out while waiting for TXE flag.
 */
uint8_t UART_u8Send(UART_Config_t *Copy_UARTConfig,uint8_t *Data, uint32_t DataLength);

/*
 * UART_u8Receive
 *
 * Description:
 * Receives an array of data using polling mode.
 * Waits until the UART Data Register (DR) has received data for each byte/word.
 *
 * Parameters:
 * - Copy_UARTConfig: Pointer to UART_Config_t structure for UART settings.
 * - Data: Pointer to the buffer where received data will be stored.
 * - DataLength: Number of data elements to receive.
 *
 * Return:
 * - OK: Data received successfully.
 * - NULL_PTR_ERR: Null pointer passed for configuration or data buffer.
 * - TIME_OUT: Operation timed out while waiting for RXNE flag.
 */
uint8_t UART_u8Receive(UART_Config_t *Copy_UARTConfig,uint8_t *Data, uint32_t DataLength);

/**
 * @brief Enables DMA mode for USART transmission.
 *
 * This function sets the DMAT (DMA Transmitter Enable) bit in the CR3 register
 * of the specified USART peripheral. This configuration allows data transmission
 * to be handled by the DMA controller, reducing CPU load.
 *
 * @param the UART instance number.
 *
 * @return no
 */
uint8_t UART_u8Send_DMA(UART_Config_t *Copy_UARTConfig);

/**
 * @brief Enables DMA mode for USART reception.
 *
 * This function sets the DMAR (DMA Receiver Enable) bit in the CR3 register
 * of the specified USART peripheral. This configuration allows incoming data
 * to be handled by the DMA controller, reducing CPU overhead.
 *
 * @param the UART instance number.
 *
 * @return no
 */
uint8_t UART_u8Receive_DMA(UART_Config_t *Copy_UARTConfig);



#endif /* USART_INTERFACE_H_ */
