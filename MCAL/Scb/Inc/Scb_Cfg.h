/*
 *  File 	   : Scb_Cfg.h
 *  Created on : Sep 4, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef SCB_INC_SCB_CFG_H_
#define SCB_INC_SCB_CFG_H_


/******************************************************
 *        AIRCR Configuration for NVIC PRIORITY       *
 *****************************************************/
/*AIRCR Vectkey*/
#define SCB_AIRCR_VECTKEY                          (Scb_Reg_Size_t)0x05FA0000

/*Priority Grouping Configuration*/

#define SCB_PRIORITY_GROUPING_16GROUPS_0SUBGROUP   (Scb_Reg_Size_t)0x300
#define SCB_PRIORITY_GROUPING_8GROUPS_2SUBGROUPS   (Scb_Reg_Size_t)0x400
#define SCB_PRIORITY_GROUPING_4GROUPS_4SUBGROUPS   (Scb_Reg_Size_t)0x500
#define SCB_PRIORITY_GROUPING_2GROUPS_8SUBGROUPS   (Scb_Reg_Size_t)0x600
#define SCB_PRIORITY_GROUPING_0GROUP_16SUBGROUPS   (Scb_Reg_Size_t)0x700

/*Caution:when you change this value you have to change the same Macro on the NVIC config driver*/
#define SCB_PRIORITY_GROUPING_VALUE                SCB_PRIORITY_GROUPING_4GROUPS_4SUBGROUPS



#endif /* SCB_INC_SCB_CFG_H_ */
