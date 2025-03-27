/*
 *  FLASH_interface.h
 *
 *  Created on: Mar 25, 2025
 *  Author: Ahmed Ragab
 */

#ifndef FLASH_INTERFACE_H_
#define FLASH_INTERFACE_H_

/**
  * @brief FLASH Status enumeration
  */
typedef enum
{
  FLASH_OK = 0,
  FLASH_ERROR,
  FLASH_BUSY,
  FLASH_TIMEOUT,
  FLASH_NULL_PTR,
  FLASH_WRITE_PROTECTION_ERROR,
  FLASH_OPERATION_ERROR
} FLASH_Status_t;

/**
  * @brief FLASH Program Type enumeration
  */
typedef enum
{
  FLASH_TYPEPROGRAM_BYTE = 0,  /*!< Program byte (8-bit) at a specified address */
  FLASH_TYPEPROGRAM_HALFWORD,   /*!< Program a half-word (16-bit) at a specified address */
  FLASH_TYPEPROGRAM_WORD,       /*!< Program a word (32-bit) at a specified address */
  FLASH_TYPEPROGRAM_DOUBLEWORD  /*!< Program a double word (64-bit) at a specified address */
} FLASH_ProgramType_t;


/**
 * @brief FLASH Erase Type
 */
typedef enum {
    FLASH_TYPEERASE_SECTOR = 0x01,  /*!< Erase specific sectors */
    FLASH_TYPEERASE_MASS   = 0x02   /*!< Erase entire bank */
} FLASH_TypeErase_t;

/**
 * @brief FLASH Voltage Range
 */
typedef enum {
    FLASH_VOLTAGE_RANGE_1 = 0x00, /*!< 1.8V - 2.1V */
    FLASH_VOLTAGE_RANGE_2 = 0x01, /*!< 2.1V - 2.7V */
    FLASH_VOLTAGE_RANGE_3 = 0x02, /*!< 2.7V - 3.6V */
    FLASH_VOLTAGE_RANGE_4 = 0x03  /*!< 3.6V and above */
} FLASH_VoltageRange_t;

/**
 * @brief FLASH Bank Selection
 */
typedef enum {
    FLASH_BANK_1 = 0x01, /*!< Bank 1 */
    FLASH_BANK_2 = 0x02  /*!< Bank 2 */
} FLASH_Bank_t;

/**
  * @brief Flash Memory Sector Enumeration
  * @note  STM32F401 has 8 sectors (0-7) of varying sizes
  */
typedef enum {
    FLASH_SECTOR_0 = 0,  /*!< Sector 0:  16 KB */
    FLASH_SECTOR_1,      /*!< Sector 1:  16 KB */
    FLASH_SECTOR_2,      /*!< Sector 2:  16 KB */
    FLASH_SECTOR_3,      /*!< Sector 3:  16 KB */
    FLASH_SECTOR_4,      /*!< Sector 4:  64 KB */
    FLASH_SECTOR_5,      /*!< Sector 5: 128 KB */
    FLASH_SECTOR_6,      /*!< Sector 6: 128 KB */
    FLASH_SECTOR_7,      /*!< Sector 7: 128 KB */
    FLASH_SECTOR_TOTAL   /*!< Total number of sectors */
} FlashSector_t;

/**
  * @brief FLASH Erase Init structure definition
  */
typedef struct {
    FLASH_TypeErase_t TypeErase;      /*!< Mass erase or sector erase */
    uint32_t Sector;                  /*!< Initial sector to erase when Mass erase is disabled */
    uint32_t NbSectors;               /*!< Number of sectors to be erased */
    FLASH_VoltageRange_t VoltageRange; /*!< Voltage range for the erase operation */
    FLASH_Bank_t Banks;                 /*!< Target flash bank for erase */
} FLASH_Erase_t;

/**
  * @brief Write Protection State Enumeration
  */
typedef enum {
    OB_WRPSTATE_DISABLE, /*!< Disable the write protection of the desired bank 1 sectors */
    OB_WRPSTATE_ENABLE   /*!< Enable the write protection of the desired bank 1 sectors  */
} OB_WRPState_t;

