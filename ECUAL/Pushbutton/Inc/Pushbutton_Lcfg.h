/*
 *  File 	   : Pushbutton_Lcfg.h
 *  Created on : April 8, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


#ifndef PUSHBUTTON_INC_PUSHBUTTON_LCFG_H_
#define PUSHBUTTON_INC_PUSHBUTTON_LCFG_H_

/************************************************************************
 *                       Macros And Types                               *
 ************************************************************************/


/*
 * this type is used to set the current position of the Push Button in terms of current
 * flow (sinking or sourcing)
 *
 * */
typedef uint8 Pushbutton_ActiveStateType;
#define PUSHBUTTON_ACTIVE_LOW                                (Pushbutton_ActiveStateType)0
#define PUSHBUTTON_ACTIVE_HIGH                               (Pushbutton_ActiveStateType)1


/*******************************************************************************************/

/************************************************************************
 *                      Configuration Structure                         *
 ************************************************************************/

typedef struct{
	Pushbutton_ChannelType                   Pushbutton_Channel;
	Pushbutton_ActiveStateType               Pushbutton_ActiveState;
}Pushbutton_ConfigType;

/************************************************************************
 *                      extern for Configuration Structure              *
 ************************************************************************/

extern Pushbutton_ConfigType gastr_PushbuttonConfigArr[];


/************************************************************************/

#endif
