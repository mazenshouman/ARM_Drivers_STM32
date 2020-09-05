/*
 *  File 	   : SysTick_Cfg.h
 *  Created on : Sep 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


#ifndef SYSTICK_INC_SYSTICK_CFG_H_
#define SYSTICK_INC_SYSTICK_CFG_H_

/************************************************************************
 *                      Configuration macros                            *
 ************************************************************************/


/************************************************
 *          Clock Source Configuration          *
 ************************************************/

typedef uint32 SysTick_ClockSource_t;
#define SYSTICK_CLOCK_SOURCE_HCLK_DIVIDED_8             (SysTick_ClockSource_t)0
#define SYSTICK_CLOCK_SOURCE_HCLK                       (SysTick_ClockSource_t)1

#define SYSTICK_CLOCK_SOURCE                            SYSTICK_CLOCK_SOURCE_HCLK_DIVIDED_8


/************************************************
 *          SysTick Clock input Value           *
 ************************************************/

/*
 * this value before applying the sysTick prescale
 * */
/*
 * this value must be changed depending on the configured HCLK prescale and SYSCLK
 * */

#define SYSTICK_HCLK_FREQ                               (uint32)80000000

/*****************************************************************************************/

#endif /* SYSTICK_INC_SYSTICK_CFG_H_ */
