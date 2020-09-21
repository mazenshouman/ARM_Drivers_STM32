/*
 *  File 	   : Led_Lcfg.h
 *  Created on : April 8, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LED_INC_LED_LCFG_H_
#define LED_INC_LED_LCFG_H_

/************************************************************************
 *                       Macros And Types                               *
 ************************************************************************/
/*
 * this type is used to set the current position of the led in terms of current
 * flow (sinking or sourcing)
 *
 * */
typedef uint8 Led_CurrentDirectionType;
#define LED_SOURCING                                (Led_CurrentDirectionType)0
#define LED_SINKING                                 (Led_CurrentDirectionType)1

/***********************************************************************************/

/************************************************************************
 *                      Configuration Structure                         *
 ************************************************************************/

typedef struct{
    Led_ChannelType                   Led_Channel;
    Led_CurrentDirectionType          Led_CurrentDirection;
    Led_StateType                     Led_InitialState;
}Led_ConfigType;

/************************************************************************
 *                      extern for Configuration Structure              *
 ************************************************************************/

extern Led_ConfigType gastr_LedConfigArr[];


/************************************************************************/



#endif /* LED_INC_LED_LCFG_H_ */
