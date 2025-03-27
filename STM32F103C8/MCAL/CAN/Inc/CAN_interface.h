/*
 *  CAN_interface.h
 *
 *  Created on: Feb 28, 2025
 *  Author: Ahmed Ragab
 */

#ifndef CAN_INTERFACE_H_
#define CAN_INTERFACE_H_

#include "CAN_private.h"

/*the operational modes of the CAN controller.*/
typedef enum {
  CAN_MODE_NORMAL,          /* Normal communication mode*/
  CAN_MODE_LOOPBACK,        /* Internal loopback for self-testing*/
  CAN_MODE_SILENT,          /* Listen-only mode (monitor bus)*/
  CAN_MODE_SILENT_LOOPBACK  /* Silent + loopback combined*/
} CAN_Mode_t;

/* Synchronization Jump Width (SJW)
 * CAN Bit Time Calculation
 * link: http://www.bittiming.can-wiki.info
 **/
/* 1-Synchronization Jump Width (SJW)*/
typedef enum {
  CAN_SJW_1TQ,              /*1 Time Quantum*/
  CAN_SJW_2TQ,
  CAN_SJW_3TQ,
  CAN_SJW_4TQ
} CAN_SJW_t;

/* 2-Time Segment 1 (BS1: Propagation + Phase Buffer 1)*/
typedef enum {
  CAN_BS1_1TQ,
  CAN_BS1_2TQ,
  CAN_BS1_3TQ,
  CAN_BS1_4TQ,
  CAN_BS1_5TQ,
  CAN_BS1_6TQ,
  CAN_BS1_7TQ,
  CAN_BS1_8TQ,
  CAN_BS1_9TQ,
  CAN_BS1_10TQ,
  CAN_BS1_11TQ,
  CAN_BS1_12TQ,
  CAN_BS1_13TQ,
  CAN_BS1_14TQ,
  CAN_BS1_15TQ,
  CAN_BS1_16TQ
} CAN_BS1_t;

/* 3-Time Segment 2 (BS2: Phase Buffer 2)*/
typedef enum {
  CAN_BS2_1TQ,
  CAN_BS2_2TQ,
  CAN_BS2_3TQ,
  CAN_BS2_4TQ,
  CAN_BS2_5TQ,
  CAN_BS2_6TQ,
  CAN_BS2_7TQ,
  CAN_BS2_8TQ
} CAN_BS2_t;

/*Configure CAN message filters.*/
/* Filter Modes*/
typedef enum {
  CAN_FILTER_MODE_ID_MASK,  /* Mask mode (filter ranges) */
  CAN_FILTER_MODE_ID_LIST   /* List mode (specific IDs) */
} CAN_FilterMode_t;

/* Filter Scales*/
typedef enum {
  CAN_FILTER_SCALE_16BIT,   /* Two 16-bit filters */
  CAN_FILTER_SCALE_32BIT    /* One 32-bit filter */
} CAN_FilterScale_t;

/* FIFO Assignment*/
typedef enum {
  CAN_FILTER_FIFO0,         /* Assign matches to FIFO 0 */
  CAN_FILTER_FIFO1          /* Assign matches to FIFO 1 */
} CAN_FilterFIFO_t;

/* Filter Activation */
typedef enum {
  CAN_FILTER_DISABLE,       /* Disable filter */
  CAN_FILTER_ENABLE         /* Enable filter */
} CAN_FilterActivation_t;

typedef enum {
  DISABLE,
  ENABLE
} FunctionalState_t;

typedef enum{
	CAN1,
	CAN2
}CAN_RegNum_t;

/*Configures CAN message acceptance filters.*/
typedef struct {
  uint32_t FilterBank;           /* Filter bank number (0-13)*/
  CAN_FilterMode_t FilterMode;   /* ID mask or list mode*/
  CAN_FilterScale_t FilterScale; /* 16-bit or 32-bit filter*/
  uint16_t FilterIdHigh;         /* High bits of ID (16/32-bit)*/
  uint16_t FilterIdLow;          /* Low bits of ID (16/32-bit)*/
  uint16_t FilterMaskIdHigh;     /* High bits of mask (mask mode)*/
  uint16_t FilterMaskIdLow;      /* Low bits of mask (mask mode)*/
  CAN_FilterFIFO_t FilterFIFO;   /* FIFO assignment (FIFO0/FIFO1)*/
  CAN_FilterActivation_t Activation; /* Enable/disable filter*/
} CAN_Filter_t;

/*settings for initializing the CAN peripheral.*/
typedef struct {
  CAN_RegNum_t CANNumber;       /* CAN peripheral (CAN1/CAN2)*/
  CAN_Mode_t Mode;              /* Operational mode*/
  uint32_t Prescaler;           /* Baud rate prescaler*/
  CAN_SJW_t SyncJumpWidth;      /* SJW (1-4 TQs)*/
  CAN_BS1_t TimeSeg1;           /* BS1 (1-16 TQs)*/
  CAN_BS2_t TimeSeg2;           /* BS2 (1-8 TQs)*/
  FunctionalState_t AutoBusOff;   /* Automatic bus-off recovery*/
  FunctionalState_t AutoWakeUp;   /* Automatic wakeup from sleep*/
  FunctionalState_t AutoRetransmission; /* Retransmit on error*/
  FunctionalState_t ReceiveFifoLocked;  /* Lock FIFO on overflow*/
  FunctionalState_t TransmitFifoPriority; /* TX priority by order*/
} CAN_Config_t;

