/*
 *  File 	   : Uart_MemMap.h
 *  Created on : Sep 26, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef UART_INC_UART_MEMMAP_H_
#define UART_INC_UART_MEMMAP_H_

/******************************
 *        H/W registers       *
 *****************************/
typedef uint32 Uart_RegSize_t;

typedef struct{
	Uart_RegSize_t SR;
	Uart_RegSize_t DR;
	Uart_RegSize_t BRR;
	Uart_RegSize_t CR1;
	Uart_RegSize_t CR2;
	Uart_RegSize_t CR3;
	Uart_RegSize_t GTPR;
}Uart_RegType;


/**************************************************
 *        pointer to the register structure       *
 **************************************************/

#define UART1_BASE_ADDRESS                             ((volatile Uart_RegType*)0x40013800)

static volatile Uart_RegType* Uart_BaseAddresses[UART_NUMBER_OF_AVAILABLE_PERIPHERAL]={(volatile Uart_RegType*)0x40013800 , (volatile Uart_RegType*)0x40004400};
/******************************************************************************************************/

/************************
 *       CR1 bits       *
 ***********************/
#define UART_CR1_UE                                     13
#define UART_CR1_M                                      12
#define UART_CR1_WAKE                                   11
#define UART_CR1_PCE                                    10
#define UART_CR1_PS                                     9
#define UART_CR1_PEIE                                   8
#define UART_CR1_TXEIE                                  7
#define UART_CR1_TCIE                                   6
#define UART_CR1_RXNEIE                                 5
#define UART_CR1_IDLEIE                                 4
#define UART_CR1_TE                                     3
#define UART_CR1_RE                                     2
#define UART_CR1_RWU                                    1
#define UART_CR1_SBK                                    0

/************************
 *       CR2 bits       *
 ***********************/
#define UART_CR2_LINEN                                  14
#define UART_CR2_STOP                                   12
#define UART_CR2_CLKEN                                  11
#define UART_CR2_CPOL                                   10
#define UART_CR2_CPHA                                   9
#define UART_CR2_LBCL                                   8
#define UART_CR2_LBDIE                                  6
#define UART_CR2_LBDL                                   5
#define UART_CR2_ADD                                    0

/************************
 *       CR3 bits       *
 ***********************/
#define UART_CR3_CTSIE                                  10
#define UART_CR3_CTSE                                   9
#define UART_CR3_RTSE                                   8
#define UART_CR3_DMAT                                   7
#define UART_CR3_DMAR                                   6
#define UART_CR3_SCEN                                   5
#define UART_CR3_NACK                                   4
#define UART_CR3_HDSEL                                  3
#define UART_CR3_IRLP                                   2
#define UART_CR3_IREN                                   1
#define UART_CR3_EIE                                    0

/************************
 *       SR bits        *
 ***********************/
#define UART_SR_CTS                                     9
#define UART_SR_LBD                                     8
#define UART_SR_TXE                                     7
#define UART_SR_TC                                      6
#define UART_SR_RXNE                                    5
#define UART_SR_IDLE                                    4
#define UART_SR_ORE                                     3
#define UART_SR_NE                                      2
#define UART_SR_FE                                      1
#define UART_SR_PE                                      0

/******************************************************************************************************/




#endif /* UART_INC_UART_MEMMAP_H_ */
