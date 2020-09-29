/*
 *  File 	   : Uart.c
 *  Created on : Sep 26, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ***********************************************************************/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Uart_Cfg.h"
#include "Uart.h"
#include "Uart_Lcfg.h"

/************************************************************************
 *        Private Includes (macros used inside this file only)          *
 ***********************************************************************/

#include "Uart_MemMap.h"

/************************************************************************
 *                              macros                                  *
 ***********************************************************************/
#define UART_PARITY_RESET_MASK                       0XFFFFF9FF
#define UART_STOPBITS_RESET_MAKS                     0xFFFFCFFF

/*INT macros*/
#define UART_INT_EN_MASK                             0x0000001F
#define UART_INT_REG_SHIFT                           0x5
#define UART_INT_FLAG_SHIFT                          0x8
#define UART_NO_BYTES_PER_REG                        4
#define UART_INT_PTR_BASE_OFFSET                     4
#define UART_INT_PTR_REG_OFFSET                      3


/*baud rate macros*/
/*the actual values are mul=100 and samples=16 but for the top value not exceed the uint32 limit we substitute those values
 * with the current values*/
#define UART_FRACTION_GET_MUL_SUB                    (uint32)25
#define UART_NUMBER_OF_SAMPLES_SUB                   (uint32)4
#define UART_FRACTION_GET_MUL                        (uint32)100
#define UART_BAUDRATE_INT_OFFSET                     4
#define UART_BAUDRATE_FRACTION_MUL                   16
#define UART_BAUDRATE_ROUND_VALUE                    50

/*Txe lock flag */
typedef uint8 Uart_TxeBusyFlag_t;
#define UART_TXE_NOT_BUSY                            (Uart_TxeBusyFlag_t)0
#define UART_TXE_BUSY                                (Uart_TxeBusyFlag_t)1


#if UART_INT_BUFFERING_STATUS==UART_ENABLE_BUFFERING

/*these structs used in Interrupts*/
typedef struct
{
	volatile Uart_TxCounter_t DataSizeCounter;
	Uart_TxData_t*   Data;
	volatile Uart_TxCounter_t CurrentIndex;
	volatile Uart_TxeBusyFlag_t Flag;
}Uart_TxDetails_t;


typedef struct
{
	volatile Uart_RxIndex_t InsertIndex;
	volatile Uart_RxIndex_t CurrentIndex;
	Uart_RxData_t   Data[UART_RX_BUFFER_SIZE];
	volatile Uart_RxIndex_t CurrentSize;
}Uart_RxDetails_t;

#endif
/************************************************************************
 *                        Gloabl Variables                              *
 ***********************************************************************/
/*array of clock depending on peripheral Id*/

static Uart_PerClk_t Uart_PerClkArr[UART_NUMBER_OF_AVAILABLE_PERIPHERAL]={UART_PCLK1_FREQ , UART_PCLK2_FREQ};

/*array of pointer to function*/

Uart_PtrToFunction_t ga_UartPtrToFunctoin[UART_NUMBER_OF_CONFIGURED_PERIPHERALS][UART_NUMBER_OF_INTERRUPT_SOURCES]={NULL};

#if UART_INT_BUFFERING_STATUS==UART_DIABLE_BUFFERING

volatile Uart_TxData_t g_UartTxData=0;

volatile Uart_RxData_t g_UartRxData=0;

#elif UART_INT_BUFFERING_STATUS==UART_ENABLE_BUFFERING


Uart_TxDetails_t Uart_IntTxeDetails[UART_NUMBER_OF_CONFIGURED_PERIPHERALS]={0};

Uart_RxDetails_t Uart_IntRxDetails[UART_NUMBER_OF_CONFIGURED_PERIPHERALS]={0};

#endif
/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/
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

