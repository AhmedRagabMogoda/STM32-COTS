/*
 *  CAN_Program.c
 *
 *  Created on: Feb 28, 2025
 *  Author: Ahmed Ragab
 */

#include <stdint.h>
#include "CAN_private.h"
#include "CAN_interface.h"

/************************* Global Variable********************************/

/* Array of pointers to CAN peripheral base addresses */
static CAN_RegDef_t* CAN[CAN_PERIPHERAL_NUM] ={bxCAN1,bxCAN2};

/************************  Implementation Function  **********************/

CAN_Status_t CAN_Init(CAN_Config_t* Copy_CANConfig)
{
	CAN_Status_t Local_ErrorState=CAN_OK;
	if(Copy_CANConfig != NULL)
	{
		/* Enter initialization mode */
		CAN[Copy_CANConfig->CANNumber]->MCR |= CAN_MCR_INRQ;
		/* Wait until initialization mode is acknowledged */
		while(!(CAN[Copy_CANConfig->CANNumber]->MSR & CAN_MSR_INAK));
		/* Configure operational mode */
		CAN[Copy_CANConfig->CANNumber]->BTR |= (Copy_CANConfig->Mode << MODE_PIN_ACCESS);
		/* Configure bit timing parameters */
		CAN[Copy_CANConfig->CANNumber]->BTR = (Copy_CANConfig->SyncJumpWidth << SJW_PIN_ACCESS) |
		                                      (Copy_CANConfig->TimeSeg1 << TS1_PIN_ACCESS) |
		                                      (Copy_CANConfig->TimeSeg2 << TS2_PIN_ACCESS) |
		                                      ((Copy_CANConfig->Prescaler - 1) << BRP_PIN_ACCESS);
		/* Configure automatic settings */
		CAN[Copy_CANConfig->CANNumber]->MCR |= (Copy_CANConfig->AutoBusOff << CAN_MCR_ABOM) |
                                               (Copy_CANConfig->AutoWakeUp << CAN_MCR_AWUM) |
                                               (Copy_CANConfig->AutoRetransmission << CAN_MCR_NART) |
                                               (Copy_CANConfig->ReceiveFifoLocked << CAN_MCR_RFLM) |
                                               (Copy_CANConfig->TransmitFifoPriority << CAN_MCR_TXFP);
		/* Exit initialization mode */
		CAN[Copy_CANConfig->CANNumber]->MCR &= ~CAN_MCR_INRQ;
		/* Wait until initialization mode is exited */
		while (CAN[Copy_CANConfig->CANNumber]->MSR & CAN_MSR_INAK);
	}
	else
	{
		Local_ErrorState=CAN_PTR_ERROR;
	}
	return Local_ErrorState;
}