/**
  * @brief FLASH Option Type Enumeration
  */
typedef enum {
    OPTIONBYTE_WRP , /*!< WRP option byte configuration  */
    OPTIONBYTE_RDP , /*!< RDP option byte configuration  */
    OPTIONBYTE_USER, /*!< USER option byte configuration */
    OPTIONBYTE_BOR   /*!< BOR option byte configuration  */
} FLASH_OptionByte_t;

/**
  * @brief FLASH Option Bytes Read Protection Levels
  */
typedef enum {
    OB_RDP_LEVEL_0 = 0xAA, /*!< No protection (full access) */
    OB_RDP_LEVEL_1 = 0x55, /*!< Read protection enabled */
    OB_RDP_LEVEL_2 = 0xCC  /*!< Permanently enabled (irreversible) */
} OB_RDPLevel_t;


/**
  * @brief FLASH Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;              /*!< Option byte to be configured */
  uint32_t RDPLevel;                /*!< Set the read protection level */
  uint32_t USERConfig;              /*!< User option byte configuration */
  uint32_t BORLevel;                /*!< BOR level */
  uint32_t WRPState;                /*!< WRP state (ENABLE/DISABLE) */
  uint32_t WRPSector;               /*!< Sector to be write protected */
} FLASH_OBProgram_t;

/*===========================================================================*/

/**
 * @brief  Waits until the FLASH is not busy.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_TIMEOUT if it takes too long)
 */
FLASH_Status_t FLASH_WaitForNotBusy(void);

/**
 * @brief  Unlocks the FLASH control register to allow modifications.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if already unlocked)
 */
FLASH_Status_t FLASH_Unlock(void);

/**
 * @brief  Locks the FLASH control register to prevent modifications.
 * @retval FLASH_Status_t (FLASH_OK if successful)
 */
FLASH_Status_t FLASH_Lock(void);

/**
 * @brief  Erases the specified FLASH sectors or performs a mass erase.
 * @param  pEraseInit: Pointer to a FLASH_Erase_t structure containing erase configuration.
 * @param  SectorError: Pointer to a variable that holds the first sector that failed to erase.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if failed)
 */
FLASH_Status_t FLASHEx_Erase(FLASH_Erase_t *pEraseInit, uint32_t *SectorError);

/**
 * @brief  Programs data into the FLASH memory.
 * @param  TypeProgram: Specifies the programming type (byte, half-word, word, double-word).
 * @param  Address: Specifies the memory address to be programmed.
 * @param  Data: Specifies the data to be written.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if failed)
 */
FLASH_Status_t FLASH_Program(FLASH_ProgramType_t TypeProgram, uint32_t Address, uint64_t Data);

/**
 * @brief  Launches the option byte loading process.
 * @note   The device resets automatically after this operation.
 * @retval FLASH_Status_t (FLASH_OK if successful)
 */
FLASH_Status_t FLASH_OB_Launch(void);

/**
 * @brief  Unlocks the FLASH Option Control Register (OPTCR) to allow modification.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if already unlocked)
 */
FLASH_Status_t FLASH_OB_Unlock(void);

/**
 * @brief  Locks the FLASH Option Control Register (OPTCR) to prevent modification.
 * @retval FLASH_Status_t (FLASH_OK if successful)
 */
FLASH_Status_t FLASH_OB_Lock(void);

/**
 * @brief  Retrieves the current configuration of the FLASH Option Bytes.
 * @param  pOBInit: Pointer to a FLASH_OBProgram_t structure that will store the configuration.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if failed)
 */
FLASH_Status_t FLASHEx_OBGetConfig(FLASH_OBProgram_t *pOBInit);

/**
 * @brief  Programs the FLASH Option Bytes with the provided configuration.
 * @param  pOBInit: Pointer to a FLASH_OBProgram_t structure containing new option byte values.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if failed)
 */
FLASH_Status_t FLASHEx_OBProgram(FLASH_OBProgram_t *pOBInit);


#endif /* FLASH_INTERFACE_H_ */
