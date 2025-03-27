/*
 * CRC_interface.h
 *
 *  Created on: Mar 24, 2025
 *      Author: Ahmed Ragab
 */

#ifndef CRC_INTERFACE_H_
#define CRC_INTERFACE_H_


/**
 * @brief  Enumerations for CRC polynomial length
 */
typedef enum {
    CRC_POLYLENGTH_8B  = 0x01,  /* 8-bit polynomial */
    CRC_POLYLENGTH_16B = 0x02,  /* 16-bit polynomial */
    CRC_POLYLENGTH_32B = 0x03   /* 32-bit polynomial */
} CRC_PolyLength_t;

/**
 * @brief  Enumerations for CRC state
 */
typedef enum {
    CRC_STATE_RESET = 0x00,  /* CRC peripheral reset state */
    CRC_STATE_READY = 0x01,  /* CRC is ready for new calculation */
    CRC_STATE_BUSY  = 0x02,  /* CRC calculation in progress */
    CRC_STATE_ERROR = 0x03   /* CRC error state */
} CRC_State_t;

/**
 * @brief  Structure for CRC configuration
 */
typedef struct {
    uint32_t Polynomial;         /* CRC polynomial */
    CRC_PolyLength_t PolyLength; /* Polynomial length */
    uint32_t InitValue;          /* Initial CRC value */
    uint32_t CRCResult;          /* Last calculated CRC value */
    CRC_State_t State;           /* Current CRC state */
} CRC_Config_t;

/*=============================================================================*/

/**
 * @brief  Initialize the CRC peripheral
 * @param  config: Pointer to the CRC_Config_t structure
 * @retval status
 */
uint8_t CRC_Init(CRC_Config_t *config);

/**
 * @brief  Reset CRC peripheral
 * @param  config: Pointer to the CRC_Config_t structure
 * @retval status
 */
uint8_t CRC_RESET(CRC_Config_t *config);

/**
 * @brief  Compute CRC using the given buffer
 * @param  config: Pointer to the CRC_Config_t structure
 * @param  pBuffer: Pointer to input data array
 * @param  BufferLength: Length of the data array
 * @retval Computed CRC value
 */
uint32_t CRC_Accumulate(CRC_Config_t *config, uint32_t pBuffer[], uint32_t BufferLength);

#endif /* CRC_INTERFACE_H_ */
