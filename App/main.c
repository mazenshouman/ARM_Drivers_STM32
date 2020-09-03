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


int main(){

	Rcc_InitClock();
	Rcc_InitPeripheralsClock();
	Port_SetPinDirection(PORT_CHANNEL_C13,PORT_PIN_OUT_2_MHZ_PUSH_PULL);
	Dio_WriteChannel(DIO_CHANNEL_C13 , STD_HIGH);
	while(1)
	{}
}
