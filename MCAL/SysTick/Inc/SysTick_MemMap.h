/*
 *  File 	   : SysTick_MemMap.h
 *  Created on : Sep 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef SYSTICK_INC_SYSTICK_MEMMAP_H_
#define SYSTICK_INC_SYSTICK_MEMMAP_H_

/******************************
 *        H/W registers       *
 *****************************/

typedef uint32 SysTick_RegSize_t;

typedef struct{
	SysTick_RegSize_t CTRL;
	SysTick_RegSize_t LOAD;
	SysTick_RegSize_t VAL;
	SysTick_RegSize_t CALIB;
}SysTick_RegType;

/**************************************************
 *        pointer to the register structure       *
 **************************************************/

#define SYSTICK_BASE_ADDRESS                             ((volatile SysTick_RegType*)0xE000E010)



/******************************
 *          CTRL Bits         *
 *****************************/
#define SYSTICK_CTRL_ENABLE                              (SysTick_RegSize_t)0
#define SYSTICK_CTRL_TICKINT                             (SysTick_RegSize_t)1
#define SYSTICK_CTRL_CLKSOURCE                           (SysTick_RegSize_t)2
#define SYSTICK_CTRL_COUNTFLAG                           (SysTick_RegSize_t)16


/******************************************************************************************************/

#endif /* SYSTICK_INC_SYSTICK_MEMMAP_H_ */
