/*
 *  Bootloader_Program.c
 *
 *  Created on: Jan 26, 2025
 *  Author: Ahmed Ragab mogoda
 */

#include <stdint.h>
#include <string.h>
#include "Bootloader_interface.h"
#include "Bootloader_private.h"
#include "main.h"

extern CRC_HandleTypeDef hcrc;
extern UART_HandleTypeDef huart6;

void Bootloader_UartReadData(void)
{
	/* this function is used to read command from Host */
	uint8_t Local_u8CmdPacket[255] = {0};

	while(1)
	{
		/* clear the command packet every iteration */
		memset(Local_u8CmdPacket,0,255);

		/* 1st step: read the first byte which includes the length to follow */
		HAL_UART_Receive(&huart6,Local_u8CmdPacket,1,HAL_MAX_DELAY);

		/* 2st step: read the reset of the command */
		HAL_UART_Receive(&huart6,&Local_u8CmdPacket[1],Local_u8CmdPacket[0],HAL_MAX_DELAY);

		/* 3st step: check the command code, then handle the command */
		switch(Local_u8CmdPacket[1]) /* this byte includes the command code */
		{
		case BL_GET_VERSION         :  BL_voidHandleGetVersionCmd(Local_u8CmdPacket);         break;
		case BL_GET_HELP            :  BL_voidHandleGetHelpCmd(Local_u8CmdPacket);            break;
		case BL_GET_CID             :  BL_voidHandleGetCIDCmd(Local_u8CmdPacket);             break;
		case BL_GET_RDP_STATUS      :  BL_voidHandleGetRDPStatusCmd(Local_u8CmdPacket);       break;
		case BL_GO_TO_ADDRESS       :  BL_voidHandleGoToAddressCmd(Local_u8CmdPacket);        break;
		case BL_FLASH_ERASE         :  BL_voidHandleFlashEraseCmd(Local_u8CmdPacket);         break;
		case BL_MEMORY_WRITE        :  BL_voidHandleMemoryWriteCmd(Local_u8CmdPacket);        break;
		case BL_EM_RW_PROTECT       :  BL_voidHandleEnableRWProtectCmd(Local_u8CmdPacket);    break;
		case BL_MEMORY_READ         :  BL_voidHandleMemoryReadCmd(Local_u8CmdPacket);         break;
		case BL_READ_SECTOR_STATUS  :  BL_voidHandleReadSectorStatusCmd(Local_u8CmdPacket);   break;
		case BL_DISABLE_RW_PROTECT  :  BL_voidHandleDisableRWProtectCmd(Local_u8CmdPacket);   break;
		default:                                                                              break;
		}

	}
}

void Bootloader_JumpToUserAPP(void)
{
	/* Pointer to function to hold the address of the reset handler of the user App */
	void (*App_ResetHandler)(void);
	uint32_t ResetHandlerAddress = *((volatile uint32_t*)FLASH_SECTOR2_BASE_ADDRESS + 4);
	App_ResetHandler = (void*)ResetHandlerAddress;

	/* Configuration MSP of the user App by Reading value from base address of sector2 */
	uint32_t Local_u32MSPVal = *((volatile uint32_t*)FLASH_SECTOR2_BASE_ADDRESS);
	__asm volatile("MSR MSP,%0"::"r"(Local_u32MSPVal));

	/* Vector Table Relocation */
	SCB->VTOR = FLASH_SECTOR2_BASE_ADDRESS;

	/* Jump to the user App Reset Handler */
	App_ResetHandler();
}

