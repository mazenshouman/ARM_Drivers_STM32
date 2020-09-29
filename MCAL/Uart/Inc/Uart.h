/*
 *  File 	   : Uart.h
 *  Created on : Sep 26, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef UART_INC_UART_H_
#define UART_INC_UART_H_
/************************************************************************
 *                              Includes                                *
 ************************************************************************/
/*I had to do this because main doesn't include config file so to close some functions
 * I have to include this file here*/
#include "Uart_Cfg.h"
/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/

/****************************
 *       Peripheral ID      *
 ***************************/

/*Stm32f103 has only 2 Uarts
 * this id represent the index of the peripheral in the configuration structure*/
typedef uint8 Uart_Id_t;
#define UART_Id0                                 (Uart_Id_t)0
#define UART_Id1                                 (Uart_Id_t)1
#define UART_Id2                                 (Uart_Id_t)2
#define UART_Id3                                 (Uart_Id_t)3

/*uart can carry data up to 9 bits in each frame*/
typedef uint16 Uart_Data_t;

typedef uint8 Uart_MaxRxBufferSize_t;

typedef uint8 Uart_TxData_t;
typedef uint16 Uart_TxCounter_t;

typedef uint8 Uart_RxData_t;

/*interrupt macors*/
/*the first 5 LSB bits defines the position of the interrupt enable bit in the register, the next 3 bits defines the offset
 * the register from the base address and the rest of bit defines the offset of the flag in SR register*/
/*developed with the help of cmsis driver*/

/*encoding*/
/*    |N/A||F_Pos||Reg||E_Pos|*/
/*FFFF XXX  XXXXX  XXX  XXXXX*/

typedef uint16 Uart_InterruptSource_t;
#define UART_INT_PE                              ((Uart_InterruptSource_t)0x0068)
#define UART_INT_TXE                             ((Uart_InterruptSource_t)0x0767)
#define UART_INT_TC                              ((Uart_InterruptSource_t)0x0666)
#define UART_INT_RXNE                            ((Uart_InterruptSource_t)0x0565)
#define UART_INT_IDLE                            ((Uart_InterruptSource_t)0x0464)

typedef uint8 Uart_IntState_t;
#define UART_INT_DISABLED                        (Uart_IntState_t)0
#define UART_INT_ENABLED                         (Uart_IntState_t)1


typedef void (*Uart_PtrToFunction_t)(void);

/************************************************************************
 *                           Error macros                               *
 ***********************************************************************/
typedef uint8 Uart_ErrorStatus_t;
#define UART_E_OK                                (Uart_ErrorStatus_t)0
#define UART_E_NOT_OK                            (Uart_ErrorStatus_t)1

#if UART_INT_BUFFERING_STATUS==UART_ENABLE_BUFFERING
#define UART_ERR_TX_BUSY                         (Uart_ErrorStatus_t)2
#define UART_ERR_RX_NO_NEW_DATA                  (Uart_ErrorStatus_t)3
#endif
/************************************************************************/

/************************************************************************/

/************************************************************************
 *                    UART functions' prototypes                        *
 ***********************************************************************/
