/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mazen Sh
 */

#include "Std_Types.h"
#include "Rcc.h"
#include "Port.h"
#include "Dio.h"
#include "Scb.h"
#include "Nvic.h"
#include "SysTick.h"
#include "Exti.h"
#include "Afio.h"
#include "Uart.h"
//void ToggleLed(void)
//{
//	Dio_FlipChannel(DIO_CHANNEL_C13);
//}
//
//void TurnLedOff(void){
//	Dio_WriteChannel(DIO_CHANNEL_C13 , STD_HIGH);
//}


int main(){
//	sint8* data="mazen ahmed";
	uint8 Arr[10]={0};
	uint8 index=0;
	Rcc_InitClock();
	Rcc_InitPeripheralsClock();
	Port_Init();
	Uart_Init();
	Nvic_EnableInterrupt(NVIC_USART1);
	Uart_IntControl(UART_Id0 , UART_INT_RXNE , UART_INT_ENABLED);


//	Uart_SendDataAsync(UART_Id0 , (uint8*)data , 12);
//	uint16 value=0;
//	Port_SetPinDirection(PORT_CHANNEL_C13,PORT_PIN_OUT_2_MHZ_PUSH_PULL);
//	Scb_Init();
//	Exti_SetCallback(EXTI_LINE0,TurnLedOff);
//	SysTick_Init();
//	SysTick_SetCallback(ToggleLed);
//	SysTick_SetIntervalPeriodicInTicks(1000000);
//	Nvic_Init();
//	SysTick_SetBusyWaitInTicks(1000000);
//	Nvic_SetPending(NVIC_EXTI0);

	while(1)
	{
		if(Uart_ReceiveDataASync(UART_Id0 , &Arr[index])!=UART_ERR_RX_NO_NEW_DATA)
		{
			index++;
		}
	}
}