CAN_Status_t CAN_ConfigFilter(CAN_Config_t *Copy_CANConfig, const CAN_Filter_t *Copy_FilterConfig)
{
	CAN_Status_t Local_ErrorState=CAN_OK;
	if(Copy_CANConfig != NULL && Copy_FilterConfig != NULL)
	{
		 /* Enter filter initialization mode */
		CAN[Copy_CANConfig->CANNumber]->FMR |= (FINIT_MASK << CAN_FMR_FINIT);
		/*  Disable Selected filter bank before modifying its settings */
		CAN[Copy_CANConfig->CANNumber]->FA1R &= ~(FILTER_MASK << Copy_FilterConfig->FilterBank);
		/* Configure filter scale */
		if(Copy_FilterConfig->FilterScale == CAN_FILTER_SCALE_32BIT)
		{
			CAN[Copy_CANConfig->CANNumber]->FS1R |= (FILTER_MASK << Copy_FilterConfig->FilterBank);
		}
		else
		{
			CAN[Copy_CANConfig->CANNumber]->FS1R &= ~(FILTER_MASK << Copy_FilterConfig->FilterBank);
		}
		/* Configure filter mode */
		if(Copy_FilterConfig->FilterMode == CAN_FILTER_MODE_ID_LIST)
		{
			CAN[Copy_CANConfig->CANNumber]->FM1R |= (FILTER_MASK << Copy_FilterConfig->FilterBank);
		}
		else
		{
			CAN[Copy_CANConfig->CANNumber]->FM1R &= ~(FILTER_MASK << Copy_FilterConfig->FilterBank);
		}
		/* Assign filter values */
		CAN[Copy_CANConfig->CANNumber]->FilterRegister[Copy_FilterConfig->FilterBank].FR1 = (Copy_FilterConfig->FilterIdHigh << 16) | (Copy_FilterConfig->FilterIdLow);
		CAN[Copy_CANConfig->CANNumber]->FilterRegister[Copy_FilterConfig->FilterBank].FR2 = (Copy_FilterConfig->FilterMaskIdHigh << 16) | (Copy_FilterConfig->FilterMaskIdLow);
		/* Assign FIFO */
		if(Copy_FilterConfig->FilterFIFO == CAN_FILTER_FIFO1)
		{
			CAN[Copy_CANConfig->CANNumber]->FFA1R |= (FILTER_MASK << Copy_FilterConfig->FilterBank);
		}
		else
		{
			CAN[Copy_CANConfig->CANNumber]->FFA1R &= ~(FILTER_MASK << Copy_FilterConfig->FilterBank);
		}
		/* Enable or disable filter */
		if(Copy_FilterConfig->Activation == CAN_FILTER_ENABLE)
		{
			CAN[Copy_CANConfig->CANNumber]->FA1R |= (FILTER_MASK << Copy_FilterConfig->FilterBank);
		}
		/* Exit filter initialization mode */
		CAN[Copy_CANConfig->CANNumber]->FMR &= ~(FINIT_MASK << CAN_FMR_FINIT);
	}
	else
	{
		Local_ErrorState=CAN_PTR_ERROR;
	}
	return Local_ErrorState;
}

CAN_Status_t CAN_Start(CAN_Config_t* Copy_CANConfig)
{
	CAN_Status_t Local_ErrorState=CAN_OK;
	if(Copy_CANConfig != NULL)
	{
		CAN[Copy_CANConfig->CANNumber]->MCR &= ~CAN_MCR_SLEEP;
		CAN[Copy_CANConfig->CANNumber]->MCR &= ~CAN_MCR_INRQ;
		while (CAN[Copy_CANConfig->CANNumber]->MSR & CAN_MSR_INAK);
	}
	else
	{
		Local_ErrorState=CAN_PTR_ERROR;
	}
	return Local_ErrorState;
}

CAN_Status_t CAN_Stop(CAN_Config_t* Copy_CANConfig)
{
	CAN_Status_t Local_ErrorState=CAN_OK;
	if(Copy_CANConfig != NULL)
	{
		/* Enter initialization mode */
		CAN[Copy_CANConfig->CANNumber]->MCR |= CAN_MCR_INRQ;
		/* Wait until initialization mode is acknowledged */
		while(!(CAN[Copy_CANConfig->CANNumber]->MSR & CAN_MSR_INAK));
		/* Enter sleep mode */
		CAN[Copy_CANConfig->CANNumber]->MCR |= CAN_MCR_SLEEP;
	}
	else
	{
		Local_ErrorState=CAN_PTR_ERROR;
	}
	return Local_ErrorState;
}

