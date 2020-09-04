/*
 *  File 	   : Nvic_Cfg.h
 *  Created on : Sep 4, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


#ifndef NVIC_INC_NVIC_CFG_H_
#define NVIC_INC_NVIC_CFG_H_

/************************************************************************
 *                      Configuration macros                            *
 ************************************************************************/

/*
 *
 * number of configured peripherals which is the size of the configuration array of structures
 *
 * */

typedef uint8 Nvic_NumberOfConfiguredPeripheralsType;
#define NUMBER_OF_CONFIGURED_PERIPHERALS            (Nvic_NumberOfConfiguredPeripheralsType)1

/*
 * Priority Grouping Configuration taken from the SCB (both must match on the value)
 *
 * */
/*Priority Grouping Configuration*/
#define NVIC_PRIORITY_GROUPING_16GROUPS_0SUBGROUP   0
#define NVIC_PRIORITY_GROUPING_8GROUPS_2SUBGROUPS   1
#define NVIC_PRIORITY_GROUPING_4GROUPS_4SUBGROUPS   2
#define NVIC_PRIORITY_GROUPING_2GROUPS_8SUBGROUPS   3
#define NVIC_PRIORITY_GROUPING_0GROUP_16SUBGROUPS   4


/*Caution:when you change this value you have to change the same Macro on the Scb_Cfg file*/
#define NVIC_PRIORITY_GROUPING_VALUE           		NVIC_PRIORITY_GROUPING_4GROUPS_4SUBGROUPS




#endif /* NVIC_INC_NVIC_CFG_H_ */
/**************************************************************************************************************************************/
