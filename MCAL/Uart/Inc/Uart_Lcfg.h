/*
 * Uart_Lcfg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mazen Sh
 */

#ifndef UART_INC_UART_LCFG_H_
#define UART_INC_UART_LCFG_H_

/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/
/*************************************
 *             UART Id Macro         *
 ************************************/
typedef uint8 Uart_PerId_t;
#define UART1                                                     (Uart_PerId_t)0
#define UART2                                                     (Uart_PerId_t)1

/*if you choose to configure uart as half duplex the tx pin must be configured as input floating as when the
 * uart is receiving the pin acting as IO pin and not overridden by the UART*/
/*
 * and arbitration must be handled as two devices must not send data at the same time
 * */

/*************************************
 *             Mode Macro            *
 ************************************/
typedef uint8 Uart_Mode_t;
#define UART_FULL_DUPLEX                                           (Uart_Mode_t)0
#define UART_HALF_DUPLEX                                           (Uart_Mode_t)1

/*************************************
 *             Tx status             *
 ************************************/
typedef uint8 Uart_TxStatus_t;
#define UART_TX_DISABLED                                           (Uart_TxStatus_t)0
#define UART_TX_ENABLED                                            (Uart_TxStatus_t)1

/*************************************
 *             Rx status             *
 ************************************/
typedef uint8 Uart_RxStatus_t;
#define UART_RX_DISABLED                                           (Uart_RxStatus_t)0
#define UART_RX_ENABLED                                            (Uart_RxStatus_t)1

/*************************************
 *             Data Size             *
 ************************************/
typedef uint8 Uart_DataSize_t;
#define UART_DATA_SIZE_8_BITS                                      (Uart_DataSize_t)0
#define UART_DATA_SIZE_9_BITS                                      (Uart_DataSize_t)1

/*************************************
 *             Parity                *
 ************************************/
typedef uint8 Uart_Parity_t;
#define UART_NO_PARITY                                             (Uart_Parity_t)0
#define UART_EVEN_PARTIY                                           (Uart_Parity_t)2
#define UART_ODD_PARITY                                            (Uart_Parity_t)3

/*************************************
 *             STOP Bits             *
 ************************************/
typedef uint8 Uart_StopBits_t;
#define UART_STOP_1_BIT                                            (Uart_StopBits_t)0
#define UART_STOP_2_BITS                                           (Uart_StopBits_t)2

/*************************************
 *         DMA Transmitter           *
 ************************************/
typedef uint8 Uart_DmaTransmitterStatus_t;
#define UART_DMA_TRANSMITTER_DISABLED                              (Uart_DmaTransmitterStatus_t)0
#define UART_DMA_TRANSMITTER_ENALBED                               (Uart_DmaTransmitterStatus_t)1

/*************************************
 *         DMA Receiver              *
 ************************************/
typedef uint8 Uart_DmaReceiverStatus_t;
#define UART_DMA_RECEIVER_DISABLED                                 (Uart_DmaReceiverStatus_t)0
#define UART_DMA_RECEIVER_ENALBED                                  (Uart_DmaReceiverStatus_t)1

/*************************************
 *         TXE Interrupt             *
 ************************************/
typedef uint8 Uart_TxeInterruptStatus_t;
#define UART_TXE_INTERRUPT_DISABLED                                (Uart_TxeInterruptStatus_t)0
#define UART_TXE_INTERRUPT_ENABLED                                 (Uart_TxeInterruptStatus_t)1

/*************************************
 *         TXC Interrupt             *
 ************************************/
typedef uint8 Uart_TcInterruptStatus_t;
#define UART_TC_INTERRUPT_DISABLED                                 (Uart_TcInterruptStatus_t)0
#define UART_TC_INTERRUPT_ENABLED                                  (Uart_TcInterruptStatus_t)1

/*************************************
 *         RXNE Interrupt            *
 ************************************/
typedef uint8 Uart_RxneInterruptStatus_t;
#define UART_RXNE_INTERRUPT_DISABLED                               (Uart_RxneInterruptStatus_t)0
#define UART_RXNE_INTERRUPT_ENABLED                                (Uart_RxneInterruptStatus_t)1

/*************************************
 *         IDLE Interrupt            *
 ************************************/
typedef uint8 Uart_IdleInterruptStatus_t;
#define UART_IDLE_INTERRUPT_DISABLED                               (Uart_IdleInterruptStatus_t)0
#define UART_IDLE_INTERRUPT_ENABLED                                (Uart_IdleInterruptStatus_t)1

/*************************************
 *       Parity Error Interrupt      *
 ************************************/
typedef uint8 Uart_PeInterruptStatus_t;
#define UART_PE_INTERRUPT_DISABLED                                 (Uart_PeInterruptStatus_t)0
#define UART_PE_INTERRUPT_ENABLED                                  (Uart_PeInterruptStatus_t)1

/*************************************
 *              BuadRate             *
 ************************************/
typedef uint32 Uart_BaudRate_t;

/*************************************
 *         Peripheral Clock          *
 ************************************/
typedef uint32 Uart_PerClk_t;

/************************************************************************
 *                      Configuration Structure                         *
 ***********************************************************************/
typedef struct{
	Uart_PerId_t                    PerId:1;
	Uart_Mode_t                     Mode:1;
	Uart_TxStatus_t                 TxStatus:1;
	Uart_RxStatus_t                 RxStatus:1;
	Uart_DataSize_t                 DataSize:1;
	Uart_Parity_t                   Parity:2;
	Uart_StopBits_t                 StopBits:2;
	Uart_DmaTransmitterStatus_t     DmaTransmitterStatus:1;
	Uart_DmaReceiverStatus_t        DmaReceiverStatus:1;
	Uart_TxeInterruptStatus_t       TxeInterruptStatus:1;
	Uart_TcInterruptStatus_t        TcInterruptStatus:1;
	Uart_RxneInterruptStatus_t      RxneInterruptStatus:1;
	Uart_IdleInterruptStatus_t      IdleInterruptStatus:1;
	Uart_PeInterruptStatus_t        PeInterruptStatus:1;
	Uart_BaudRate_t                 BaudRate;
}Uart_ConfigType;


/****************************************************************************/

/************************************************************************
 *              Externed configuration Structure instance               *
 ************************************************************************/

extern Uart_ConfigType  gastr_UartPeripheralConfig[UART_NUMBER_OF_CONFIGURED_PERIPHERALS];



#endif /* UART_INC_UART_LCFG_H_ */
