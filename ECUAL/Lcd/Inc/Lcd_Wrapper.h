/*
 *  File 	   : Lcd_Wrapper.h
 *  Created on : April 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LCD_INC_LCD_WRAPPER_H_
#define LCD_INC_LCD_WRAPPER_H_

/************************************************************************
 *                   Wrappers for Macros and Types                      *
 ************************************************************************/

#define Lcd_ChannelType         Dio_ChannelType

/************************************************************************
 *                        Wrappers for APIS                             *
 ************************************************************************/

#define Lcd_WriteChannel         Dio_WriteChannel
#define Lcd_ReadChannel			 Dio_ReadChannel

/************************************************************************/


#endif /* LCD_INC_LCD_WRAPPER_H_ */