CAN_Status_t CAN_AddTxMessage(CAN_Config_t* Copy_CANConfig, const CAN_TxHeader_t *pTxHeader, const uint8_t *pData, uint8_t *pTxMailbox)
{
	CAN_Status_t Local_ErrorState = CAN_OK;
	if(Copy_CANConfig != NULL && pTxHeader != NULL && pData != NULL && pTxMailbox != NULL)
	{
		/* Find an Available Transmit Mailbox */
		uint8_t TxMailBox = (CAN[Copy_CANConfig->CANNumber]->TSR & CAN_TSR_TME0) ? Mailbox0 :
				            (CAN[Copy_CANConfig->CANNumber]->TSR & CAN_TSR_TME1) ? Mailbox1 :
				            (CAN[Copy_CANConfig->CANNumber]->TSR & CAN_TSR_TME2) ? Mailbox2 : MailboxesBusy;
		if(TxMailBox != MailboxesBusy)
		{
			/* Configure the Transmit Identifier
			 * Identifier Extension Bit → Specifies if the ID is standard (11-bit) or extended (29-bit)
			 * Remote Transmission Request Bit → Specifies if the frame is a data frame or remote frame */
			CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TIR = (pTxHeader->RTR << RTR_PIN_ACCESS) |
					                                                    (pTxHeader->IDE << IDE_PIN_ACCESS);
			if(pTxHeader->IDE)
			{
				/* ID is extended (29-bit) */
				CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TIR |= (pTxHeader->ExtId << ExtId_PIN_ACCESS);
			}
			else
			{
				/* ID is standard (11-bit) */
				CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TIR |= (pTxHeader->StdId << StdId_PIN_ACCESS);
			}
			/* Configure Data Length Code (DLC) */
			CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TDTR = pTxHeader->DLC;
			/* Load Data into the Mailbox */
			CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TDLR = 0;
			CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TDHR = 0;

			CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TDLR = ((pTxHeader->DLC > 0) ? ((uint32_t)pData[0] << 0) : 0)  |
					                                                     ((pTxHeader->DLC > 1) ? ((uint32_t)pData[1] << 8) : 0)  |
																		 ((pTxHeader->DLC > 2) ? ((uint32_t)pData[2] << 16) : 0) |
																		 ((pTxHeader->DLC > 3) ? ((uint32_t)pData[3] << 24) : 0);

			CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TDHR = ((pTxHeader->DLC > 4) ? ((uint32_t)pData[4] << 0) : 0)  |
                                                                         ((pTxHeader->DLC > 5) ? ((uint32_t)pData[5] << 8) : 0)  |
				                                                      	 ((pTxHeader->DLC > 6) ? ((uint32_t)pData[6] << 16) : 0) |
				                                                     	 ((pTxHeader->DLC > 7) ? ((uint32_t)pData[7] << 24) : 0);
			/* Request Transmission*/
			CAN[Copy_CANConfig->CANNumber]->sTxMailBox[TxMailBox].TIR |= CAN_TI0R_TXRQ;
			/* Return the Mailbox Index */
			*pTxMailbox = TxMailBox;
		}
		else
		{
			Local_ErrorState = CAN_BUSY;
		}
	}
	else
	{
		Local_ErrorState = CAN_PTR_ERROR;
	}
	return Local_ErrorState;
}

CAN_Status_t CAN_GetRxMessage(CAN_Config_t* Copy_CANConfig, CAN_FilterFIFO_t RxFIFO, CAN_RxHeader_t* pRxHeader, uint8_t* pData)
{
	CAN_Status_t Local_ErrorState=CAN_OK;
	if(Copy_CANConfig != NULL && pRxHeader != NULL && pData != NULL)
	{
		/* Check if there is data in FIFO and Determine FIFO register base */
		uint32_t FIFOIndex = ((CAN[Copy_CANConfig->CANNumber]->RF0R & CAN_RF0R_FMP0) && (RxFIFO == FIFO0)) ? FIFO0 :
				             ((CAN[Copy_CANConfig->CANNumber]->RF1R & CAN_RF1R_FMP1) && (RxFIFO == FIFO1)) ? FIFO1 : FIFO_EMPTY;
		if(FIFOIndex != FIFO_EMPTY)
		{
			uint32_t MailboxIndex = 0;
			/*
			// Determine number of messages in FIFO
			uint32_t MessageCount = (RxFIFO == FIFO0) ?
									(CAN[Copy_CANConfig->CANNumber]->RF0R & CAN_RF0R_FMP0) :
									(CAN[Copy_CANConfig->CANNumber]->RF1R & CAN_RF1R_FMP1);
			// Determine which Mailbox within the FIFO to read from
			MailboxIndex = (MessageCount > 2) ? 2 :
			               (MessageCount > 1) ? 1 : 0;
			*/

			/* Read message ID and type */
			pRxHeader->IDE = (CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RIR & CAN_RI0R_IDE) ? 1 : 0;
			pRxHeader->RTR = (CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RIR & CAN_RI0R_RTR) ? 1 : 0;
		    if(pRxHeader->IDE)
		    {
		        /* Extended ID (29-bit) */
		        pRxHeader->ExtId = ((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RIR >> ExtId_PIN_ACCESS) & 0x1FFFFFFF);
		    }
		    else
		    {
		        /* Standard ID (11-bit) */
		        pRxHeader->StdId = ((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RIR >> StdId_PIN_ACCESS) & 0x7FF);
		    }
		    /* Read DLC (Data Length Code) */
		    pRxHeader->DLC = (CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDTR & 0x0F);
		    /* Read received data (up to 8 bytes) based on DLC */
		    if(pRxHeader->DLC > 0) pData[0] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDLR >> 0) & 0xFF);
		    if(pRxHeader->DLC > 1) pData[1] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDLR >> 8) & 0xFF);
		    if(pRxHeader->DLC > 2) pData[2] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDLR >> 16) & 0xFF);
		    if(pRxHeader->DLC > 3) pData[3] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDLR >> 24) & 0xFF);
		    if(pRxHeader->DLC > 4) pData[4] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDHR >> 0) & 0xFF);
		    if(pRxHeader->DLC > 5) pData[5] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDHR >> 8) & 0xFF);
		    if(pRxHeader->DLC > 6) pData[6] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDHR >> 16) & 0xFF);
		    if(pRxHeader->DLC > 7) pData[7] = (uint8_t)((CAN[Copy_CANConfig->CANNumber]->sFIFOMailBox[FIFOIndex][MailboxIndex].RDHR >> 24) & 0xFF);
		    /* Release FIFO (clear RFOM bit to free up space) */
		     if(RxFIFO == FIFO0) CAN[Copy_CANConfig->CANNumber]->RF0R |= CAN_RF0R_RFOM0;
		     else CAN[Copy_CANConfig->CANNumber]->RF1R |= CAN_RF1R_RFOM1;
		}
		else
		{
			Local_ErrorState=CAN_RX_EMPTY;
		}
	}
	else
	{
		Local_ErrorState=CAN_PTR_ERROR;
	}
	return Local_ErrorState;
}


