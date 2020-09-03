/*
 *  File 	   : Led.c
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
#include "Led_Wrapper.h"
#include "Led_Cfg.h"
#include "Led.h"
#include "Led_Lcfg.h"


/************************************************************************/

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/

/**************************************************************************************************************************************
 *  Function : Led_Init                                                                                                               *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to initialize Leds with the initial state                           *
 *             ON/OFF)                                                                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Led_Init(void){
    Led_ConfigurationStrSizeType  u8_LoopCounter=0;
    /*
     * loop on all the configured leds and check it's status if it was on then turn it on
     *
     * */
    for(u8_LoopCounter=0 ; u8_LoopCounter<LED_NUMBER_OF_CONFIGURED_LEDS ; ++u8_LoopCounter)
    {
    	if(gastr_LedConfigArr[u8_LoopCounter].Led_InitialState==LED_ON)
    	{
    		Led_On(u8_LoopCounter);
    	}
    	else if(gastr_LedConfigArr[u8_LoopCounter].Led_InitialState==LED_OFF)
    	{
    		Led_Off(u8_LoopCounter);
    	}
    	else
    	{
    		/*report Error*/
    	}
    }
}

/**************************************************************************************************************************************
 *  Function : Led_On                                                                                                                 *
 *  Param    : IN     : Name / Led_Id                                                                                                 *
 *                      Type / Led_IdType                                                                                             *
 *                      Desc / predefine macro for led id                                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Led_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function turn on led depending on its current direction                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Led_ErrorStateType Led_On(Led_IdType Led_Id)
{
	Led_ErrorStateType returnStatus=LED_E_OK;
	if(Led_Id >= LED_NUMBER_OF_CONFIGURED_LEDS){
		returnStatus=LED_ID_OUTOFRANGE;
	}
	else
	{
		switch(gastr_LedConfigArr[Led_Id].Led_CurrentDirection){
			case LED_SOURCING:
				Led_WriteChannel(gastr_LedConfigArr[Led_Id].Led_Channel , STD_HIGH);
				break;
			case LED_SINKING:
				Led_WriteChannel(gastr_LedConfigArr[Led_Id].Led_Channel , STD_LOW);
				break;
			default:
				returnStatus= LED_CURRENT_DIRECTION_IS_NOT_DEFINED;
				break;
		}
	}
	return returnStatus;
}

/**************************************************************************************************************************************
 *  Function : Led_On                                                                                                                 *
 *  Param    : IN     : Name / Led_Id                                                                                                 *
 *                      Type / Led_IdType                                                                                             *
 *                      Desc / predefine macro for led id                                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Led_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function turn off led depending on its current direction                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Led_ErrorStateType Led_Off(Led_IdType Led_Id)
{
	Led_ErrorStateType returnStatus=LED_E_OK;
	if(Led_Id >= LED_NUMBER_OF_CONFIGURED_LEDS){
		returnStatus=LED_ID_OUTOFRANGE;
	}
	else
	{
		switch(gastr_LedConfigArr[Led_Id].Led_CurrentDirection){
			case LED_SOURCING:
				Led_WriteChannel(gastr_LedConfigArr[Led_Id].Led_Channel , STD_LOW);
				break;
			case LED_SINKING:
				Led_WriteChannel(gastr_LedConfigArr[Led_Id].Led_Channel , STD_HIGH);
				break;
			default:
				returnStatus= LED_CURRENT_DIRECTION_IS_NOT_DEFINED;
				break;
		}
	}
	return returnStatus;
}

/**************************************************************************************************************************************
 *  Function : Led_Toggle                                                                                                                 *
 *  Param    : IN     : Name / Led_Id                                                                                                 *
 *                      Type / Led_IdType                                                                                             *
 *                      Desc / predefine macro for led id                                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Led_ErrorStateType                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function toggle led depending on its current direction                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Led_ErrorStateType Led_Toggle(Led_IdType Led_Id)
{
	Led_ErrorStateType returnStatus=LED_E_OK;
	if(Led_Id >= LED_NUMBER_OF_CONFIGURED_LEDS){
		returnStatus=LED_ID_OUTOFRANGE;
	}
	else
	{
		Led_ToggleChannel(gastr_LedConfigArr[Led_Id].Led_Channel);
	}
	return returnStatus;
}

/**************************************************************************************************************************************/