static uint8_t BL_u8VerifyCRC(uint8_t* Copy_pu8DataArr,uint8_t Copy_u8Length,uint32_t Copy_u8HostCRC)
{
	uint8_t Local_u8Iteration, Local_u8CRCStatus;
	uint32_t Local_u32AccCRC, Local_u32Temp;
	for(Local_u8Iteration = 0; Local_u8Iteration < Copy_u8Length; Local_u8Iteration++)
	{
		Local_u32Temp = Copy_pu8DataArr[Local_u8Iteration];
		Local_u32AccCRC = HAL_CRC_Accumulate(&hcrc,&Local_u32Temp, 1);
	}

	/* Reset CRC calculation unit */
	__HAL_CRC_DR_RESET(&hcrc);

	if(Local_u32AccCRC == Copy_u8HostCRC)
	{
		Local_u8CRCStatus = CRC_SUCCESS;
	}
	else
	{
		Local_u8CRCStatus = CRC_FAIL;
	}

	return Local_u8CRCStatus;
}
static void voidSendACK(uint8_t Copy_u8ReplyLength)
{
	uint8_t Local_u8AckBuffer[2] = {BL_ACK,Copy_u8ReplyLength};
	HAL_UART_Transmit(&huart6,Local_u8AckBuffer, 2,HAL_MAX_DELAY);
}
static void voidSendNACK(void)
{
	uint8_t Local_u8Nack = BL_NACK;
	HAL_UART_Transmit(&huart6, &Local_u8Nack, 1,HAL_MAX_DELAY);
}

