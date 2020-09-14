/*
 *  File 	   : Exti_Lcfg.h
 *  Created on : Sep 10, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */
#ifndef EXTI_EXTI_LCFG_H_
#define EXTI_EXTI_LCFG_H_


/************************************************************************
 *                      Configuration Structure                         *
 ***********************************************************************/
typedef struct{
	Exti_LineId_t                  LineId;
	Exti_Mode_t                    Mode;
	Exti_Trigger_t                 Trigger;
	Exti_InitialState_t            InitialState;
}Exti_ConfigType;

/************************************************************************
 *                      Externed Structure instance                     *
 ***********************************************************************/

extern Exti_ConfigType gastr_ExtiConfigArr[];


/************************************************************************/


#endif /* EXTI_EXTI_LCFG_H_ */