CAN_Status_t CAN_TxMessagePolling(CAN_Config_t* Copy_CANConfig, uint32_t TxMailbox)
{
    CAN_Status_t Local_ErrorState = CAN_OK;

    if (Copy_CANConfig != NULL)
    {
        uint32_t Time = TIME_OUT;

        /* Wait for the selected mailbox to complete transmission */
        while (!(CAN[Copy_CANConfig->CANNumber]->TSR & (RQCP_MASK << (TxMailbox * 8))) && Time--);

        if (Time == 0)
        {
            Local_ErrorState = CAN_TIMEOUT;
        }
        else
        {
            /* Clear the transmission complete flag */
            CAN[Copy_CANConfig->CANNumber]->TSR |= (RQCP_MASK  << (TxMailbox * 8));
        }
    }
    else
    {
        Local_ErrorState = CAN_PTR_ERROR;
    }

    return Local_ErrorState;
}

CAN_Status_t CAN_RxMessagePolling(CAN_Config_t* Copy_CANConfig, uint32_t RxFIFO)
{
	CAN_Status_t Local_ErrorState=CAN_OK;
	if(Copy_CANConfig != NULL)
	{
		uint32_t Time = TIME_OUT;
		if (RxFIFO == FIFO0)
		{
	        /* Wait for a message to be available in the FIFO */
	        while (!(CAN[Copy_CANConfig->CANNumber]->RF0R & CAN_RF0R_FMP0) && Time--);
		}
		else
		{
	        /* Wait for a message to be available in the FIFO */
	        while (!(CAN[Copy_CANConfig->CANNumber]->RF1R & CAN_RF1R_FMP1) && Time--);
		}

		if(Time == 0)
		{
			Local_ErrorState=CAN_TIMEOUT;
		}
	}
	else
	{
		Local_ErrorState=CAN_PTR_ERROR;
	}
	return Local_ErrorState;
}

CAN_FIFONumPending_t CAN_RxMessagePending(CAN_Config_t* Copy_CANConfig, uint32_t RxFIFO)
{
	CAN_FIFONumPending_t PendingMessages = CAN_FIFO_EMPTY;
    if (Copy_CANConfig != NULL)
    {
        /* Check the specified FIFO and get the number of pending messages */
        if (RxFIFO == FIFO0)
        {
            PendingMessages = (CAN[Copy_CANConfig->CANNumber]->RF0R & CAN_RF0R_FMP0);
        }
        else if (RxFIFO == FIFO1)
        {
            PendingMessages = (CAN[Copy_CANConfig->CANNumber]->RF1R & CAN_RF1R_FMP1);
        }
    }
    return PendingMessages;
}

/*========================================================================================================*/