/* Transmit Header*/
typedef struct {
  uint32_t StdId;   /* 11-bit standard ID*/
  uint32_t ExtId;   /* 29-bit extended ID*/
  uint8_t IDE;      /* Identifier extension (STD/EXT)*/
  uint8_t RTR;      /* Remote Transmission Request*/
  uint8_t DLC;      /* Data Length Code (0-8 bytes)*/
} CAN_TxHeader_t;

/* Receive Header*/
typedef struct {
  uint32_t StdId;   /* 11-bit standard ID*/
  uint32_t ExtId;   /* 29-bit extended ID*/
  uint8_t IDE;      /* Identifier extension (STD/EXT)*/
  uint8_t RTR;      /* Remote Transmission Request*/
  uint8_t DLC;      /* Data Length Code*/
  uint32_t Timestamp; /* Frame reception timestamp*/
  uint8_t FilterMatchIndex; /* Filter bank that matched*/
} CAN_RxHeader_t;

/*statuses for CAN functions.*/
typedef enum {
  CAN_OK,          /* Operation successful*/
  CAN_ERROR,       /* General error*/
  CAN_PTR_ERROR,   /* Pointer error*/
  CAN_BUSY,        /* Peripheral busy*/
  CAN_RX_EMPTY,    /* No data available in FIFO0 or FIFO1*/
  CAN_TIMEOUT      /* Operation timed out*/
} CAN_Status_t;

/* enumeration that represents the number of pending messages */
typedef enum
{
  CAN_FIFO_EMPTY,  /* 00 → No message */
  CAN_FIFO_1MSG,   /* 01 → 1 message */
  CAN_FIFO_2MSG,   /* 10 → 2 messages */
  CAN_FIFO_FULL    /* 11 → 3 messages (FIFO full) */
} CAN_FIFONumPending_t;

/*======================================================================================*/

/*
 * @brief Initializes the CAN peripheral with the specified configuration.
 * @param Copy_CANConfig: Pointer to the CAN configuration structure.
 * @return CAN_Status_t: Status of the initialization process.
 */
CAN_Status_t CAN_Init(CAN_Config_t* Copy_CANConfig);

/*
 * @brief Configures the CAN filter settings.
 * @param Copy_CANConfig: Pointer to the CAN configuration structure.
 * @param Copy_FilterConfig: Pointer to the CAN filter configuration structure.
 * @return CAN_Status_t: Status of the filter configuration process.
 */
CAN_Status_t CAN_ConfigFilter(CAN_Config_t *Copy_CANConfig, const CAN_Filter_t *Copy_FilterConfig);

/*
 * @brief Starts the CAN peripheral.
 * @param Copy_CANConfig: Pointer to the CAN configuration structure.
 * @return CAN_Status_t: Status of the start operation.
 */
CAN_Status_t CAN_Start(CAN_Config_t* Copy_CANConfig);

/*
 * @brief Stops the CAN peripheral and puts it into sleep mode.
 * @param Copy_CANConfig: Pointer to the CAN configuration structure.
 * @return CAN_Status_t: Status of the stop operation.
 */
CAN_Status_t CAN_Stop(CAN_Config_t* Copy_CANConfig);

/**
 * @brief Transmits a CAN message using an available mailbox.
 * @param Copy_CANConfig Pointer to CAN configuration structure.
 * @param pTxHeader Pointer to the CAN transmission header structure.
 * @param pData Pointer to the data payload to be transmitted.
 * @param pTxMailbox Pointer to store the index of the used mailbox.
 * @return CAN status indicating success, busy state, or pointer error.
 */
CAN_Status_t CAN_AddTxMessage(CAN_Config_t* Copy_CANConfig, const CAN_TxHeader_t *pTxHeader, const uint8_t *pData, uint8_t *pTxMailbox);

/**
 * @brief Retrieves a received CAN message from the specified FIFO.
 * @param Copy_CANConfig Pointer to CAN configuration structure.
 * @param RxFIFO Specifies which receive FIFO to check (FIFO0 or FIFO1).
 * @param pRxHeader Pointer to structure storing received message metadata.
 * @param pData Pointer to buffer where received data will be stored.
 * @return CAN status indicating success, empty FIFO, or pointer error.
 */
CAN_Status_t CAN_GetRxMessage(CAN_Config_t* Copy_CANConfig, CAN_FilterFIFO_t RxFIFO, CAN_RxHeader_t* pRxHeader, uint8_t* pData);

/**
 * @brief Waits for the transmission of a message to complete (polling-based).
 * @param Copy_CANConfig Pointer to CAN configuration structure.
 * @param TxMailbox Index of the mailbox used for transmission.
 * @return CAN status indicating success, timeout, or pointer error.
 */
CAN_Status_t CAN_TxMessagePolling(CAN_Config_t* Copy_CANConfig, uint32_t TxMailbox);

/**
 * @brief Waits for a received message in the specified FIFO (polling-based).
 * @param Copy_CANConfig Pointer to CAN configuration structure.
 * @param RxFIFO Specifies which receive FIFO to check (FIFO0 or FIFO1).
 * @return CAN status indicating success, timeout, or pointer error.
 */
CAN_Status_t CAN_RxMessagePolling(CAN_Config_t* Copy_CANConfig, uint32_t RxFIFO);

/**
 * @brief Checks the number of pending messages in a specified FIFO.
 * @param Copy_CANConfig Pointer to CAN configuration structure.
 * @param RxFIFO Specifies which receive FIFO to check (FIFO0 or FIFO1).
 * @return The number of pending messages in the FIFO.
 */
CAN_FIFONumPending_t CAN_RxMessagePending(CAN_Config_t* Copy_CANConfig, uint32_t RxFIFO);


#endif /* CAN_INTERFACE_H_ */
