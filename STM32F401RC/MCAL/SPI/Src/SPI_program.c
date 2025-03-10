/*
 *  SPI_program.c
 *
 *  Created on: Dec 10, 2024
 *  Author: Ahmed Ragab
 */

/*************************  Includes *************************************/
#include "stm32f401xx.h"
#include "ErrorState.h"
#include "SPI_interface.h"
#include "SPI_private.h"

/************************* Global Variable *******************************/
static SPI_RegDef_t* SPI[SPI_NUM_MAX]={SPI1,SPI2,SPI3,SPI4};

/************************  Implementation Function  **********************/

uint8_t SPI_u8Init(SPI_Config_t *Copy_SPIConfig)
{
	uint8_t Local_u8ErrorState = OK;
	if(Copy_SPIConfig!=NULL)
	{
		/* Disable SPI before configuration */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(ENABLE_MASK << ENABLE_PIN_ACCESS);
		/* Configure Bidirectional Data Mode (half duplex) */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(BIDIMODE_MASK << BIDIMODE_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->BidirectionalMode << BIDIMODE_PIN_ACCESS);
		/* Configure Output Enable in Bidirectional Mode in (half duplex) */
		if(Copy_SPIConfig->BidirectionalMode==SPI_BidirectionalMode_1Line)
		{
			SPI[Copy_SPIConfig->Number]->CR1 &= ~(BIDIOE_MASK << BIDIOE_PIN_ACCESS);
			SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->BidirectionalOutput << BIDIOE_PIN_ACCESS);
		}
		/* Configure Receive-Only Mode (Simplex duplex) */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(RXONLY_MASK << RXONLY_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->ReceiveOnlyMode << RXONLY_PIN_ACCESS);
		/* Configure CRC Enable */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(CRCEN_MASK << CRCEN_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->CRCEN << CRCEN_PIN_ACCESS);
		/* Configure Data Frame Format */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(DFF_MASK << DFF_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->DataFrameFormat << DFF_PIN_ACCESS);
		/* Configure Software Slave Management */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(SSM_MASK << SSM_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->SoftwareSlaveManagement << SSM_PIN_ACCESS);
		/* Configure Internal Slave Select */
		if(Copy_SPIConfig->SoftwareSlaveManagement==SPI_SoftwareSlave_Enabled)
		{
			SPI[Copy_SPIConfig->Number]->CR1 &= ~(SSI_MASK << SSI_PIN_ACCESS);
			SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->InternalSlaveSelect << SSI_PIN_ACCESS);
		}
		/* Configure Frame Format */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(LSBFIRST_MASK << LSBFIRST_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->FrameFormat << LSBFIRST_PIN_ACCESS);
		/* Configure Baud Rate Control */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(BR_MASK << BR_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->BaudRateControl << BR_PIN_ACCESS);
		/* Configure Master/Slave Mode */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(MSTR_MASK << MSTR_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->Mode << MSTR_PIN_ACCESS);
		/* Configure Clock Polarity */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(CPOL_MASK << CPOL_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->ClockPolarity << CPOL_PIN_ACCESS);
		/* Configure Clock Phase */
		SPI[Copy_SPIConfig->Number]->CR1 &= ~(CPHA_MASK << CPHA_PIN_ACCESS);
		SPI[Copy_SPIConfig->Number]->CR1 |= (Copy_SPIConfig->ClockPhase << CPHA_PIN_ACCESS);
		/* Enable SPI */
		SPI[Copy_SPIConfig->Number]->CR1 |= (ENABLE_MASK << ENABLE_PIN_ACCESS);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

uint8_t SPI_u8SendReceiveData(SPI_Number_t SPINumber,uint16_t *SendData,uint16_t *ReceivedData,uint32_t DataLength)
{
	uint8_t Local_u8ErrorState = OK;
		if(SendData!=NULL  && ReceivedData!=NULL)
		{
			uint32_t Time;
			uint32_t Count;
			for(Count=CLEAR;Count<DataLength;Count++)
			{
				Time = TIMEOUT;
				/* Wait until TXE is set (Transmit buffer empty) */
				while( !((SPI[SPINumber]->SR >> TXE_PIN_ACCESS) & ONE) && --Time);
				if(Time == TIME_FINISHED)
				{
					Local_u8ErrorState=TIME_OUT;
					break;
				}
				SPI[SPINumber]->DR = SendData[Count];
         /***************************************************************************/
				Time = TIMEOUT;
				/* Wait until RXNE is set (Receive buffer not empty) */
				while( !((SPI[SPINumber]->SR >> RXNE_PIN_ACCESS) & ONE) && --Time);
				if(Time == TIME_FINISHED)
				{
					Local_u8ErrorState=TIME_OUT;
					break;
				}
				ReceivedData[Count] = SPI[SPINumber]->DR;
			}
		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR;
		}
		return Local_u8ErrorState;
}

uint8_t SPI_u8SendData(SPI_Number_t SPINumber,uint16_t *Data,uint32_t DataLength)
{
	uint8_t Local_u8ErrorState = OK;
		if(Data!=NULL)
		{
			uint32_t Time;
			uint32_t Count;
			for(Count=CLEAR;Count<DataLength;Count++)
			{
				Time = TIMEOUT;
				/* Wait until TXE is set (Transmit buffer empty) */
				while( !((SPI[SPINumber]->SR >> TXE_PIN_ACCESS) & ONE) && --Time);
				if(Time == TIME_FINISHED)
				{
					Local_u8ErrorState=TIME_OUT;
					break;
				}
				SPI[SPINumber]->DR = Data[Count];
			}
		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR;
		}
		return Local_u8ErrorState;
}

uint8_t SPI_u8ReceiveData(SPI_Number_t SPINumber,uint16_t *Data,uint32_t DataLength)
{
	uint8_t Local_u8ErrorState = OK;
		if(Data!=NULL)
		{
			uint32_t Time;
			uint32_t Count;
			for(Count=CLEAR;Count<DataLength;Count++)
			{
				Time = TIMEOUT;
				/* Wait until RXNE is set (Receive buffer not empty) */
				while( !((SPI[SPINumber]->SR >> RXNE_PIN_ACCESS) & ONE) && --Time);
				if(Time == TIME_FINISHED)
				{
					Local_u8ErrorState=TIME_OUT;
					break;
				}
				Data[Count] = SPI[SPINumber]->DR;
			}
		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR;
		}
		return Local_u8ErrorState;
}

void SPI_u8SendData_DMA(SPI_Number_t SPINumber)
{
	SPI[SPINumber]->CR2 |= (TXDMAEN_MASK << TXDMAEN_PIN_ACCESS);
}

void SPI_u8ReceiveData_DMA(SPI_Number_t SPINumber)
{
	SPI[SPINumber]->CR2 |= (RXDMAEN_MASK << RXDMAEN_PIN_ACCESS);
}













