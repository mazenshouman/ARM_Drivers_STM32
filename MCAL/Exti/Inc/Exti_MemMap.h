/*
 *  File 	   : Exti_MemMap.h
 *  Created on : Sep 10, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef EXTI_EXTI_MEMMAP_H_
#define EXTI_EXTI_MEMMAP_H_

/******************************
 *        H/W registers       *
 *****************************/
typedef uint32 Exti_Reg_Size_t;

typedef struct{
	Exti_Reg_Size_t            IMR;
	Exti_Reg_Size_t            EMR;
	Exti_Reg_Size_t            RTSR;
	Exti_Reg_Size_t            FTSR;
	Exti_Reg_Size_t            SWIER;
	Exti_Reg_Size_t            PR;
}Exti_RegType;

/**************************************************
 *        pointer to the register structure       *
 **************************************************/

#define EXTI_BASE_ADDRESS                             ((volatile Exti_RegType*)0x40010400)

/******************************************************************************************************/

#endif /* EXTI_EXTI_MEMMAP_H_ */
