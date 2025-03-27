/*
 * FLASH_program.c
 *
 *  Created on: Mar 25, 2025
 *      Author: Ahmed Ragab
 */

#include "stm32f401xx.h"
#include "FLASH_interface.h"
#include "FLASH_private.h"


/**
 * @brief  Waits until the FLASH is not busy.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_TIMEOUT if it takes too long)
 */
FLASH_Status_t FLASH_WaitForNotBusy(void)
{
    uint32_t Timeout = TIME_OUT; /* Timeout counter to prevent infinite loop */
    FLASH_Status_t Status = FLASH_OK;
    while ((FLASH->SR & FLASH_SR_BSY) && (Timeout > 0))
    {
        Timeout--;
    }
    if (Timeout == 0)
    {
    	Status = FLASH_TIMEOUT; /* Return timeout error if the loop exits due to timeout */
    }
    return Status; /* FLASH is ready */
}

/**
 * @brief Unlock the FLASH control register
 */
FLASH_Status_t FLASH_Unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK)
    {
    	/* Authorize the FLASH Registers access */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
    return (FLASH->CR & FLASH_CR_LOCK) ? FLASH_ERROR : FLASH_OK;
}

/**
 * @brief Lock the FLASH control register
 */
FLASH_Status_t FLASH_Lock(void)
{
	/* Set the LOCK Bit to lock the FLASH Registers access */
    FLASH->CR |= FLASH_CR_LOCK;
    return FLASH_OK;
}

FLASH_Status_t FLASHEx_Erase(FLASH_Erase_t *pEraseInit, uint32_t *SectorError)
{
    FLASH_Status_t Status = FLASH_ERROR;

    if (pEraseInit == NULL || SectorError == NULL)
    {
        Status = FLASH_NULL_PTR;
    }
    else if (FLASH_WaitForNotBusy() != FLASH_OK)
    {
        Status = FLASH_BUSY;
    }
    else
    {
        /* Select MASS Erase Type */
        if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASS)
        {
            /* Mass Erase (Entire Bank) */
            if (pEraseInit->Banks == FLASH_BANK_1)
            {
                FLASH->CR |= FLASH_CR_MER; /* Set Mass Erase for Bank 1 */
            }
            else if (pEraseInit->Banks == FLASH_BANK_2)
            {
                FLASH->CR |= FLASH_CR_MER | FLASH_CR_BKER; /* Mass Erase for Bank 2 */
            }

            FLASH->CR |= FLASH_CR_STRT; /* Start Erase */

            /* Wait for completion */
            while (FLASH->SR & FLASH_SR_BSY);

            /* Check for errors */
            if (FLASH->SR & FLASH_SR_EOP)
            {
                FLASH->SR |= FLASH_SR_EOP; /* Clear End of Operation flag */
                Status = FLASH_OK;
            }
            else
            {
            	Status = FLASH_ERROR;
            }
        }
        else if (pEraseInit->TypeErase == FLASH_TYPEERASE_SECTOR)
        {
            /* Sector Erase */
        	uint32_t Count = 0;
            for (Count = 0; Count < pEraseInit->NbSectors; Count++)
            {
                uint32_t CurrentSector = pEraseInit->Sector + Count;

                /* Configure the sector number and erase mode */
                FLASH->CR &= ~FLASH_CR_SNB; /* Clear previous sector */
                FLASH->CR |= (CurrentSector << FLASH_CR_SNB_Pos) | FLASH_CR_SER;

                /* Set voltage range */
                FLASH->CR |= (pEraseInit->VoltageRange << FLASH_CR_PSIZE_Pos);

                /* Start erase */
                FLASH->CR |= FLASH_CR_STRT;

                /* Wait for completion */
                while (FLASH->SR & FLASH_SR_BSY);

                /* Check for errors */
                if (FLASH->SR & FLASH_SR_EOP)
                {
                    FLASH->SR |= FLASH_SR_EOP; /* Clear End of Operation flag */
                }
                else
                {
                    *SectorError = CurrentSector;
                    Status = FLASH_ERROR;
                    break; /* Stop on first error */
                }
            }
        }
        else
        {
        	Status = FLASH_ERROR;
        }
    }
    return Status;
}


FLASH_Status_t FLASH_Program(FLASH_ProgramType_t TypeProgram, uint32_t Address, uint64_t Data)
{
    FLASH_Status_t Status = FLASH_OK;
    if (FLASH_WaitForNotBusy() != FLASH_OK)
    {
        Status = FLASH_BUSY; /* if FLASH is busy */
    }
    else
    {
        /* Configure the FLASH program size */
        FLASH->CR &= ~FLASH_CR_PSIZE;
        FLASH->CR |= (TypeProgram << FLASH_CR_PSIZE_Pos);
        /* Enable programming */
        FLASH->CR |= FLASH_CR_PG;
        /* Perform programming based on the selected type */
        switch (TypeProgram)
        {
            case FLASH_TYPEPROGRAM_BYTE:       *(volatile uint8_t*)Address = (uint8_t)Data; break;
            case FLASH_TYPEPROGRAM_HALFWORD:   *(volatile uint16_t*)Address = (uint16_t)Data; break;
            case FLASH_TYPEPROGRAM_WORD:       *(volatile uint32_t*)Address = (uint32_t)Data; break;
            case FLASH_TYPEPROGRAM_DOUBLEWORD: *(volatile uint64_t*)Address = Data; break;
            default:  Status = FLASH_ERROR;
        }
        if(Status == FLASH_OK)
        {
            /* Wait for the operation to complete */
            while (FLASH->SR & FLASH_SR_BSY);
            /* Disable programming */
            FLASH->CR &= ~FLASH_CR_PG;
            /* Check if operation was successful */
            if (FLASH->SR & FLASH_SR_EOP)
            {
                FLASH->SR |= FLASH_SR_EOP;  /* Clear EOP flag */
                Status = FLASH_OK;
            }
            else
            {
                Status = FLASH_ERROR;
            }
        }
    }
    return Status;
}


