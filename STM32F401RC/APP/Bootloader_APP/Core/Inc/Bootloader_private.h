/*
 *  Bootloader_private.h
 *
 *  Created on: Jan 26, 2025
 *  Author: Ahmed Ragab mogoda
 */

#ifndef BOOTLOADER_PRIVATE_H_
#define BOOTLOADER_PRIVATE_H_

#define BL_Version  1u

#define CRC_SUCCESS  0u
#define CRC_FAIL     1u

#define PROTECTION_SUCCESS  1u
#define PROTECTION_FAIL     0u

#define VALID_ADDRESS   0u
#define INVALID_ADDRESS 1u

#define WRITING_SUCCESS  0U
#define WRITING_ERORR    1U

#define DBGMCU_IDCODE_REG      *((volatile uint16_t*)0xE0042000UL)
#define RDP_USER_OPTION_WORD   *((volatile uint16_t*)0x1FFFC000UL)

/*
 * Function: BL_u8VerifyCRC
 * ------------------------
 * Verifies the CRC checksum for the received data packet.
 *
 * Parameters:
 *   Copy_pu8DataArr - Pointer to the received data array.
 *   Copy_u8Length   - Length of the data array.
 *   Copy_u8HostCRC  - CRC value sent by the host.
 *
 * Returns:
 *   CRC_SUCCESS if the calculated CRC matches the host CRC.
 *   CRC_FAIL otherwise.
 */
static uint8_t BL_u8VerifyCRC(uint8_t* Copy_pu8DataArr,uint8_t Copy_u8Length,uint32_t Copy_u8HostCRC);

/*
 * Function: voidSendACK
 * ----------------------
 * Sends an acknowledgment (ACK) to the host.
 *
 * Parameters:
 *   Copy_u8ReplyLength - Number of bytes expected in the response.
 */
static void voidSendACK(uint8_t Copy_u8ReplyLength);

/*
 * Function: voidSendNACK
 * -----------------------
 * Sends a negative acknowledgment (NACK) to the host.
 */
static void voidSendNACK(void);

/*
 * Function: u8ValidAddress
 * -------------------------
 * Validates whether the given memory address falls within Flash or SRAM.
 *
 * Parameters:
 *   Copy_u32Address - The memory address to validate.
 *
 * Returns:
 *   VALID_ADDRESS if the address is within Flash or SRAM.
 *   INVALID_ADDRESS otherwise.
 */
static uint8_t u8ValidAddress(uint32_t Copy_u32Address);

/*
 * Function: u8ExecuteFlashErase
 * -----------------------------
 * Erases one or more sectors in Flash memory.
 *
 * Parameters:
 *   Copy_u8SectorNumber   - The starting sector number to erase. 0xFF means mass erase.
 *   Copy_u8NumberOfSectors - Number of sectors to erase.
 *
 * Returns:
 *   HAL_OK if the erase operation is successful.
 *   HAL_ERROR if an invalid sector number is provided.
 */
static uint8_t u8ExecuteFlashErase(uint8_t Copy_u8SectorNumber, uint8_t Copy_u8NumberOfSectors);

/*
 * Function: u8ExecuteMemoryWrite
 * ------------------------------
 * Writes data to Flash or SRAM memory.
 *
 * Parameters:
 *   Copy_pu8DataArr - Pointer to the data array to be written.
 *   Copy_u32Address - The target memory address.
 *   Copy_u8Length   - Number of bytes to write.
 *
 * Returns:
 *   HAL_OK if writing is successful.
 *   HAL_ERROR otherwise.
 */
static uint8_t u8ExecuteMemoryWrite(uint8_t* Copy_pu8DataArr, uint32_t Copy_u32Address, uint8_t Copy_u8Length);



#endif /* BOOTLOADER_PRIVATE_H_ */