void BL_voidHandleGetVersionCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8BLVersion, Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		Local_u8BLVersion = BL_Version;
		voidSendACK(1u);
		HAL_UART_Transmit(&huart6, &Local_u8BLVersion, 1,HAL_MAX_DELAY);
	}
	else
	{
		voidSendNACK();
	}
}
void BL_voidHandleGetHelpCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_pu8BLCommands[] =
		{
				BL_GET_VERSION,
				BL_GET_HELP,
				BL_GET_CID,
				BL_GET_RDP_STATUS,
				BL_GO_TO_ADDRESS,
				BL_FLASH_ERASE,
				BL_MEMORY_WRITE,
				BL_EM_RW_PROTECT,
				BL_MEMORY_READ,
				BL_READ_SECTOR_STATUS,
				BL_OTP_READ,
				BL_DISABLE_RW_PROTECT
		};
		voidSendACK(sizeof(Local_pu8BLCommands));
		HAL_UART_Transmit(&huart6, (uint8_t*)Local_pu8BLCommands, sizeof(Local_pu8BLCommands),HAL_MAX_DELAY);
	}
	else
	{
		voidSendNACK();
	}
}
void BL_voidHandleGetCIDCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint16_t Local_u16DeviceID = (DBGMCU_IDCODE_REG & 0x0FFF);
		voidSendACK(sizeof(Local_u16DeviceID));
		HAL_UART_Transmit(&huart6,(uint8_t*)&Local_u16DeviceID, sizeof(Local_u16DeviceID),HAL_MAX_DELAY);
	}
	else
	{
		voidSendNACK();
	}
}
void BL_voidHandleGetRDPStatusCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8RDPStatus = (uint8_t)((RDP_USER_OPTION_WORD >> 8) & 0xFF);
		voidSendACK(sizeof(Local_u8RDPStatus));
		HAL_UART_Transmit(&huart6, &Local_u8RDPStatus, sizeof(Local_u8RDPStatus),HAL_MAX_DELAY);
	}
	else
	{
		voidSendNACK();
	}
}
void BL_voidHandleGoToAddressCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8AddressValidStatus;
		uint32_t Local_u32Address = *((uint32_t*)&copy_pu8CmdPacket[2]);
		voidSendACK(1u);
		Local_u8AddressValidStatus = u8ValidAddress(Local_u32Address);
		HAL_UART_Transmit(&huart6, &Local_u8AddressValidStatus, 1,HAL_MAX_DELAY);

		if(Local_u8AddressValidStatus == VALID_ADDRESS)
		{
			/*Definite Pointer to function */
			void (*Local_pvFuncPtr)(void) = NULL;
			Local_u32Address |= 1;   /* Set bit 1 address to make T_Bit=1 */
			Local_pvFuncPtr = (void*)Local_u32Address;
			Local_pvFuncPtr();
		}
	}
	else
	{
		voidSendNACK();
	}
}
static uint8_t u8ValidAddress(uint32_t Copy_u32Address)
{
	uint8_t Local_u8AddressStatus;
	/* Address is valid in Flash or SRAM */
	if((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <= FLASH_END))
	{
		Local_u8AddressStatus = VALID_ADDRESS;
	}
	else if ((Copy_u32Address >= SRAM1_BASE) && (Copy_u32Address <= (SRAM1_BASE + (128*1024))))
	{
		Local_u8AddressStatus= VALID_ADDRESS;
	}
	else
	{
		Local_u8AddressStatus= INVALID_ADDRESS;
	}
	return Local_u8AddressStatus;
}
void BL_voidHandleFlashEraseCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8EraseStatus;
		voidSendACK(1u);
		Local_u8EraseStatus = u8ExecuteFlashErase(copy_pu8CmdPacket[2], copy_pu8CmdPacket[3]);
		HAL_UART_Transmit(&huart6, &Local_u8EraseStatus, 1, HAL_MAX_DELAY);
	}
	else
	{
		voidSendNACK();
	}
}
static uint8_t u8ExecuteFlashErase(uint8_t Copy_u8SectorNumber, uint8_t Copy_u8NumberOfSectors)
{
	HAL_StatusTypeDef Local_ErrorStatus = HAL_OK;
	if((Copy_u8SectorNumber > 7) && (Copy_u8SectorNumber != 0xFF))
	{
		Local_ErrorStatus = HAL_ERROR;
	}
	else if((Copy_u8NumberOfSectors > 8) && (Copy_u8SectorNumber != 0xFF))
	{
		Local_ErrorStatus = HAL_ERROR;
	}
	else
	{
		FLASH_EraseInitTypeDef Local_MyErase;
		uint32_t Local_SectorError;
		if(Copy_u8NumberOfSectors == 0xFF)
		{
			/* mass erase operation is required */
			Local_MyErase.TypeErase = FLASH_TYPEERASE_MASSERASE;
			Local_MyErase.Banks = FLASH_BANK_1;
			Local_MyErase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
		}
		else
		{
			/* Sector erase operation is required */
			uint8_t Local_u8RemainingSectors =  (8 - Copy_u8SectorNumber);
			if(Copy_u8NumberOfSectors > Local_u8RemainingSectors)
			{
				Copy_u8NumberOfSectors = Local_u8RemainingSectors;
			}
			Local_MyErase.TypeErase = FLASH_TYPEERASE_SECTORS;
			Local_MyErase.Sector = Copy_u8SectorNumber;
			Local_MyErase.NbSectors = Copy_u8NumberOfSectors;
			Local_MyErase.Banks = FLASH_BANK_1;
			Local_MyErase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
		}
		/* unlock the flash before erasing */
		HAL_FLASH_Unlock();

		Local_ErrorStatus = HAL_FLASHEx_Erase(&Local_MyErase, &Local_SectorError);

		/* lock the flash again */
		HAL_FLASH_Lock();
	}
	return Local_ErrorStatus;
}
void BL_voidHandleMemoryWriteCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8WritingStatus;
		uint32_t Local_u32Address = *((uint32_t*)&copy_pu8CmdPacket[2]);
		uint8_t Local_u8AddressStatus = u8ValidAddress(Local_u32Address);
		voidSendACK(1u);
		if(Local_u8AddressStatus == VALID_ADDRESS)
		{
			Local_u8WritingStatus = u8ExecuteMemoryWrite(&copy_pu8CmdPacket[7], Local_u32Address, copy_pu8CmdPacket[6]);
		}
		else
		{
			Local_u8WritingStatus = WRITING_ERORR;
		}
		HAL_UART_Transmit(&huart6, &Local_u8WritingStatus, 1,HAL_MAX_DELAY);
	}
	else
	{
		voidSendNACK();
	}
}
static uint8_t u8ExecuteMemoryWrite(uint8_t* Copy_pu8DataArr, uint32_t Copy_u32Address, uint8_t Copy_u8Length)
{
	uint8_t Local_u8ErrorStatus = HAL_OK;
	if((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <= FLASH_END))
	{
		uint8_t Local_u8Itaretor;
		/* unlock the flash before writing */
		HAL_FLASH_Unlock();

		for(Local_u8Itaretor=0;Local_u8Itaretor<Copy_u8Length;Local_u8Itaretor++)
		{
			Local_u8ErrorStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,Copy_u32Address+Local_u8Itaretor,Copy_pu8DataArr[Local_u8Itaretor]);
		}

		/* lock the flash again */
		HAL_FLASH_Lock();
	}
	else
	{
		/* writing in SRAM */
		uint8_t Local_u8Itaretor;
		uint8_t* Local_pu8Dest = (uint8_t*)Copy_u32Address;
		for(Local_u8Itaretor=0;Local_u8Itaretor<Copy_u8Length;Local_u8Itaretor++)
		{
			Local_pu8Dest[Local_u8Itaretor] = Copy_pu8DataArr[Local_u8Itaretor];
		}

	}
	return Local_u8ErrorStatus;
}
void BL_voidHandleMemoryReadCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8DataLen,Local_u8Itaretor;
		uint8_t Local_u8ReadBuffer[256]; /* Maximum buffer size to hold data to be read */
		uint32_t Local_u32MemAddress;

		/* Extract memory address from the command packet (bytes 2 to 5) */
        Local_u32MemAddress = *((uint32_t*)(copy_pu8CmdPacket + 2));

        /* Extract data length to be read from the command packet (byte 6) */
        Local_u8DataLen = copy_pu8CmdPacket[6];

        /* Check if the requested address and length are valid */
        if ((u8ValidAddress(Local_u32MemAddress) == VALID_ADDRESS) && (Local_u8DataLen <= 256))
        {
            /* Read the requested data from memory */
            for (Local_u8Itaretor = 0; Local_u8Itaretor < Local_u8DataLen; Local_u8Itaretor++)
            {
                Local_u8ReadBuffer[Local_u8Itaretor] = *((uint8_t*)(Local_u32MemAddress + Local_u8Itaretor));
            }

            /* Send ACK with the size of the response */
            voidSendACK(Local_u8DataLen);

            /* Send the data to the host */
            HAL_UART_Transmit(&huart6, Local_u8ReadBuffer, Local_u8DataLen,HAL_MAX_DELAY);
        }
	}
	else
	{
		voidSendNACK();
	}
}
void BL_voidHandleEnableRWProtectCmd(uint8_t* copy_pu8CmdPacket)
{
    uint8_t Local_u8CRCStatus, Local_u8CmdLen;
    uint32_t Local_u32HostCRC;

    Local_u8CmdLen = copy_pu8CmdPacket[0] + 1;
    Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
    Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen - 4), Local_u32HostCRC);

    if (Local_u8CRCStatus == CRC_SUCCESS)
    {
    	uint8_t Local_u8Status = PROTECTION_FAIL; /* Initialize status to failure (0) */
        FLASH_OBProgramInitTypeDef OBInit; /* Option bytes structure */
        uint8_t Local_u8ProtectionMode = copy_pu8CmdPacket[2]; /* Protection type (Write or Read/Write)*/

        /* Step 1: Unlock Flash and Option Bytes */
        HAL_FLASH_Unlock();
        HAL_FLASH_OB_Unlock();

        /* Step 2: Configure Option Bytes */
        HAL_FLASHEx_OBGetConfig(&OBInit); /* Read current configuration*/
        OBInit.OptionType = OPTIONBYTE_WRP;  /* Set option type to Write Protection*/
        OBInit.WRPState = OB_WRPSTATE_ENABLE; /* Enable Write Protection*/

        /* If Read and Write protection is required, enable RDP Level 1 */
        if (Local_u8ProtectionMode == 2)
        {
            OBInit.OptionType |= OPTIONBYTE_RDP;
            OBInit.RDPLevel = OB_RDP_LEVEL_1; /* Enable Read and Write Protection */
        }

        /* Step 3: Program Option Bytes */
        if (HAL_FLASHEx_OBProgram(&OBInit) == HAL_OK)
        {
            /* Step 4: Launch Option Bytes Programming */
            if (HAL_FLASH_OB_Launch() == HAL_OK)
            {
                Local_u8Status = PROTECTION_SUCCESS; /* Success*/
            }
        }

        /* Step 5: Lock Flash and Option Bytes */
        HAL_FLASH_OB_Lock();
        HAL_FLASH_Lock();

        /* Send ACK to confirm CRC success */
        voidSendACK(1u);
        HAL_UART_Transmit(&huart6, &Local_u8Status, 1,HAL_MAX_DELAY);  /*  Send status (1 = success, 0 = failure)*/
    }
    else
    {
        voidSendNACK();  /*  Send NACK if CRC check fails*/
    }
}