/**
 * @brief  Launch the option byte loading.
 * @retval FLASH_Status_t
 */
FLASH_Status_t FLASH_OB_Launch(void)
{
	 FLASH_Status_t Status = FLASH_OK;
    /* Set the OPTSTRT bit in OPTCR register to apply changes */
    FLASH->OPTCR |= FLASH_OPTCR_OBL_LAUNCH;
    /* Wait for FLASH operation to complete */
    while (FLASH->SR & FLASH_SR_BSY);
    /* The device resets automatically after this operation,
       so this function technically never returns */
    return Status;
}

/**
 * @brief  Unlocks the FLASH Option Control Register (OPTCR) to allow modification.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if already unlocked)
 */
FLASH_Status_t FLASH_OB_Unlock(void)
{
	FLASH_Status_t Status = FLASH_ERROR;
    if (FLASH->OPTCR & FLASH_OPTCR_OPTLOCK) /* Check if option bytes are locked */
    {
        FLASH->OPTKEYR = FLASH_OPT_KEY1;  /* Write first unlock key */
        FLASH->OPTKEYR = FLASH_OPT_KEY2;  /* Write second unlock key */
        Status = FLASH_OK;
    }
    return Status; /* Already unlocked */
}

/**
 * @brief  Locks the FLASH Option Control Register (OPTCR) to prevent modification.
 * @retval FLASH_Status_t (FLASH_OK if successful)
 */
FLASH_Status_t FLASH_OB_Lock(void)
{
    FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK; /* Set the OPTLOCK bit to lock option bytes */
    return FLASH_OK;
}

/**
 * @brief  Gets the current configuration of the Option Bytes.
 * @param  pOBInit: Pointer to a FLASH_OBProgramInitTypeDef structure that will hold the configuration.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if failed)
 */
FLASH_Status_t FLASHEx_OBGetConfig(FLASH_OBProgram_t *pOBInit)
{
	FLASH_Status_t Status = FLASH_OK;
	if (pOBInit == NULL)
    {
		Status = FLASH_NULL_PTR;
    }
	else
	{
	    /* Read the option byte values from FLASH registers */
	    pOBInit->OptionType = FLASH->OPTCR & FLASH_OPTCR_OPTLOCK;  /* Option lock status */
	    pOBInit->WRPState = (FLASH->OPTCR & FLASH_OPTCR_WRP) >> FLASH_OPTCR_WRP_Pos; /* Write protection */
	    pOBInit->BORLevel = (FLASH->OPTCR & FLASH_OPTCR_BOR_LEV) >> FLASH_OPTCR_BOR_LEV_Pos; /* Brownout Reset level */
	    pOBInit->RDPLevel = (FLASH->OPTCR & FLASH_OPTCR_RDP) >> FLASH_OPTCR_RDP_Pos; /* Read protection level */
	    pOBInit->USERConfig = (FLASH->OPTCR & FLASH_OPTCR_USER) >> FLASH_OPTCR_USER_Pos; /*User-defined option byte settings.*/
	    pOBInit->WRPSector = (FLASH->OPTCR & FLASH_OPTCR_WRP) >> FLASH_OPTCR_WRP_Pos;/*the sector(s) protected against write operations.*/
	}
	return Status;
}

/**
 * @brief  Programs the Option Bytes.
 * @param  pOBInit: Pointer to a FLASH_OBProgramInitTypeDef structure with the new configuration.
 * @retval FLASH_Status_t (FLASH_OK if successful, FLASH_ERROR if failed)
 */
FLASH_Status_t FLASHEx_OBProgram(FLASH_OBProgram_t *pOBInit)
{
	FLASH_Status_t Status = FLASH_OK;
	if (pOBInit == NULL)
    {
		Status = FLASH_NULL_PTR;
    }
	else
	{

	    /* Clear existing option byte values */
	    FLASH->OPTCR &= ~(FLASH_OPTCR_WRP | FLASH_OPTCR_RDP | FLASH_OPTCR_BOR_LEV | FLASH_OPTCR_USER);

	    /* Set new option byte values */
	    FLASH->OPTCR |= (pOBInit->WRPState  << FLASH_OPTCR_WRP_Pos)  |
	                    (pOBInit->RDPLevel  << FLASH_OPTCR_RDP_Pos)  |
	                    (pOBInit->BORLevel  << FLASH_OPTCR_BOR_LEV_Pos) |
	                    (pOBInit->USERConfig << FLASH_OPTCR_USER_Pos);

	    /* Start the option byte programming */
	    FLASH->OPTCR |= FLASH_OPTCR_OPTSTRT;

	    /* Wait for operation to complete */
	    while (FLASH->SR & FLASH_SR_BSY);

	    /* Verify if programming was successful */
	    if (FLASH->SR & FLASH_SR_EOP)
	    {
	        FLASH->SR |= FLASH_SR_EOP;  /* Clear EOP flag */
	        Status = FLASH_OK;
	    }
	    else
	    {
	        Status = FLASH_ERROR;
	    }
	}
	return Status;
}


