/*
 *  DMA_interface.h
 *
 *  Created on: Dec 8, 2024
 *  Author: Ahmed Ragab
 */

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

/* DMA Controller Selection */
typedef enum {
    DMA_1,
    DMA_2
}DMA_Number_t;

/* DMA Stream Selection */
typedef enum {
    Stream0=0,
    Stream1,
    Stream2,
    Stream3,
    Stream4,
    Stream5,
    Stream6,
    Stream7
}DMA_StreamNumber_t;

/* DMA Channel Selection*/
typedef enum {
    Channel0= 0,
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7
}DMA_ChannelNumber_t;

/* DMA Transfer Direction */
typedef enum {
    Peripheral_To_Memory=0,   /* Data flows from Peripheral to Memory*/
    Memory_To_Peripheral,     /* Data flows from Memory to Peripheral*/
    Memory_To_Memory          /* Data flows from Memory to Memory*/
}DMA_Direction_t;

/* DMA Priority Level */
typedef enum {
    DMA_PriorityLow=0,      /* Low Priority*/
    DMA_PriorityMedium,     /* Medium Priority*/
    DMA_PriorityHigh,       /* High Priority*/
    DMA_PriorityVeryHigh    /*Very High Priority*/
}DMA_PriorityLevel_t;

/* DMA Transfer Mode */
typedef enum {
    DMA_ModeNormal=0,   /* Normal mode (transfer stops after completion) */
    DMA_ModeCircular    /* Circular mode (transfer restarts automatically) */
}DMA_CircularMode_t;

/* DMA FIFO Mode */
typedef enum {
    DMA_FIFO_Disable=0,
    DMA_FIFO_Enable
}DMA_FIFO_Mode_t;

/* FIFO Threshold Selection Mode */
typedef enum {
    FIFO_THRESHOLD_1_4=0,     /* FIFO threshold is 1/4 full */
    FIFO_THRESHOLD_1_2,       /* FIFO threshold is 1/2 full */
    FIFO_THRESHOLD_3_4,       /* FIFO threshold is 3/4 full */
    FIFO_THRESHOLD_FULL       /* FIFO threshold is 4/4 full */
}DMA_FIFO_Threshold_t;

/*  Interrupt Status Flag */
typedef enum {
	FEIF=0,
	DMEIF=2,
    TEIF,
    HTIF,
	TCIF=5
}DMA_StatusID_t;

/* User defined configuration structure for DMA */
typedef struct {
    DMA_Number_t DMA_Number;
    DMA_StreamNumber_t Stream_Number;
    DMA_ChannelNumber_t Channel_Number;
    DMA_Direction_t Direction;
    DMA_PriorityLevel_t Priority;
    DMA_CircularMode_t Circular_Mode;
    DMA_FIFO_Mode_t FIFO_Mode;
    DMA_FIFO_Threshold_t FIFO_Threshold;
}DMA_Config_t;

/*==========================================================================================*/

/**
 * @brief  Initializes the DMA stream with the provided configuration.
 * @param  Copy_DMAConfig: Pointer to the DMA configuration structure, which contains:
 *         - DMA_Number: The DMA controller number (DMA1 or DMA2).
 *         - Stream_Number: The stream to configure (Stream0 to Stream7).
 *         - Channel_Number: The channel associated with the stream.
 *         - Priority: Priority level of the stream (Low, Medium, High, Very High).
 *         - Direction: Data transfer direction (Peripheral-to-Memory, Memory-to-Peripheral, Memory-to-Memory).
 *         - Circular_Mode: Enable/Disable circular mode.
 *         - FIFO_Mode: Enable/Disable FIFO mode.
 *         - FIFO_Threshold: FIFO threshold level (used if FIFO mode is enabled).
 * @retval uint8_t: Returns OK (0) if successful, or an error code if a failure occurs.
 * @note   This function disables the stream before applying the configuration to ensure safe changes.
 */
uint8_t DMA_u8Init(const DMA_Config_t *Copy_DMAConfig);

/**
 * @brief  Starts the DMA stream transfer with the provided parameters.
 * @param  Copy_DMAConfig: Pointer to the DMA configuration structure (same as in DMA_u8Init).
 * @param  Copy_u32PeripheralAddress: Address of the peripheral data register for the transfer.
 * @param  Copy_u32MemoryAddress: Address of the memory buffer for the transfer.
 * @param  Copy_u16DataLenght: Number of data items to transfer.
 * @retval uint8_t: Returns OK (0) if successful, or an error code if a failure occurs.
 * @note   The stream is enabled after setting all parameters.
 */
uint8_t DMA_u8Start(const DMA_Config_t *Copy_DMAConfig,uint32_t Copy_u32PeripheralAddress,uint32_t Copy_u32MemoryAddress,uint16_t Copy_u16DataLenght);

/**
 * @brief  Polls for the transfer completion of the specified DMA stream.
 * @param  Copy_DMAConfig: Pointer to the DMA configuration structure (same as in DMA_u8Init).
 * @retval uint8_t: Returns OK (0) if the transfer completes successfully, or a timeout error code.
 * @note   This function uses a timeout mechanism to avoid infinite loops in case of errors.
 * @note   The Transfer Complete Flag (TCIF) is cleared after polling.
 */
uint8_t DMA_u8PollForTransfer(const DMA_Config_t *Copy_DMAConfig);

/**
 * @brief  Starts the DMA stream transfer in interrupt mode.
 * @param  Copy_DMAConfig: Pointer to the DMA configuration structure (same as in DMA_u8Init).
 * @param  Copy_u32PeripheralAddress: Address of the peripheral data register for the transfer.
 * @param  Copy_u32MemoryAddress: Address of the memory buffer for the transfer.
 * @param  Copy_u16DataLenght: Number of data items to transfer.
 * @retval uint8_t: Returns OK (0) if successful, or an error code if a failure occurs.
 * @note   Interrupts for transfer complete (TCIE) and transfer error (TEIE) are enabled.
 */
uint8_t DMA_u8Start_IT(const DMA_Config_t *Copy_DMAConfig,uint32_t Copy_u32PeripheralAddress,uint32_t Copy_u32MemoryAddress,uint16_t Copy_u16DataLenght);

/**
 * @brief  Retrieves the status of a specific DMA flag.
 * @param  Copy_DMAConfig: Pointer to the DMA configuration structure (same as in DMA_u8Init).
 * @param  StatusID: Identifier of the status flag to check (e.g., TCIF, TEIF, etc.).
 * @param  Copy_u8Status: Pointer to a variable where the flag's status (1 or 0) will be stored.
 * @retval uint8_t: Returns OK (0) if successful, or an error code if a failure occurs.
 * @note   Determines the status register (LISR or HISR) and extracts the specific flag's value.
 */
uint8_t DMA_u8GetStatus(const DMA_Config_t *Copy_DMAConfig,DMA_StatusID_t StatusID,uint8_t *Copy_u8Status);


#endif /* DMA_INTERFACE_H_ */
