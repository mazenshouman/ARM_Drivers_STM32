/*
 *  File 	   : keypad_Wrapper.h
 *  Created on : Sep 20, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LEDMATRIX_INC_LEDMATRIX_WRAPPER_H_
#define LEDMATRIX_INC_LEDMATRIX_WRAPPER_H_

/************************************************************************
 *                   Wrappers for Macros and Types                      *
 ************************************************************************/

#define LedMatrix_ChannelType                       Dio_ChannelType
#define LedMatrix_NumberOfTicks_t                   SysTick_LoadValue_t
/************************************************************************
 *                        Wrappers for APIS                             *
 ************************************************************************/

#define LedMatrix_WriteChannel                      Dio_WriteChannel
#define LedMatrix_SetBusyWaitInTicks                SysTick_SetBusyWaitInTicks
#define LedMatrix_TimerInit                         SysTick_Init

#endif /* LEDMATRIX_INC_LEDMATRIX_WRAPPER_H_ */