Uart_ErrorStatus_t Uart_Init(void)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	Uart_NumberOfConfiguredPeripherals_t Local_Counter=0;
	volatile Uart_RegType* Local_CurrentPtrToPer=0;
	uint16 Local_BaudRateInteger=0;
	uint8 Local_BaudRateFraction=0;
	uint32 Local_BaudRateValue=0;

	/*loop on configuration structure*/
	for(Local_Counter=0 ; Local_Counter<UART_NUMBER_OF_CONFIGURED_PERIPHERALS ; ++Local_Counter)
	{

		/*get peripheral Base Address*/
		Local_CurrentPtrToPer=Uart_BaseAddresses[gastr_UartPeripheralConfig[Local_Counter].PerId];

		/*check if one of the Tx or Rx is enabled*/
		if(gastr_UartPeripheralConfig[Local_Counter].TxStatus == UART_TX_ENABLED || gastr_UartPeripheralConfig[Local_Counter].RxStatus==UART_RX_ENABLED)
		{
			/*enable uart*/
			SET_BIT(Local_CurrentPtrToPer->CR1 , UART_CR1_UE);
		}
		/*else return error*/
		else
		{
			/*datasheet stated that we have to enable the uart before configuration so this must be
			 * an error for not enabling one of the Rx or Tx (can be modified if the my information was wrong)*/
			CLEAR_BIT(Local_CurrentPtrToPer->CR1 , UART_CR1_UE);

			returnValue=UART_E_NOT_OK;
		}

		if(returnValue==UART_E_OK)
		{

			/*this is not the most effecient code in terms of execution time but the most efficient one in terms of configure-ability and code size
			 * ->for more efficient code the size of configuration structure will increase from 8 bytes to almost 20 bytes by putting the wanted value
			 * in each member to just ORing them together and put the value in the register
			 * ->but for this code to run in AVR it will be so hard to do so with this size of structure for almost all peripheral as
			 * AVR has only 2K Bytes of RAM and it will be disaster if I wanted to run that code in PIC16f877A
			 *->Maybe I will consider doing so in the future
			 * */

			/*all these values must be checked before running the code to make sure it uses the predefined macros for each configuration*/

			/*set mode*/
			/*this bit configure the uart as half duplex if set and if not the uart will operate as full-duplex */
			/*NOTE:if the peripheral was configured as half-duplex then only the tx pin will be active and must be
			 * configured as input floating in port driver as if the peripheral is receiving it will act as IO pin*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR3 , UART_CR3_HDSEL ,gastr_UartPeripheralConfig[Local_Counter].Mode );

			/*set data size*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 ,  UART_CR1_M , gastr_UartPeripheralConfig[Local_Counter].DataSize);

			/*set parity*/
			SET_VALUE_FOR_BITS_IN_REG(Local_CurrentPtrToPer->CR1 , UART_PARITY_RESET_MASK , UART_CR1_PS , gastr_UartPeripheralConfig[Local_Counter].Parity);

			/*set stop bits*/
			SET_VALUE_FOR_BITS_IN_REG(Local_CurrentPtrToPer->CR2 , UART_STOPBITS_RESET_MAKS , UART_CR2_STOP , gastr_UartPeripheralConfig[Local_Counter].StopBits);

			/*Dma Tx enable*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR3 , UART_CR3_DMAT , gastr_UartPeripheralConfig[Local_Counter].DmaTransmitterStatus);

			/*Dma Rx enable*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR3 , UART_CR3_DMAR , gastr_UartPeripheralConfig[Local_Counter].DmaReceiverStatus);

			/*enable/disable interrupts*/
			/*it's preferable to set call back functions for interrupts before intializing the module
			 * specially for the TXE and TXC interrupts as they will fire immediately if the NVIC vector is
			 * enabled*/

			/*TXE*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 , UART_CR1_TXEIE , gastr_UartPeripheralConfig[Local_Counter].TxeInterruptStatus );

			/*TXC*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 , UART_CR1_TCIE , gastr_UartPeripheralConfig[Local_Counter].TcInterruptStatus);

			/*RXNE*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 , UART_CR1_RXNEIE , gastr_UartPeripheralConfig[Local_Counter].RxneInterruptStatus);

			/*IDLE*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 , UART_CR1_IDLEIE , gastr_UartPeripheralConfig[Local_Counter].IdleInterruptStatus);

			/*PE*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 , UART_CR1_PEIE , gastr_UartPeripheralConfig[Local_Counter].PeInterruptStatus);

			/*set baudrate*/
			/*the baud rate must be multiplied by 100 at least to take two digit from fraction and represent
			 * them in the 4 fraction bits after rounding the fraction to the nearest value*/
			/*we can add more precision by taking more bits, hence bigger multiplier but you have to take
			 * in consideration that the value will exceed the uint32 limit
			 * if we have clk over than 172MHZ then we have to change the variable to uint64
			 * */

			/*complete value = (Fclk*25)/(4*wanted baud Rate)    (25/4) substitute for (100/16)*/
			Local_BaudRateValue=(UART_FRACTION_GET_MUL_SUB*Uart_PerClkArr[gastr_UartPeripheralConfig[Local_Counter].PerId])/(UART_NUMBER_OF_SAMPLES_SUB*gastr_UartPeripheralConfig[Local_Counter].BaudRate);

			/*integral part is the first 12 bits */
			Local_BaudRateInteger=(Local_BaudRateValue/UART_FRACTION_GET_MUL);

			/*fraction part = ((complete value -integer part)*16)+0.5*/
			/*the 16 value came from that the value will be represented in 4 bits so we want to know how
			 * many LSB (1/16 parts) the value will take
			 * the .5 part to round the value to the nearest number LSB
			 * */
			Local_BaudRateFraction=Local_BaudRateValue%UART_FRACTION_GET_MUL;

			/*as the value must be divided by 100 then we have to represent the added .5 as 50*/
			Local_BaudRateFraction=((Local_BaudRateFraction*UART_BAUDRATE_FRACTION_MUL)+UART_BAUDRATE_ROUND_VALUE)/UART_FRACTION_GET_MUL;

			/*if the value of fraction exceed 15 then we have to add one to the integer part and get the mod value to the fraciton part*/
			if(Local_BaudRateFraction>=UART_BAUDRATE_FRACTION_MUL)
			{
				Local_BaudRateFraction%=UART_BAUDRATE_FRACTION_MUL;
				Local_BaudRateInteger++;
			}

			Local_BaudRateValue=(Local_BaudRateInteger<<UART_BAUDRATE_INT_OFFSET)|Local_BaudRateFraction;

			/*set the value in the register*/
			Local_CurrentPtrToPer->BRR=Local_BaudRateValue;

			/*enable/disable Tx*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 , UART_CR1_TE , gastr_UartPeripheralConfig[Local_Counter].TxStatus);

			/*enable/disable Rx*/
			SET_VALUE_FOR_BIT_IN_REG(Local_CurrentPtrToPer->CR1 , UART_CR1_RE , gastr_UartPeripheralConfig[Local_Counter].RxStatus);

		}

	}
	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Uart_SendDataSync                                                                                                      *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_Data_t                                                                                           *
 *                      Desc / takes data wanted to be sent                                                                           *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function send data through Uart and it's synchronous function                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_SendDataSync(Uart_Id_t Id , Uart_Data_t Data)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	volatile Uart_RegType* Local_CurrentPtrToPer=0;

	/*check the id*/
	if(Id>UART_NUMBER_OF_CONFIGURED_PERIPHERALS)
	{
		returnValue=UART_E_NOT_OK;
	}
	else
	{
		Local_CurrentPtrToPer=Uart_BaseAddresses[gastr_UartPeripheralConfig[Id].PerId];
		/*wait until tx is empty*/
		while(!GET_BIT(Local_CurrentPtrToPer->SR , UART_SR_TXE));
		/*write the wanted data in the */
		Local_CurrentPtrToPer->DR=Data;
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Uart_SendStringSync                                                                                                    *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / String                                                                                                 *
 *                      Type / Uart_Data_t*                                                                                           *
 *                      Desc / takes data wanted to be sent                                                                           *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function send String and it's synchronous function                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_SendStringSync(Uart_Id_t Id , sint8* String)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	while(*String)
	{
		Uart_SendDataSync(Id , (uint16)(*String));
		++String;
	}
	return returnValue;
}
/**************************************************************************************************************************************
 *  Function : Uart_ReceiveDataSync                                                                                                   *
 *  Param    : IN     : Name / Id                                                                                                     *
 *                      Type / Uart_Id_t                                                                                              *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / Data                                                                                                   *
 *                      Type / Uart_Data_t*                                                                                           *
 *                      Desc / takes pointer to variable which the data will be returned on it                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Uart_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Receive data through Uart and it's synchronous function                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_ReceiveDataSync(Uart_Id_t Id , Uart_Data_t* Data)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	volatile Uart_RegType* Local_CurrentPtrToPer=0;

	/*check the id*/
	if(Id>UART_NUMBER_OF_CONFIGURED_PERIPHERALS)
	{
		returnValue=UART_E_NOT_OK;
	}
	else
	{
		Local_CurrentPtrToPer=Uart_BaseAddresses[gastr_UartPeripheralConfig[Id].PerId];
		/*wait until Rx has received data*/
		while(!GET_BIT(Local_CurrentPtrToPer->SR , UART_SR_RXNE));
		/*write the wanted data in the */
		*Data=Local_CurrentPtrToPer->DR;
	}
	return returnValue;
}


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