void BL_voidHandleDisableRWProtectCmd(uint8_t* copy_pu8CmdPacket)
{
    uint8_t Local_u8CRCStatus, Local_u8CmdLen;
    uint32_t Local_u32HostCRC;

    Local_u8CmdLen = copy_pu8CmdPacket[0] + 1;  /* Command length + 1 */
    Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4)); /* Host-provided CRC */
    Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen - 4), Local_u32HostCRC);

    if (Local_u8CRCStatus == CRC_SUCCESS)
    {
    	uint8_t Local_u8Status = PROTECTION_FAIL;  /* Initialize status to failure */
        FLASH_OBProgramInitTypeDef OBInit; /* Option bytes structure */

        /* Step 1: Unlock Flash and Option Bytes */
        HAL_FLASH_Unlock();
        HAL_FLASH_OB_Unlock();

        /* Step 2: Disable Write and Read/Write Protection */
        HAL_FLASHEx_OBGetConfig(&OBInit);      /* Read current configuration*/
        OBInit.OptionType = OPTIONBYTE_WRP;    /* Set option type to Write Protection*/
        OBInit.WRPState = OB_WRPSTATE_DISABLE; /* Disable Protection*/

        /* Step 3: Program Option Bytes */
        if (HAL_FLASHEx_OBProgram(&OBInit) == HAL_OK)
        {
            /* Step 4: Launch Option Bytes Programming */
            if (HAL_FLASH_OB_Launch() == HAL_OK)
            {
                Local_u8Status = PROTECTION_SUCCESS; /* Success*/
            }
        }

        /* Step 5: Lock Flash and Option Bytes */
        HAL_FLASH_OB_Lock();
        HAL_FLASH_Lock();

        voidSendACK(1u); /* Send ACK */
        HAL_UART_Transmit(&huart6, &Local_u8Status, 1,HAL_MAX_DELAY); /* Send status (1 = success, 0 = failure)*/
    }
    else
    {
        voidSendNACK(); /* Send NACK if CRC check fails*/
    }
}

void BL_voidHandleReadSectorStatusCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0]+1;        /* The first byte includes the length to follow */
	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));
	Local_u8CRCStatus = BL_u8VerifyCRC(copy_pu8CmdPacket,(Local_u8CmdLen - 4),Local_u32HostCRC);
	if(Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint16_t Local_u16OptionBytes;
		uint8_t Local_u8SectorStatus;

        /* Read the option bytes (FLASH_OPTR register contains sector protection status) */
        Local_u16OptionBytes = FLASH->OPTCR;  /*  Read option control register */

        /*  Extract the protection status from the appropriate bits (sector 0-7 protection stored in OPTCR[16:23]) */
        Local_u8SectorStatus = (uint8_t)((Local_u16OptionBytes >> 16) & 0xFF);

        /*  Send ACK with the size of the response (1 byte for sector status) */
        voidSendACK(1u);

        /*  Send the sector protection status back to the host */
        HAL_UART_Transmit(&huart6, &Local_u8SectorStatus, 1,HAL_MAX_DELAY);
	}
	else
	{
		voidSendNACK();
	}
}
