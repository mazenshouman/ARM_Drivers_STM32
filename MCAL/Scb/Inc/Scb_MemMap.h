/*
 *  File 	   : Scb_MemMap.h
 *  Created on : Sep 4, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


#ifndef SCB_INC_SCB_MEMMAP_H_
#define SCB_INC_SCB_MEMMAP_H_

/******************************
 *        H/W registers       *
 *****************************/
typedef uint32 Scb_Reg_Size_t;


typedef struct{
	Scb_Reg_Size_t     SCB_CPUID;
	Scb_Reg_Size_t     SCB_ICSR;
	Scb_Reg_Size_t     SCB_VTOR;
	Scb_Reg_Size_t     SCB_AIRCR;
	Scb_Reg_Size_t     SCB_SCR;
	Scb_Reg_Size_t     SCB_CCR;
	Scb_Reg_Size_t     SCB_SHPR1;
	Scb_Reg_Size_t     SCB_SHPR2;
	Scb_Reg_Size_t     SCB_SHPR3;
	Scb_Reg_Size_t     SCB_SHCRS;
	Scb_Reg_Size_t     SCB_CFSR;
	Scb_Reg_Size_t     SCB_HFSR;
	Scb_Reg_Size_t     SCB_MMAR;
	Scb_Reg_Size_t     SCB_BFAR;
}Scb_RegType;

/**************************************************
 *        pointer to the register structure       *
 **************************************************/

#define SCB_BASE_ADDRESS                             ((volatile Scb_RegType*)0xE000ED00)

/**************************************************/

/************************
 *       AIRCR bits     *
 ***********************/
#define SCB_AIRCR_VECTKEYSTAT                        16
#define SCB_AIRCR_ENDIANESS                          15
#define SCB_AIRCR_PRIGROUP                           8
#define SCB_AIRCR_SYSRESETREQ                        2
#define SCB_AIRCR_VECTCLRACTIVE                      1
#define SCB_AIRCR_VECTRESET                          0

/**************************************************/
#endif
