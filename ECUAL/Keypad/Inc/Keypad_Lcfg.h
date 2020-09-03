/*
 *  File 	   : Keypad_Lcfg.h
 *  Created on : April 10, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef KEYPAD_INC_KEYPAD_LCFG_H_
#define KEYPAD_INC_KEYPAD_LCFG_H_

/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/
/************************************************************************
 *                      Configuration Structure                         *
 ************************************************************************/

typedef struct{
	Keypad_ChannelType                   Keypad_RowsChannelArr[KEYPAD_NUMBER_OF_ROWS];
	Keypad_ChannelType                   Keypad_ColumnsChannelArr[KEYPAD_NUMBER_OF_COLUMNS];
	keypad_OutputDataType				 Keypad_ArrOutputCharacters[KEYPAD_NUMBER_OF_ROWS][KEYPAD_NUMBER_OF_COLUMNS];
}Keypad_ConfigType;


/************************************************************************
 *                      extern for Configuration Structure              *
 ************************************************************************/

extern Keypad_ConfigType gastr_KeypadConfigArr[];


/************************************************************************/

#endif /* KEYPAD_INC_KEYPAD_LCFG_H_ */
