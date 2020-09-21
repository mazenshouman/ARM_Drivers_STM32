/*
 *  File 	   : LedMatrix_Cfg.h
 *  Created on : Sep 20, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LEDMATRIX_LEDMATRIX_CFG_H_
#define LEDMATRIX_LEDMATRIX_CFG_H_

 /***************************************************************************************************************
 * by default led matrix will be controlled using columns(column by column) to support shift text left or right *
 * for 1088AS led matrix is common row cathode
 * for now we can configure only symmetrical LedMatrices for Ex all 8*8 or all 5*7
 *************************************************************************************************************/
/*
 * this Configuration parameter used to select the max number of Row and Columns in the Led Matrix
 *
 * */
typedef uint8 LedMatrix_NumberOfPins_t;
#define LEDMATRIX_NUMBER_OF_ROWS                            (LedMatrix_NumberOfPins_t)8
#define LEDMATRIX_NUMBER_OF_COLUMNS                         (LedMatrix_NumberOfPins_t)8



/*
 * this configuration parameter used to determine the number of LedMatrixs that
 * will be configured in the LedMatrix_Lcfg.c file (array of structures)
 * */

typedef uint8 LedMatrix_ConfigurationStrSize_t;
#define LEDMATRIX_NUMBER_OF_CONFIGURED_MODULES			       (LedMatrix_NumberOfFramesPerSecond_t)1



/*
 * configuration parameter for the number of frames per second to calcuate the tick time from it to pass it
 * to either RTOS task or timer overflow time(load value)
 * */
typedef uint8 LedMatrix_NumberOfFramesPerSecond_t;
#define LEDMATRIX_NUMBER_OF_FRAMES_PER_SECOND                  (LedMatrix_NumberOfFramesPerSecond_t)60



/*
 *this configuration selects between timer and RTOS to make decision in init function to configure
 *timer or just let the user set the timing in the RTOS task
 *
 * */


#define LEDMATRIX_TIMING_USING_TIMER                           0
#define LEDMATRIX_TIMING_USING_RTOS                            1

#define LEDMATRIX_TIMING_SYSTEM                                LEDMATRIX_TIMING_USING_TIMER


/*if timer is selected as timing system for led matrix and it uses tick in it's function then you have to set the timer freq in this
 * macro or just use the function for timer with time instead of ticks
 * *
 */

typedef uint32 LedMatrix_Freq_t;
#if LEDMATRIX_TIMING_SYSTEM==LEDMATRIX_TIMING_USING_TIMER
/*must not be less than 1000000Hz*/
#define LEDMATRIX_TIMER_FREQ_HZ                                (LedMatrix_Freq_t)1000000
#endif



/*
 * configuration parameter for the size of predefined array of data
 * */
#define LEDMATRIX_SIZE_OF_DATA_ARRAY                          7
#endif /* LEDMATRIX_LEDMATRIX_CFG_H_ */
