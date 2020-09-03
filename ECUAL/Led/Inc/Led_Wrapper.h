/*
 *  File 	   : Led_Wrapper.h
 *  Created on : April 8, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LED_INC_LED_WRAPPER_H_
#define LED_INC_LED_WRAPPER_H_


/************************************************************************
 *                   Wrappers for Macros and Types                      *
 ************************************************************************/

#define Led_ChannelType         Dio_ChannelType

/************************************************************************
 *                        Wrappers for APIS                             *
 ************************************************************************/

#define Led_WriteChannel        Dio_WriteChannel
#define Led_ToggleChannel		Dio_FlipChannel

/************************************************************************/



#endif /* LED_INC_LED_WRAPPER_H_ */
