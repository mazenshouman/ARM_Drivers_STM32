/*
 * Nvic_MemMap.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mazen Sh
 */

#ifndef NVIC_INC_NVIC_MEMMAP_H_
#define NVIC_INC_NVIC_MEMMAP_H_


/******************************
 *        H/W registers       *
 *****************************/
typedef uint32 Nvic_Reg_Size_t;

/*I used this type with the IPR register as it's byte accessible register to reduce code complexity*/
typedef uint8  Nvic_Ipr_Size_t;

typedef struct{
	Nvic_Reg_Size_t ISER[32];
	Nvic_Reg_Size_t ICER[32];
	Nvic_Reg_Size_t ISPR[32];
	Nvic_Reg_Size_t ICPR[32];
	Nvic_Reg_Size_t IABR[64];
	Nvic_Ipr_Size_t IPR[81];
}Nvic_RegType;


/**************************************************
 *        pointer to the register structure       *
 **************************************************/

#define NVIC_BASE_ADDRESS                             ((volatile Nvic_RegType*)0xE000E100)

/******************************************************************************************************/

#endif /* NVIC_INC_NVIC_MEMMAP_H_ */
