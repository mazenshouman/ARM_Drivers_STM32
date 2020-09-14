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

void ToggleLed(void)
{
	Dio_FlipChannel(DIO_CHANNEL_C13);
}

void TurnLedOff(void){
	Dio_WriteChannel(DIO_CHANNEL_C13 , STD_HIGH);
}

int main(){
	Rcc_InitClock();
	Rcc_InitPeripheralsClock();
	Port_SetPinDirection(PORT_CHANNEL_C13,PORT_PIN_OUT_2_MHZ_PUSH_PULL);
	Scb_Init();
	Exti_SetCallback(EXTI_LINE0,TurnLedOff);
	SysTick_Init();
	SysTick_SetCallback(ToggleLed);
	SysTick_SetIntervalPeriodicInTicks(1000000);
	Nvic_Init();
//	SysTick_SetBusyWaitInTicks(1000000);
//	Nvic_SetPending(NVIC_EXTI0);
	while(1)
	{}
}
