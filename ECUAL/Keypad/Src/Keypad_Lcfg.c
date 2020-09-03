/*
 *  File 	   : Keypad_Lcfg.c
 *  Created on : April 8, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_types.h"
#include "Dio.h"
#include "Dio_Lcfg.h"
#include "keypad_Wrapper.h"
#include "keypad.h"
#include "keypad_Lcfg.h"




/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/

Keypad_ConfigType gastr_KeypadConfigArr[KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS]=
/*                                RowsChannelIds                           	                                         ColumnsChannelIds                                    ArrayOfData                                 */
{
  /*first keypad*/
		{     {DIO_CHANNEL_A0,DIO_CHANNEL_A1,DIO_CHANNEL_A2,DIO_CHANNEL_A3}         ,            {DIO_CHANNEL_A4,DIO_CHANNEL_A5,DIO_CHANNEL_A6,DIO_CHANNEL_A7}     ,   {{'1','2','3','A'},
		                                                                                                                                                                {'4','5','6','B'},
																																								        {'7','8','9','C'},
		                                                                                                                                                                {'*','0','#','D'}}}
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**/



};



/****************************************************************************/
