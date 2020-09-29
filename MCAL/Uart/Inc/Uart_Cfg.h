/*
 *  File 	   : Uart_Cfg.h
 *  Created on : Sep 26, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


#ifndef UART_INC_UART_CFG_H_
#define UART_INC_UART_CFG_H_

/************************************************************************
 *                      Configuration macros                            *
 ************************************************************************/
/*
 *
 * configuration parameter used to decide number of Uart Peripherals in this Device
 *
 * */
typedef uint8 Uart_NumberOfAvailablePeripherals_t;
#define UART_NUMBER_OF_AVAILABLE_PERIPHERAL               (Uart_NumberOfAvailablePeripherals_t)2

/*
 *
 * number of configured peripherals which is the size of the configuration array of structures
 *
 * */


typedef  uint8 Uart_NumberOfConfiguredPeripherals_t;
#define UART_NUMBER_OF_CONFIGURED_PERIPHERALS            (Uart_NumberOfConfiguredPeripherals_t)1


/*
 * configuration values for clk depending on peripheral
 * must be synchronized with values in RCC
 * */

#define UART_PCLK1_FREQ                                  8000000UL
#define UART_PCLK2_FREQ                                  8000000UL


/*
 * Number of Configured Interrupt which determines the size of the Pointer to functions Array
 * */

#define UART_NUMBER_OF_INTERRUPT_SOURCES                 4


/*this configuration  parameter enable and disable Async functions which they use extra buffers to send and receive*/

typedef uint8 Uart_TxRxIntBuffering_t;
#define UART_ENABLE_BUFFERING                            1
#define UART_DIABLE_BUFFERING                            0

#define UART_INT_BUFFERING_STATUS                       UART_ENABLE_BUFFERING


#if UART_INT_BUFFERING_STATUS==UART_ENABLE_BUFFERING

/*configuration parameter for the size of the RX buffer
 * which is used as temp buffer for received data until the user attempt to take from it
 * it's circular queue if user didn't take the data after the buffer is full then the first element will be overwritten*/
/*typedef for rx details */
typedef uint8 Uart_RxIndex_t;
#define UART_RX_BUFFER_SIZE                              10

#define UART_RX_DEFAULT_VALUE                            255

#endif

#endif /* UART_INC_UART_CFG_H_ */