/**************************************************************************************************************************************
 *  Function : Uart_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to configure Peripheral define in                                   *
 *             Uart_LCFG                                                                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_Init(void);

/**************************************************************************************************************************************
 *  Function : Uart_SendDataSync                                                                                                      *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_Data_t                                                                                            *
 *                      Desc / takes data wanted to be sent                                                                           *
 *                                                                                                                                    *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function send data through Uart and it's synchronous function                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_SendDataSync(Uart_Id_t Id , Uart_Data_t Data);

/**************************************************************************************************************************************
 *  Function : Uart_SendStringSync                                                                                                    *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / String                                                                                                 *
 *                      Type / Sint8*                                                                                                 *
 *                      Desc / takes data wanted to be sent                                                                           *
 *                                                                                                                                    *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function sends String and it's synchronous function                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_SendStringSync(Uart_Id_t Id , sint8* String);

/**************************************************************************************************************************************
 *  Function : Uart_ReceiveDataSync                                                                                                   *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_Data_t*                                                                                           *
 *                      Desc / takes pointer to variable which the data will be returned on it                                        *
 *                                                                                                                                    *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Receive data through Uart and it's synchronous function                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_ReceiveDataSync(Uart_Id_t Id , Uart_Data_t* Data);

/**************************************************************************************************************************************
 *  Function : Uart_ReceiveStringSync                                                                                                 *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / String                                                                                                 *
 *                      Type / Uart_Data_t*                                                                                           *
 *                      Desc / takes data wanted to be sent                                                                           *
 *                                                                                                                                    *
 *                      Name / MaxSize                                                                                                *
 *                      Type / Uart_MaxRxBufferSize_t                                                                                 *
 *                      Desc / max size of the receive buffer                                                                         *
 *                                                                                                                                    *
 *                      Name / EndingChar                                                                                             *
 *                      Type / sint8                                                                                                  *
 *                      Desc / Expected Ending Character from Sender                                                                  *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Receive String and it's synchronous function                                                             *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_ReceiveStringSync(Uart_Id_t Id , sint8* String , Uart_MaxRxBufferSize_t MaxSize , sint8 EndingChar);

/**************************************************************************************************************************************
 *  Function : Uart_IntControl                                                                                                        *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / IntSource                                                                                              *
 *                      Type / Uart_InterruptSource_t                                                                                 *
 *                      Desc / Predefine macro for interrupt source                                                                   *
 *                                                                                                                                    *
 *                      Name / State                                                                                                  *
 *                      Type / Uart_IntState_t                                                                                        *
 *                      Desc / take predefine macro defines the wanted state for the specified interrupt                              *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function send data through Uart and it's Asynchronous function                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_IntControl(Uart_Id_t Id , Uart_InterruptSource_t IntSource , Uart_IntState_t State);


#if UART_INT_BUFFERING_STATUS==UART_DIABLE_BUFFERING

/**************************************************************************************************************************************
 *  Function : Uart_SendDataAsync                                                                                                     *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_TxData_t*                                                                                         *
 *                      Desc / takes data wanted to be sent                                                                           *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function send data through Uart and it's Asynchronous function                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_SendDataAsync(Uart_Id_t Id , Uart_TxData_t* Data );

/**************************************************************************************************************************************
 *  Function : Uart_ReceiveDataASync                                                                                                  *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_RxData_t*                                                                                         *
 *                      Desc / takes pointer to variable which the data will be returned in                                           *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the last received data from the interrupt                                                         *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_ReceiveDataASync(Uart_Id_t Id , Uart_RxData_t* Data);

#elif UART_INT_BUFFERING_STATUS==UART_ENABLE_BUFFERING

/**************************************************************************************************************************************
 *  Function : Uart_SendDataAsync                                                                                                     *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_TxData_t*                                                                                            *
 *                      Desc / takes data wanted to be sent                                                                           *
 *                                                                                                                                    *
 *                      Name / DataSize                                                                                               *
 *                      Type / Uart_TxCounter_t                                                                                                 *
 *                      Desc / size of the data wanted to be send                                                                     *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function send data through Uart and it's Asynchronous function                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_SendDataAsync(Uart_Id_t Id , Uart_TxData_t* Data , Uart_TxCounter_t DataSize);


/**************************************************************************************************************************************
 *  Function : Uart_ReceiveDataASync                                                                                                  *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_RxData_t*                                                                                         *
 *                      Desc / takes pointer to variable which the data will be returned in                                           *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the top of the queue which have been received from interrupt                                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_ReceiveDataASync(Uart_Id_t Id , Uart_RxData_t* Data);


#endif


#endif /* UART_INC_UART_H_ */
