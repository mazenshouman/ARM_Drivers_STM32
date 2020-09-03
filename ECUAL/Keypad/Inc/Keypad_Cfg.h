/*
 *  File 	   : Keypad_Cfg.h
 *  Created on : April 10, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef KEYPAD_INC_KEYPAD_CFG_H_
#define KEYPAD_INC_KEYPAD_CFG_H_

/*************************************************************************************************************
 * by defaul keypad input pins must configured as input pull up or pulled up by external resistors
 *     And Rows Must be configured as output and columns as input
 *************************************************************************************************************/
/*
 * this Configuration parameter used to select the number of Row and Columns in the Keypad Matrix
 *
 * */
typedef uint8 Keypad_NumberOfPinsType;
#define KEYPAD_NUMBER_OF_ROWS                            (Keypad_NumberOfPinsType)4
#define KEYPAD_NUMBER_OF_COLUMNS                         (Keypad_NumberOfPinsType)4


/*
 * this configuration parameter used to determine the number of Keypads that
 * will be configured in the Keypad_Lcfg.c file (array of structures)
 * */

typedef uint8 Keypad_ConfigurationStrSizeType;
#define KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS			    (Keypad_ConfigurationStrSizeType)1

typedef sint8 keypad_OutputDataType;
#define KEYPAD_NO_KEY_IS_PRESSED                        (keypad_OutputDataType)0


/*
 * this parameter will change the behavior of the function depending if we have
 * want to use this driver for periodic update (RTOS/Timer) or not
 * */

/*#define KEYPAD_PERIODIC_UPDATE*/


#ifdef KEYPAD_PERIODIC_UPDATE
/*this parameter will be used for future enhancement if call back function is used for
 * each state
 * */
#define KEYPAD_NUMBER_OF_STATES                          4

/*
 * this parameter is used as number of checks done in each state to check the correctness of the state
 * (number of check per state)depending on its value the periodic time must change
 * if it was configured as 1 then to check the switch full states it will take 4 cycles only
 * */
typedef uint8 Keypad_StateCounterType;
#define KEYPAD_COUNTER_VALUE                             1


#endif
/************************************************************************/


#endif /* KEYPAD_INC_KEYPAD_CFG_H_ */
