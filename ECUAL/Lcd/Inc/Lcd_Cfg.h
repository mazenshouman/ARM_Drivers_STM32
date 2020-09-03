/*
 *  File 	   : Lcd_Cfg.h
 *  Created on : April 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LCD_INC_LCD_CFG_H_
#define LCD_INC_LCD_CFG_H_


/*
 * this configuration parameter used to determine the number of Lcds that
 * will be configured in the Lcd_Lcfg.c file (array of structures)
 * */

typedef uint8 Lcd_ConfigurationStrSizeType;
#define LCD_NUMBER_OF_CONFIGURED_LCDS			    (Lcd_ConfigurationStrSizeType)1

typedef uint8 Lcd_NumberOfDataPinsType;
#define LCD_MAX_NUMBER_OF_DATA_PINS                     (Lcd_NumberOfDataPinsType)8

typedef uint8 Lcd_NumberOfControlPinsType;
#define LCD_MAX_NUMBER_OF_CONTROL_PINS                  (Lcd_NumberOfControlPinsType)3

#define LCD_RS                                           0
#define LCD_R_W                                          1
#define LCD_E                                            2

/*
 * if we want to initialize lcd with the same operations performed by the interal reset circuit
 * */

#define LCD_INTERAL_RESET_OPERATIONS    0

/*
 * this parameter will change the behavior of the function depending if we have
 * want to use this driver for (RTOS/Timer) or not
 * */

/*#define LCD_ACTIVATE_STATES*/



/*this definition will unlock alternative configuration structure which contains 2d array of char
 * for each lcd 4 bytes is stored(so take care with memory) and must allocated in Lcfg file */

#define LCD_ACTIVATE_CUSTOME_CHAR_MEMORY



#endif /* LCD_INC_LCD_CFG_H_ */