Uart_ErrorStatus_t Uart_ReceiveStringSync(Uart_Id_t Id , sint8* String , Uart_MaxRxBufferSize_t MaxSize , sint8 EndingChar)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	uint16 Local_Char=0;
	Uart_MaxRxBufferSize_t Local_Index= 0;
	do
	{
		Uart_ReceiveDataSync(Id , &Local_Char);
	}
	while((Local_Index<MaxSize)&&((String[Local_Index++]=(sint8)Local_Char)!=EndingChar));
	return returnValue;
}

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

Uart_ErrorStatus_t Uart_IntControl(Uart_Id_t Id , Uart_InterruptSource_t IntSource , Uart_IntState_t State)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	Uart_RegSize_t Local_IntEnPos=0;
	Uart_RegSize_t Local_IntRegOffset=0;
	volatile Uart_RegType* Local_CurrentPtrToPer=0;

	/*get the interrupt enable bit position*/
	Local_IntEnPos = IntSource & UART_INT_EN_MASK;

	/*get the register number from the base address and then mul it by 4 to get the actual reg offset*/
	Local_IntRegOffset = (uint8)IntSource >> UART_INT_REG_SHIFT;


	/*get peripheral Base Address*/
	Local_CurrentPtrToPer=Uart_BaseAddresses[gastr_UartPeripheralConfig[Id].PerId];

	/*add the offset to the base address and access it then you are currently in the wanted register*/
	SET_VALUE_FOR_BIT_IN_REG((*((Uart_RegSize_t*)Local_CurrentPtrToPer+Local_IntRegOffset)) , Local_IntEnPos , State);

	return returnValue;
}


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

