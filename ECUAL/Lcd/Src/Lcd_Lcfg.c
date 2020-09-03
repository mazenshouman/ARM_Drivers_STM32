/*
 *  File 	   : Lcd_Lcfg.c
 *  Created on : April 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_types.h"
#include "Dio.h"
#include "Lcd_Wrapper.h"
#include "Lcd_Cfg.h"
#include "Lcd.h"
#include "Lcd_Lcfg.h"

/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/
/*if you want to save custom char with the configuration for later use this define custom char here
 * if not so you need to pass it from the caller function in the app
 *
 * */
#ifdef LCD_MAX_NUMBER_OF_CUST_CHAR

Lcd_CustCharType Lcd_ArrCustChar[LCD_MAX_NUMBER_OF_CUST_CHAR][LCD_MAX_SIZE_OF_CUST_CHAR_ARR]={{0b00000000 , 0b00011011 , 0b00011011 , 0b00011111 , 0b00001110 , 0b00000100 , 0b00000000 , 0b00000000 , 0b00000000 ,0b00000000}};

Lcd_ConfigType gastr_LcdConfigArr[LCD_NUMBER_OF_CONFIGURED_LCDS]=
{
		/*                                                   DataPins                                                                                                      ControlPins                                   CursorOrDiplayShiftCommand                                EntryModeCommand 	                         FunctionSetCommand                                   DisplayContorlCommand        */
		/*First LCD*/
		{ {DIO_CHANNEL_A0 , DIO_CHANNEL_A1 , DIO_CHANNEL_A2 , DIO_CHANNEL_A3 , DIO_CHANNEL_A4 , DIO_CHANNEL_A5 , DIO_CHANNEL_A6 , DIO_CHANNEL_A7} , {DIO_CHANNEL_B5 , DIO_CHANNEL_B6 , DIO_CHANNEL_B7} ,    (LCD_DISPLAY_OR_CURSOR_SHIFT_LEFT|LCD_DISPLAY_SHIFT) , (LCD_DISPLAY_SHIFT_OFF|LCD_ADDRESS_INCREMENT) , (LCD_FONT_5_8|LCD_TWO_DISPLAY_LINE|LCD_8_BIT_DATA_MODE) ,   (LCD_DISPLAY_ON|LCD_BLINKING_OFF|LCD_CURSOR_ON)   , 1  , Lcd_ArrCustChar }

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
};

#else

Lcd_ConfigType gastr_LcdConfigArr[LCD_NUMBER_OF_CONFIGURED_LCDS]=
{
		/*                                                   DataPins                                                                                                      ControlPins                                   CursorOrDiplayShiftCommand                                EntryModeCommand 	                         FunctionSetCommand                                   DisplayContorlCommand        */
		/*First LCD*/
		{ {DIO_CHANNEL_A0 , DIO_CHANNEL_A1 , DIO_CHANNEL_A2 , DIO_CHANNEL_A3 , DIO_CHANNEL_A4 , DIO_CHANNEL_A5 , DIO_CHANNEL_A6 , DIO_CHANNEL_A7} , {DIO_CHANNEL_B5 , DIO_CHANNEL_B6 , DIO_CHANNEL_B7} , ,    (LCD_DISPLAY_OR_CURSOR_SHIFT_LEFT|LCD_DISPLAY_SHIFT) , (LCD_DISPLAY_SHIFT_OFF|LCD_ADDRESS_INCREMENT) , (LCD_FONT_5_8|LCD_TWO_DISPLAY_LINE|LCD_8_BIT_DATA_MODE) ,   (LCD_DISPLAY_ON|LCD_BLINKING_OFF|LCD_CURSOR_ON)   }

		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
};


#endif
