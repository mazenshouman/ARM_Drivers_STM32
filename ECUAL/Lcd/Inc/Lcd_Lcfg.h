/*
 *  File 	   : Lcd_Lcfg.h
 *  Created on : April 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LCD_INC_LCD_LCFG_H_
#define LCD_INC_LCD_LCFG_H_


/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/



/************************************************************************
 *                      Configuration Structure                         *
 ************************************************************************/
#if 0
typedef struct{
	Lcd_ChannelType                        Lcd_DataPinsArr[LCD_MAX_NUMBER_OF_DATA_PINS];
	Lcd_ChannelType                        Lcd_ControlPinsArr[LCD_MAX_NUMBER_OF_CONTROL_PINS];
	Lcd_NumberOfDataPinsType               Lcd_NumberOfDataPinsMode:5;
	Lcd_FontSizeType                       Lcd_FontSize:3;
	Lcd_NumbeOfDisplayLinesType            Lcd_NumberOfDisplayLines:4;
	Lcd_DisplayOnOffType                   Lcd_DisplayOnOff:3;
	Lcd_CursorOnOffType                    Lcd_CursorOnOff:2;
	Lcd_BlinkingOnOffType                  Lcd_BlinkingOnOff:1;
	Lcd_AddressIncDecType                  Lcd_AddressIncDec:2;
	Lcd_DisplayShiftOnWritingType          Lcd_DispalyShiftOnWriting:1;
	Lcd_DisplayOrCursorShiftType           Lcd_DisplayOrCursor:4;
	Lcd_DisplayOrCursorShiftDirectionType  Lcd_ShiftDirecton:3;
}Lcd_ConfigType;

#endif


#ifndef LCD_ACTIVATE_CUSTOME_CHAR_MEMORY

typedef struct{
	Lcd_ChannelType                        Lcd_DataPinsArr[LCD_MAX_NUMBER_OF_DATA_PINS];
	Lcd_ChannelType                        Lcd_ControlPinsArr[LCD_MAX_NUMBER_OF_CONTROL_PINS];
	Lcd_CursorOrDiplayShiftType            Lcd_CursorOrDiplayShift:5;
	Lcd_EntryModeType				       Lcd_EntryMode:3;
	Lcd_FunctionSetType                    Lcd_FunctionSet:6;
	Lcd_DisplayContorlType                 Lcd_DisplayControl:4;
}Lcd_ConfigType;

#else

typedef struct{
	Lcd_ChannelType                        Lcd_DataPinsArr[LCD_MAX_NUMBER_OF_DATA_PINS];
	Lcd_ChannelType                        Lcd_ControlPinsArr[LCD_MAX_NUMBER_OF_CONTROL_PINS];
	Lcd_CursorOrDiplayShiftType            Lcd_CursorOrDiplayShift:5;
	Lcd_EntryModeType				       Lcd_EntryMode:3;
	Lcd_FunctionSetType                    Lcd_FunctionSet:6;
	Lcd_DisplayContorlType                 Lcd_DisplayControl:4;
	Lcd_CustCharMaxNumberType              Lcd_NumberOfCustomChar:4;
	Lcd_CustCharType                       (*Lcd_PtrArrCustomChar)[LCD_MAX_SIZE_OF_CUST_CHAR_ARR];
}Lcd_ConfigType;

#endif

/************************************************************************
 *                      extern for Configuration Structure              *
 ************************************************************************/

extern Lcd_ConfigType gastr_LcdConfigArr[];


/************************************************************************/


#endif /* LCD_INC_LCD_LCFG_H_ */
