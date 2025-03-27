/*
 * FLASH_private.h
 *
 *  Created on: Mar 25, 2025
 *      Author: Ahmed Ragab
 */

#ifndef FLASH_PRIVATE_H_
#define FLASH_PRIVATE_H_

#define TIME_OUT            0xFFFFFFFF
#define FLASH_CR_LOCK       (1U << 31)  /*!< Bit 31: LOCK bit in FLASH_CR register */
#define FLASH_KEY1          0x45670123U /*!< First unlock key for FLASH_CR */
#define FLASH_KEY2          0xCDEF89ABU /*!< Second unlock key for FLASH_CR */

#define FLASH_CR_MER       (1 << 2)  /*!< Mass Erase Bit */
#define FLASH_CR_SER       (1 << 1)  /*!< Sector Erase Bit */
#define FLASH_CR_STRT      (1 << 16) /*!< Start Erase Bit */
#define FLASH_CR_SNB_Pos   3U        /*!< Sector Number Bit Position */
#define FLASH_CR_SNB       (0xF << FLASH_CR_SNB_Pos) /*!< Sector Number Mask */
#define FLASH_SR_BSY       (1 << 16) /*!< Flash Busy Flag */
#define FLASH_SR_EOP       (1 << 0)  /*!< End of Operation Flag */
#define FLASH_CR_PSIZE_Pos 8U   /* Position of the PSIZE bits in FLASH_CR register */
#define FLASH_CR_BKER      (1U << 11) /* Bank Erase bit (used in Dual-Bank mode for selecting Bank 2 erase) */
#define FLASH_CR_PSIZE_Pos 8U                                /*!< Position of PSIZE bits in FLASH_CR register */
#define FLASH_CR_PSIZE     (0x3U << FLASH_CR_PSIZE_Pos)     /*!< PSIZE mask (bit 8 and 9 define the program size) */
#define FLASH_CR_PG        (1U << 0)                        /*!< Programming bit (1: Flash programming activated) */

#define FLASH_OPT_KEY1               0x08192A3BUL /* Option Bytes Unlock Key 1 */
#define FLASH_OPT_KEY2               0x4C5D6E7FUL /* Option Bytes Unlock Key 2 */
#define FLASH_OPTCR_OBL_LAUNCH       (1U << 1)  /* Option Control Register - Option Byte Launch */
#define FLASH_OPTCR_OPTLOCK          (1U << 0)  /* Option Control Register - Option Byte Lock */

#define FLASH_OPTCR_WRP           (0xFFFU << 8)  /*!< Write protection mask */
#define FLASH_OPTCR_WRP_Pos       8U  /*!< Position of write protection bits */

#define FLASH_OPTCR_BOR_LEV       (0x3U << 2)  /*!< Brown-Out Reset (BOR) Level mask */
#define FLASH_OPTCR_BOR_LEV_Pos   2U  /*!< Position of BOR level bits */

#define FLASH_OPTCR_RDP           (0xFFU << 16)  /*!< Read protection level mask */
#define FLASH_OPTCR_RDP_Pos       16U  /*!< Position of read protection level bits */

#define FLASH_OPTCR_USER          (0xFFU << 24)  /*!< User option byte configuration mask */
#define FLASH_OPTCR_USER_Pos      24U  /*!< Position of user configuration bits */

#define FLASH_OPTCR_WRP           (0xFFFU << 8)  /*!< Write protection mask */
#define FLASH_OPTCR_WRP_Pos       8U  /*!< Position of write protection bits */
#define FLASH_OPTCR_OPTSTRT     (1U << 1)  /*!< Option byte start bit */



#endif /* FLASH_PRIVATE_H_ */
