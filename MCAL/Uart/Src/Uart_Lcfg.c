/*
 *  File 	   : Uart_Lcfg.c
 *  Created on : Sep 26, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_Types.h"
#include "Uart_Cfg.h"
#include "Uart.h"
#include "Uart_Lcfg.h"



/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/

Uart_ConfigType  gastr_UartPeripheralConfig[UART_NUMBER_OF_CONFIGURED_PERIPHERALS]=
/*            Peipheral ID                             Mode                            TxStatus                        RxStatus                             DataSize                        Parity                      StopBits                           DmaTxStatus                          DmaRxStatus                              TXEIE                              TXCIE                              RXNEIE                               IDLEIE                             PEIE                          baudrate*/
{
 {              UART1         ,                     UART_FULL_DUPLEX       ,       UART_TX_ENABLED          ,      UART_RX_ENABLED       ,          UART_DATA_SIZE_8_BITS      ,       UART_NO_PARITY       ,       UART_STOP_1_BIT      ,       UART_DMA_TRANSMITTER_DISABLED    ,    UART_DMA_RECEIVER_DISABLED   ,       UART_TXE_INTERRUPT_DISABLED   ,     UART_TC_INTERRUPT_DISABLED    ,    UART_RXNE_INTERRUPT_DISABLED   ,    UART_IDLE_INTERRUPT_DISABLED   ,    UART_PE_INTERRUPT_DISABLED   ,            9600     }
};
