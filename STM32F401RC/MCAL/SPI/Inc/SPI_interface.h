/*
 *  SPI_interface.h
 *
 *  Created on: Dec 10, 2024
 *  Author: Ahmed Ragab
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/* SPI Numbers */
typedef enum{
	SPI_1=0,
	SPI_2,
	SPI_3,
	SPI_4
}SPI_Number_t;

/* SPI Modes */
typedef enum{
    SPI_Mode_Slave,   /* Slave mode */
    SPI_Mode_Master   /* Master mode */
}SPI_Mode_t;

/* SPI Bidirectional data mode enable */
typedef enum{
    SPI_BidirectionalMode_2Line,  /* Two-line unidirectional data mode */
    SPI_BidirectionalMode_1Line   /* One-line bidirectional data mode */
}SPI_BidirectionalMode_t;

/* Output Enable in Bidirectional Mode */
typedef enum{
    SPI_BidirectionalOutput_Disabled, /* Receiver enabled in bidirectional mode (receive-only mode) */
    SPI_BidirectionalOutput_Enabled   /* Transmitter enabled in bidirectional mode (transmit-only mode) */
}SPI_BidirectionalOutput_t;

/* Enumeration for Receive-Only Mode */
typedef enum{
    SPI_ReceiveOnly_Disabled,  /* Full-duplex mode */
    SPI_ReceiveOnly_Enabled    /* Receive-only mode */
}SPI_ReceiveOnlyMode_t;

/* Enumeration for CRC Enable */
typedef enum{
    SPI_CRC_Disabled,  /* CRC calculation disabled */
    SPI_CRC_Enabled    /* CRC calculation enabled */
}SPI_CRC_t;

typedef enum{
    SPI_BIDIOE_INPUT = 0x0,     // Receiver enabled in bidirectional mode
    SPI_BIDIOE_OUTPUT = 0x1     // Transmitter enabled in bidirectional mode
}SPI_BIDIOE_t;

/* SPI Baud Rate Prescaler */
typedef enum{
    SPI_BaudRate_Div2=0,  /* Baud rate: f_PCLK / 2 */
    SPI_BaudRate_Div4,    /* Baud rate: f_PCLK / 4 */
    SPI_BaudRate_Div8,    /* Baud rate: f_PCLK / 8 */
    SPI_BaudRate_Div16,   /* Baud rate: f_PCLK / 16 */
    SPI_BaudRate_Div32,   /* Baud rate: f_PCLK / 32 */
    SPI_BaudRate_Div64,   /* Baud rate: f_PCLK / 64 */
    SPI_BaudRate_Div128,  /* Baud rate: f_PCLK / 128 */
    SPI_BaudRate_Div256   /* Baud rate: f_PCLK / 256 */
}SPI_BaudRateControl_t;

/* SPI Data Frame Format */
typedef enum{
    SPI_DataFrame_8Bit,  /* 8-bit data frame format */
    SPI_DataFrame_16Bit  /* 16-bit data frame format */
}SPI_DataFrameFormat_t;

/* SPI Clock Polarity */
typedef enum{
    SPI_ClockPolarity_Low,  /* Clock idle state low */
    SPI_ClockPolarity_High  /* Clock idle state high */
}SPI_ClockPolarity_t;

/* SPI Clock Phase */
typedef enum{
    SPI_ClockPhase_1Edge,  /* Data captured on the first clock edge */
    SPI_ClockPhase_2Edge   /* Data captured on the second clock edge */
}SPI_ClockPhase_t;

/* Enumeration for Frame Format */
typedef enum{
    SPI_FrameFormat_MSB,  /* Data frame starts with MSB */
    SPI_FrameFormat_LSB   /* Data frame starts with LSB */
}SPI_FrameFormat_t;

/* SPI NSS Management */
typedef enum{
    SPI_SoftwareSlave_Disabled, /* Hardware NSS management */
    SPI_SoftwareSlave_Enabled   /* Software NSS management */
}SPI_SoftwareSlaveManagement_t;

/* Enumeration for Internal Slave Select */
typedef enum{
    SPI_InternalSlave_Low,  /* Slave mode */
    SPI_InternalSlave_High  /* Master mode (with SSM enabled) */
}SPI_InternalSlaveSelect_t;

/* SPI Configuration Structure */
typedef struct{
	SPI_Number_t Number;                                    /* Number of SPI */
	SPI_Mode_t Mode;                                        /* Master/slave mode */
    SPI_BidirectionalMode_t BidirectionalMode;              /* Bidirectional data mode */
    SPI_BidirectionalOutput_t BidirectionalOutput;          /* Output enable in bidirectional mode */
    SPI_CRC_t CRCEN;                                        /* CRC enable */
    SPI_DataFrameFormat_t DataFrameFormat;                  /* Data frame format */
    SPI_ReceiveOnlyMode_t ReceiveOnlyMode;                  /* Receive-only mode */
    SPI_SoftwareSlaveManagement_t SoftwareSlaveManagement;  /* Software slave management */
    SPI_InternalSlaveSelect_t InternalSlaveSelect;          /* Internal slave select */
    SPI_FrameFormat_t FrameFormat;                          /* Frame format LSB or MSB */
    SPI_BaudRateControl_t BaudRateControl;                  /* Baud rate control */
    SPI_ClockPolarity_t ClockPolarity;                      /* Clock polarity */
    SPI_ClockPhase_t ClockPhase;                            /* Clock phase */
}SPI_Config_t;

