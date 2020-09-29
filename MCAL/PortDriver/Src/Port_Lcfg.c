/*
 *  File 	   : Port_Lcfg.c
 *  Created on : Sep 2, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_Types.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "Port_Lcfg.h"



/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/
Port_ConfigType gastr_PortConfigArr[NUMBER_OF_CONFIGURED_PINS]=
/*            channel ID                             Direction                 */
{
 {          PORT_CHANNEL_C13         ,       PORT_PIN_OUT_2_MHZ_PUSH_PULL       },
 {          PORT_CHANNEL_A9          ,       PORT_PIN_OUT_10_MHZ_AF_OPEN_DRAIN  },
 {          PORT_CHANNEL_A10         ,       PORT_PIN_IN_FLAOTING               },
};


/****************************************************************************/
