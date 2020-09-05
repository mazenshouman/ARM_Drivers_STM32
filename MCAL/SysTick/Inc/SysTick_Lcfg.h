/*
 *  File 	   : SysTick_Lcfg.h
 *  Created on : Sep 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef SYSTICK_INC_SYSTICK_LCFG_H_
#define SYSTICK_INC_SYSTICK_LCFG_H_

#if 0
/************************************************************************
 *                         Macros And Types                             *
 ***********************************************************************/
typedef uint32 SysTick_ClockSource_t;
#define SYSTICK_CLOCK_SOURCE_HCLK_DIVIDED_8             (SysTick_ClockSource_t)0
#define SYSTICK_CLOCK_SOURCE_HCLK                       (SysTick_ClockSource_t)1

typedef uint32 SysTick_InterruptStatus_t;
#define SYSTICK_INTERRUPT_DISABLE                       (SysTick_InterruptStatus_t)0
#define SYSTICK_INTERRUPT_ENABLE                        (SysTick_InterruptStatus_t)1

/*if systick enabled the load register value will be loaded to the value register and start counting*/
typedef uint32 SysTick_Status_t;
#define SYSTICK_DISABLE                                 (SysTick_InterruptStatus_t)0
#define SYSTICK_ENABLE                                  (SysTick_InterruptStatus_t)1

/*max 24 bit value*/
typedef uint32 SysTick_LoadValue_t;


/************************************************************************
 *                      Configuration Structure                         *
 ***********************************************************************/
typedef struct{
	SysTick_LoadValue_t              InitialLoadValue:24;
	SysTick_ClockSource_t            ClockSource:2;
	SysTick_Status_t                 InitialStatus:1;
	SysTick_InterruptStatus_t        InterruptInitialStatus:1;
}SysTick_ConfigType;

/************************************************************************
 *                      Externed Structure instance                     *
 ***********************************************************************/

extern SysTick_ConfigType gstr_SysTickConfig;


/************************************************************************/
#endif

#endif /* SYSTICK_INC_SYSTICK_LCFG_H_ */
