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
int main(){
	Rcc_InitClock();
	Rcc_InitPeripheralsClock();
	Port_SetPinDirection(PORT_CHANNEL_C13,PORT_PIN_OUT_2_MHZ_PUSH_PULL);
	Scb_Init();
	Nvic_Init();
	Dio_WriteChannel(DIO_CHANNEL_C13 , STD_HIGH);
	while(1)
	{}
}