/*=======================================================================================================*/

/**
 * @brief Initialize the SPI peripheral based on the user configuration.
 * This function configures various SPI parameters such as data format, baud rate, mode, clock settings, and others.
 * It disables the SPI module before making any configurations to ensure safe initialization.
 *
 * @param Copy_SPIConfig: Pointer to the SPI_Config_t structure containing the configuration parameters.
 * - Number: The SPI instance (e.g., SPI1, SPI2).
 * - BidirectionalMode: Determines if the SPI operates in full-duplex, half-duplex, or simplex.
 * - BidirectionalOutput: Sets the output enable in half-duplex mode.
 * - ReceiveOnlyMode: Enables receive-only mode in simplex operation.
 * - CRCEN: Enables or disables CRC calculation for error detection.
 * - DataFrameFormat: Sets the data frame size (8-bit or 16-bit).
 * - SoftwareSlaveManagement: Enables software-based slave select management.
 * - InternalSlaveSelect: Configures the internal slave select pin (used when software management is enabled).
 * - FrameFormat: Configures the frame format (LSB first or MSB first).
 * - BaudRateControl: Sets the SPI clock speed.
 * - Mode: Configures the SPI as a master or slave.
 * - ClockPolarity: Sets the clock idle state (high or low).
 * - ClockPhase: Configures data sampling on the rising or falling clock edge.
 *
 * @return uint8_t: Error state:
 * - OK: Initialization successful.
 * - NULL_PTR_ERR: The configuration pointer is NULL.
 */
uint8_t SPI_u8Init(SPI_Config_t *Copy_SPIConfig);

/**************************************************************************
 * @brief   SPI Send and Receive Data Function
 * @details This function sends and receives data using the SPI peripheral
 *          in full-duplex mode. It supports a specified length of data and
 *          ensures proper data transmission with timeouts for safety.
 *
 * @param   SPINumber       Specifies the SPI peripheral number (e.g., SPI1, SPI2).
 * @param   *SendData       Pointer to the array of data to be sent.
 * @param   *ReceivedData   Pointer to the array to store received data.
 * @param   DataLength      The number of data elements to be transmitted/received.
 *
 * @return  uint8_t         Function execution status:
 *                          - OK: Operation succeeded.
 *                          - TIME_OUT: Timeout occurred during send/receive.
 *                          - NULL_PTR_ERR: One of the pointers is NULL.
 *
 * @note    The function waits for the TXE (Transmit Buffer Empty) flag
 *          before sending data and RXNE (Receive Buffer Not Empty) flag
 *          before reading the received data. It uses a timeout mechanism
 *          to prevent indefinite waiting.
 **************************************************************************/
uint8_t SPI_u8SendReceiveData(SPI_Number_t SPINumber, uint16_t *SendData, uint16_t *ReceivedData, uint32_t DataLength);

/**
 * @brief Transmit data through the SPI peripheral in blocking mode.
 * This function waits until the transmit buffer is empty before sending each data byte.
 * It ensures all data in the provided array is transmitted successfully.
 * @param SPINumber: Specifies the SPI peripheral number (e.g., SPI1, SPI2).
 * @param Data: Pointer to an array of data to transmit.
 * @param DataLength: Number of data elements in the array.
 * @return uint8_t: Error state:
 * - OK: Data transmission successful.
 * - TIME_OUT: Transmission timed out waiting for the buffer to empty.
 * - NULL_PTR_ERR: One of the provided pointers is NULL.
 */
uint8_t SPI_u8SendData(SPI_Number_t SPINumber,uint16_t *Data,uint32_t DataLength);

/**
 * @brief Receive data from the SPI peripheral in blocking mode.
 * This function waits until the receive buffer is full before reading each data byte.
 * It ensures all data elements are received and stored in the provided array.
 * @param SPINumber: Specifies the SPI peripheral number (e.g., SPI1, SPI2).
 * @param Data: Pointer to an array where received data will be stored.
 * @param DataLength: Number of data elements to receive.
 * @return uint8_t: Error state:
 * - OK: Data reception successful.
 * - TIME_OUT: Reception timed out waiting for the buffer to fill.
 * - NULL_PTR_ERR: One of the provided pointers is NULL.
 */
uint8_t SPI_u8ReceiveData(SPI_Number_t SPINumber,uint16_t *Data,uint32_t DataLength);

/**
 * @brief Enable DMA transmission for the SPI peripheral.
 * This function enables the SPI's DMA transmission capability by setting the corresponding bit in the control register.
 * It assumes the DMA controller is correctly configured beforehand.
 * @param SPINumber: Specifies the SPI peripheral number (e.g., SPI1, SPI2)..
 * @return  none
 */
void SPI_u8SendData_DMA(SPI_Number_t SPINumber);

/**
 * @brief Enable DMA reception for the SPI peripheral.
 * This function enables the SPI's DMA reception capability by setting the corresponding bit in the control register.
 * It assumes the DMA controller is correctly configured beforehand.
 * @param SPINumber: Specifies the SPI peripheral number (e.g., SPI1, SPI2).
 * @return none
 */
void SPI_u8ReceiveData_DMA(SPI_Number_t SPINumber);


#endif /* SPI_INTERFACE_H_ */
