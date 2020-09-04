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
#include "Nvic_Cfg.h"
#include "Nvic.h"
#include "Nvic_Lcfg.h"



/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/
Nvic_ConfigType gastr_NvicConfigArr[NUMBER_OF_CONFIGURED_PERIPHERALS]=
/*            Peipheral ID                             PriorityGroupNumber                  PrioritySubgroupNumber                 */
{
 {          NVIC_EXTI0         ,                     NVIC_PRIORITY_GROUP_2          ,       NVIC_PRIORITY_SUBGROUP_1},
};


/****************************************************************************/

