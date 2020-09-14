/*
 *  File 	   : Nvic_Lcfg.c
 *  Created on : Sep 4, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_Types.h"
#include "Exti_Cfg.h"
#include "Exti.h"
#include "Exti_Lcfg.h"


/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/

Exti_ConfigType gastr_ExtiConfigArr[EXTI_NUMBER_OF_CONFIGURED_LINES]=
/*            Line ID                             Mode                               Trigger                              Initial State*/
{
 {          EXTI_LINE0           ,          EXTI_MODE_INTERRUPT      ,        EXTI_TRIGGER_RISING_EDGE           ,             EXTI_ENABLED},
};



/****************************************************************************/
