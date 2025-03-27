/*
 *  Bootloader_interface.h
 *
 *  Created on: Jan 26, 2025
 *  Author: Ahmed Ragab mogoda
 */

#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_

#define FLASH_SECTOR2_BASE_ADDRESS   0x08008000UL

#define UART USART_6

#define BL_ACK        0xA5
#define BL_NACK       0x7F


#define BL_GET_VERSION          0x51
#define BL_GET_HELP             0x52
#define BL_GET_CID              0x53
#define BL_GET_RDP_STATUS       0x54
#define BL_GO_TO_ADDRESS        0x55
#define BL_FLASH_ERASE          0x56
#define BL_MEMORY_WRITE         0x57
#define BL_EM_RW_PROTECT        0x58
#define BL_MEMORY_READ          0x59
#define BL_READ_SECTOR_STATUS   0x5A
#define BL_OTP_READ             0x5B
#define BL_DISABLE_RW_PROTECT   0x5C

/*=================================================================================*/

/* Function: BL_voidHandleGetVersionCmd
 * Description: Handles the Get Version command from the bootloader, verifying the CRC and sending the bootloader version if valid.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleGetVersionCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleGetHelpCmd
 * Description: Handles the Get Help command by sending a list of supported bootloader commands.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleGetHelpCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleGetCIDCmd
 * Description: Retrieves the chip identification number and sends it if CRC is valid.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleGetCIDCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleGetRDPStatusCmd
 * Description: Retrieves the Read Protection (RDP) status and sends it if CRC is valid.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleGetRDPStatusCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleGoToAddressCmd
 * Description: Jumps to a specified address if it is valid.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleGoToAddressCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleFlashEraseCmd
 * Description: Handles Flash Erase Command from the host by verifying CRC and executing a flash erase operation.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleFlashEraseCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleMemoryWriteCmd
 * Description: Handles Memory Write Command by validating the address and writing data to memory.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleMemoryWriteCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleMemoryReadCmd
 * Description: Reads data from memory and sends it back to the host if the address is valid.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleMemoryReadCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleEnableRWProtectCmd
 * Description: Enables Read/Write protection on the Flash memory.
 *              It locks specific sectors from being written or read based on the input command.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet containing the protection mode.
 * Return: None
 */
void BL_voidHandleEnableRWProtectCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleDisableRWProtectCmd
 * Description: Disables Read/Write protection on the Flash memory.
 *              It allows previously protected sectors to be accessed normally.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleDisableRWProtectCmd(uint8_t* copy_pu8CmdPacket);

/* Function: BL_voidHandleReadSectorStatusCmd
 * Description: Reads and returns the protection status of Flash memory sectors.
 *              The status is extracted from the Option Bytes register.
 * Parameters: copy_pu8CmdPacket - Pointer to the received command packet.
 * Return: None
 */
void BL_voidHandleReadSectorStatusCmd(uint8_t* copy_pu8CmdPacket);

#endif /* BOOTLOADER_INTERFACE_H_ */
