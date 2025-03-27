/*
 *  CAN_private.h
 *
 *  Created on: Feb 28, 2025
 *  Author: Ahmed Ragab
 */

#ifndef CAN_PRIVATE_H_
#define CAN_PRIVATE_H_

#define CAN1_BASE               0x40006400UL
#define CAN2_BASE               0x40006800UL

/* CAN Transmit Mailbox Structure */
typedef struct {
    volatile uint32_t TIR;   /* Transmit Identifier Register */
    volatile uint32_t TDTR;  /* Transmit Data Length Code Register */
    volatile uint32_t TDLR;  /* Transmit Data Low Register */
    volatile uint32_t TDHR;  /* Transmit Data High Register */
} CAN_TxMailBox_t;

/* CAN Receive FIFO Mailbox Structure */
typedef struct {
    volatile uint32_t RIR;   /* Receive Identifier Register */
    volatile uint32_t RDTR;  /* Receive Data Length Code Register */
    volatile uint32_t RDLR;  /* Receive Data Low Register */
    volatile uint32_t RDHR;  /* Receive Data High Register */
} CAN_FIFOMailBox_t;

/* CAN Filter Register Structure */
typedef struct {
    volatile uint32_t FR1;   /* Filter Register 1 */
    volatile uint32_t FR2;   /* Filter Register 2 */
} CAN_FilterRegister_t;

/* CAN Register Definition Structure */
typedef struct {
    volatile uint32_t MCR;      /* CAN Master Control Register */
    volatile uint32_t MSR;      /* CAN Master Status Register */
    volatile uint32_t TSR;      /* CAN Transmit Status Register */
    volatile uint32_t RF0R;     /* CAN Receive FIFO 0 Register */
    volatile uint32_t RF1R;     /* CAN Receive FIFO 1 Register */
    volatile uint32_t IER;      /* CAN Interrupt Enable Register */
    volatile uint32_t ESR;      /* CAN Error Status Register */
    volatile uint32_t BTR;      /* CAN Bit Timing Register */
    uint32_t RESERVED0[84];     /* Reserved space for proper alignment */
    volatile CAN_TxMailBox_t sTxMailBox[3]; /* Transmit Mailboxes */
    volatile CAN_FIFOMailBox_t sFIFOMailBox[2][3]; /* Receive FIFO Mailboxes, Each FIFO has 3 messages */
    uint32_t RESERVED1[12];     /* Reserved space */
    volatile uint32_t FMR;      /* CAN Filter Master Register */
    volatile uint32_t FM1R;     /* CAN Filter Mode Register */
    volatile uint32_t FS1R;     /* CAN Filter Scale Register */
    volatile uint32_t FFA1R;    /* CAN Filter FIFO Assignment Register */
    volatile uint32_t FA1R;     /* CAN Filter Activation Register */
    uint32_t RESERVED2[1];      /* Reserved space */
    volatile CAN_FilterRegister_t FilterRegister[14]; /* 14 Filter Banks */
} CAN_RegDef_t;

#define bxCAN1                   ((CAN_RegDef_t *) CAN1_BASE) /* Define a pointer to CAN1 */
#define bxCAN2                   ((CAN_RegDef_t *) CAN2_BASE) /* Define a pointer to CAN2 */

/*==================================================================================================*/

#define NULL ((void *)0)
#define CAN_PERIPHERAL_NUM  2u
#define TIME_OUT            0xffffff
/**
 * @brief Enumeration for CAN Master Control Register (MCR) bits.
 * Each bit controls a specific behavior of the CAN peripheral.
 */
typedef enum {
	CAN_MCR_INRQ = (1U << 0), /* Initialization Mode Request */
	CAN_MCR_SLEEP= (1U << 1), /* Sleep Mode Request */
	CAN_MCR_TXFP = 2, /* Transmit FIFO Priority */
	CAN_MCR_RFLM = 3, /* Receive FIFO Locked Mode */
	CAN_MCR_NART = 4, /* No Automatic Retransmission */
	CAN_MCR_AWUM = 5, /* Automatic Wakeup Mode */
	CAN_MCR_ABOM = 6, /* Automatic Bus-Off Management */
	CAN_MCR_TTCM = 7, /* Time Triggered Communication Mode */
	CAN_MCR_RESET= 8, /* Software Reset */
	CAN_MCR_DBF  = 15 /* Debug Freeze */
} CAN_MCR_Bits_t;

/**
 * @brief Enumeration for CAN Master Status Register (MSR) bits.
 * Each bit provides status information about the CAN peripheral.
 */
typedef enum {
    CAN_MSR_INAK = (1U << 0),  /* Initialization Acknowledge */
    CAN_MSR_SLAK = (1U << 1),  /* Sleep Acknowledge */
    CAN_MSR_ERRI = (1U << 2),  /* Error Status */
    CAN_MSR_WKUI = (1U << 3),  /* Wakeup Status */
    CAN_MSR_SLAKI= (1U << 4),  /* Sleep Status */
    CAN_MSR_TXM  = (1U << 8),  /* Transmit Mode */
    CAN_MSR_RXM  = (1U << 9),  /* Receive Mode */
    CAN_MSR_SAMP = (1U << 10), /* Sleep Mode */
    CAN_MSR_RXERR= (1U << 16), /* RX Error Counter */
    CAN_MSR_TXERR= (1U << 24), /* TX Error Counter */
} CAN_MSR_Bits;

#define MODE_PIN_ACCESS 30U
#define SJW_PIN_ACCESS  24U
#define TS2_PIN_ACCESS  20U
#define TS1_PIN_ACCESS  16U
#define BRP_PIN_ACCESS   0
#define FINIT_MASK       1U
#define CAN_FMR_FINIT    0
#define FILTER_MASK      1U

#define CAN_TSR_TME0   (1U << 26)  /* Bit 26: Mailbox 0 empty */
#define CAN_TSR_TME1   (1U << 27)  /* Bit 27: Mailbox 1 empty */
#define CAN_TSR_TME2   (1U << 28)  /* Bit 28: Mailbox 2 empty */
#define CAN_TSR_RQCP0  (1U << 0)   /* Transmission Request Completed for Mailbox 0 */
#define CAN_TSR_RQCP1  (1U << 8)   /* Transmission Request Completed for Mailbox 1 */
#define CAN_TSR_RQCP2  (1U << 16)  /* Transmission Request Completed for Mailbox 2 */
#define CAN_RF0R_FMP0  (0x03U)     /* Bits [1:0] - FIFO 0 Message Pending */
#define CAN_RF1R_FMP1  (0x03U)     /* Bits [1:0] - FIFO 1 Message Pending */

#define RQCP_MASK      1u

#define Mailbox0         0
#define Mailbox1         1u
#define Mailbox2         2u
#define MailboxesBusy    3u

#define CAN_TI0R_TXRQ     (1U << 0)
#define RTR_PIN_ACCESS    1u
#define IDE_PIN_ACCESS    2u
#define ExtId_PIN_ACCESS  3u
#define StdId_PIN_ACCESS  21u

#define CAN_RF0R_RFOM0  (1U << 5)  /* Release FIFO 0 */
#define CAN_RF1R_RFOM1  (1U << 5)  /* Release FIFO 1 */
#define CAN_RI0R_IDE    (1U << 2)  /* IDE bit position */
#define CAN_RI0R_RTR    (1U << 1)  /* RTR bit position */

#define FIFO0             0
#define FIFO1             1u
#define FIFO_EMPTY        2u


#endif /* CAN_PRIVATE_H_ */