Uart_ErrorStatus_t Uart_SendDataAsync(Uart_Id_t Id , Uart_TxData_t* Data )
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	/*check the id*/
	if(Id>UART_NUMBER_OF_CONFIGURED_PERIPHERALS)
	{
		returnValue=UART_E_NOT_OK;
	}
	else
	{
		g_UartTxData=*Data;
	}
	return returnValue;
}


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

Uart_ErrorStatus_t Uart_ReceiveDataASync(Uart_Id_t Id , Uart_RxData_t* Data)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	/*check the id*/
	if(Id>UART_NUMBER_OF_CONFIGURED_PERIPHERALS)
	{
		returnValue=UART_E_NOT_OK;
	}
	else
	{
		*Data=g_UartRxData;
	}
	return returnValue;
}

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

Uart_ErrorStatus_t Uart_SendDataAsync(Uart_Id_t Id , Uart_TxData_t* Data , Uart_TxCounter_t DataSize)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	/*check the id*/
	if(Id>UART_NUMBER_OF_CONFIGURED_PERIPHERALS)
	{
		returnValue=UART_E_NOT_OK;
	}
	else
	{
		if(Uart_IntTxeDetails[Id].Flag==UART_TXE_NOT_BUSY)
		{
			/*set values for tx */
			Uart_IntTxeDetails[Id].Data = Data;
			Uart_IntTxeDetails[Id].DataSizeCounter = DataSize;
			Uart_IntTxeDetails[Id].CurrentIndex = 0;
			Uart_IntTxeDetails[Id].Flag = UART_TXE_BUSY;

			/*enable interrupt*/
			Uart_IntControl(Id , UART_INT_TXE , UART_INT_ENABLED);
		}
		else
		{
			returnValue=UART_E_NOT_OK;
		}
	}
	return returnValue;
}


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
 *  Desc     : This function return the top of the queue which have been received from interrupt if there is no new data the          *
 *             function will return state indicating that                                                                             *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Uart_ErrorStatus_t Uart_ReceiveDataASync(Uart_Id_t Id , Uart_RxData_t* Data)
{
	Uart_ErrorStatus_t returnValue=UART_E_OK;
	/*check the id*/
	if(Id>UART_NUMBER_OF_CONFIGURED_PERIPHERALS)
	{
		returnValue=UART_E_NOT_OK;
	}
	else
	{
		/*if there is new elements in the queue*/
		if(Uart_IntRxDetails[Id].CurrentSize)
		{
			/*return the top of the queue*/
			*Data=Uart_IntRxDetails[Id].Data[Uart_IntRxDetails[Id].CurrentIndex];

			/*update index*/
			Uart_IntRxDetails[UART1].CurrentIndex=(Uart_IntRxDetails[UART1].CurrentIndex+1)%(UART_RX_BUFFER_SIZE-1);
			--Uart_IntRxDetails[Id].CurrentSize;
		}
		else
		{
			returnValue=UART_ERR_RX_NO_NEW_DATA;
		}
	}
	return returnValue;
}
#endif
/**********************************************************************************************************************************************************/

