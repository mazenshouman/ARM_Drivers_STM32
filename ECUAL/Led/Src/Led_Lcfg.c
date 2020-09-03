/*
 *  File 	   : Led_Lcfg.c
 *  Created on : April 8, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_types.h"
#include "Dio_Lcfg.h"
#include "Dio.h"
#include "Led_Wrapper.h"
#include "Led_Cfg.h"
#include "Led.h"
#include "Led_Lcfg.h"
/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/

Led_ConfigType gastr_LedConfigArr[LED_NUMBER_OF_CONFIGURED_LEDS]=
/*            channel ID                      CurrentDirection                          InitialState*/
{{          DIO_CHANNEL_B0         ,            LED_SOURCING                ,              LED_OFF                },
 {          DIO_CHANNEL_B1         ,            LED_SOURCING                ,              LED_OFF                }
};





/****************************************************************************/