/***************************************************
 *                       ISR                       *
 ***************************************************/

void USART1_IRQHandler()
{
	volatile Uart_RegSize_t Local_SR=0;
	/*read SR register*/
	Local_SR=Uart_BaseAddresses[UART1]->SR;

#if UART_INT_BUFFERING_STATUS==UART_DIABLE_BUFFERING

	if(GET_BIT(Local_SR , UART_SR_RXNE))
	{

		g_UartRxData=Uart_BaseAddresses[UART1]->DR;
		/*callback function to inform the request creator that the data was sent*/
		if(ga_UartPtrToFunctoin[UART1][UART_SR_RXNE-UART_INT_PTR_BASE_OFFSET]!=NULL)
		{
			ga_UartPtrToFunctoin[UART1][UART_SR_RXNE-UART_INT_PTR_BASE_OFFSET]();
		}
	}
	else if(GET_BIT(Local_SR , UART_SR_TXE))
	{
		Uart_BaseAddresses[UART1]->DR=g_UartTxData;

		/*callback function to inform the request creator that the data was sent*/
		if(ga_UartPtrToFunctoin[UART1][UART_SR_TXE-UART_INT_PTR_BASE_OFFSET]!=NULL)
		{
			ga_UartPtrToFunctoin[UART1][UART_SR_TXE-UART_INT_PTR_BASE_OFFSET]();
		}

	}
	else
	{

	}

#elif UART_INT_BUFFERING_STATUS==UART_ENABLE_BUFFERING
	if(GET_BIT(Local_SR , UART_SR_RXNE))
	{
		/*receive data in the current empty position*/
		Uart_IntRxDetails[UART1].Data[Uart_IntRxDetails[UART1].InsertIndex]=Uart_BaseAddresses[UART1]->DR;
		/*if the queue is not full*/
		if(Uart_IntRxDetails[UART1].CurrentSize!=UART_RX_BUFFER_SIZE)
		{
			++Uart_IntRxDetails[UART1].CurrentSize;
		}
		else
		{
			/*if the current element overwritten then take the next element*/
			Uart_IntRxDetails[UART1].CurrentIndex=(Uart_IntRxDetails[UART1].CurrentIndex+1)%(UART_RX_BUFFER_SIZE-1);
		}
		/*update the insert index*/
		Uart_IntRxDetails[UART1].InsertIndex=(Uart_IntRxDetails[UART1].InsertIndex+1)%(UART_RX_BUFFER_SIZE-1);
	}
	/*check for Txe Flag must be the last interrupt to be checked as it will always be true*/
	else if(GET_BIT(Local_SR , UART_SR_TXE))
	{
		if(Uart_IntTxeDetails[UART1].CurrentIndex<Uart_IntTxeDetails[UART1].DataSizeCounter)
		{
			Uart_BaseAddresses[UART1]->DR=Uart_IntTxeDetails[UART1].Data[Uart_IntTxeDetails[UART1].CurrentIndex++];
		}
		else
		{
			/*Disable Interrupt*/
			CLEAR_BIT(Uart_BaseAddresses[UART1]->CR1 , UART_CR1_TXEIE);

			/*clear busy flag*/
			Uart_IntTxeDetails[UART1].Flag = UART_TXE_NOT_BUSY;

			/*callback function to inform the request creator  that the data was sent*/
			if(ga_UartPtrToFunctoin[UART1][UART_SR_TXE-UART_INT_PTR_BASE_OFFSET]!=NULL)
			{
				ga_UartPtrToFunctoin[UART1][UART_SR_TXE-UART_INT_PTR_BASE_OFFSET]();
			}

		}
	}

	else
	{

	}
#endif
}


