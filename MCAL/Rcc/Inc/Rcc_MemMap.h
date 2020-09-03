/*
 *  File 	   : Rcc_MemMap.h
 *  Created on : Aug 29, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef RCC_INC_RCC_MEMMAP_H_
#define RCC_INC_RCC_MEMMAP_H_

/******************************
 *        H/W registers       *
 *****************************/
typedef uint32 Rcc_Reg_Size_t;

typedef struct{
	Rcc_Reg_Size_t CR;
	Rcc_Reg_Size_t CFGR;
	Rcc_Reg_Size_t CIR;
	Rcc_Reg_Size_t APB2RSTR;
	Rcc_Reg_Size_t APB1RSTR;
	Rcc_Reg_Size_t AHBENR;
	Rcc_Reg_Size_t APB2ENR;
	Rcc_Reg_Size_t APB1ENR;
	Rcc_Reg_Size_t BDCR;
	Rcc_Reg_Size_t CSR;
}Rcc_RegType;

/**************************************************
 *        pointer to the register structure       *
 **************************************************/

#define RCC_BASE_ADDRESS                             ((volatile Rcc_RegType*)0x40021000)
/************************
 *        CR bits       *
 ***********************/
#define RCC_CR_PLLRDY	                             25
#define RCC_CR_PLLON                                 24
#define RCC_CR_CSSON                                 19
#define RCC_CR_HSEBYP                                18
#define RCC_CR_HSERDY                                17
#define RCC_CR_HSEON                                 16
#define RCC_CR_HSICAL                                8
#define RCC_CR_HSITRIM                               3
#define RCC_CR_HSIRDY                                1
#define RCC_CR_HSION                                 0

/*************************
 *        CFGR bits      *
 ************************/
#define RCC_CFGR_MCO                                 24
#define RCC_CFGR_USBPRE                              22
#define RCC_CFGR_PLLMUL                              18
#define RCC_CFGR_PLLXTPRE                            17
#define RCC_CFGR_PLLSRC                              16
#define RCC_CFGR_ADCPRE                              14
#define RCC_CFGR_PPRE2                               11
#define RCC_CFGR_PPRE1                               8
#define RCC_CFGR_HPRE                                4
#define RCC_CFGR_SWS                                 2
#define RCC_CFGR_SW                                  0

/************************
 *       CIR bits       *
 ***********************/
#define RCC_CIR_CSSC                                 23
#define RCC_CIR_PLLRDYC                              20
#define RCC_CIR_HSERDYC                              19
#define RCC_CIR_HSIRDYC                              18
#define RCC_CIR_LSERDYC                              17ö
#define RCC_CIR_LSIRDYC                              16
#define RCC_CIR_PLLRDYIE                             12
#define RCC_CIR_HSERDYIE                             11
#define RCC_CIR_HSIRDYIE                             10
#define RCC_CIR_LSERDYIE                             9
#define RCC_CIR_LSIRDYIE                             8
#define RCC_CIR_CSSF                                 7
#define RCC_CIR_PLLRDYF                              4
#define RCC_CIR_HSERDYF                              3
#define RCC_CIR_HSIRDYF                              2
#define RCC_CIR_LSERDYF                              1
#define RCC_CIR_LSIRDYF                              0

/************************
 *      BDCR bits       *
 ***********************/
#define RCC_BDCR_BDRST                               16
#define RCC_BDCR_RTCEN                               15
#define RCC_BDCR_RTCSEL                              8
#define RCC_BDCR_LSEBYP                              2
#define RCC_BDCR_LSERDY                              1
#define RCC_BDCR_LSEON                               0

/************************
 *       CSR bits       *
 ***********************/
#define RCC_CSR_LPWRRSTF                             31
#define RCC_CSR_WWDGRSTF                             30
#define RCC_CSR_IWDGRSTF                             29
#define RCC_CSR_SFTRSTF                              28
#define RCC_CSR_PORRSTF                              27
#define RCC_CSR_PINRSTF                              26
#define RCC_CSR_RMVF                                 24
#define RCC_CSR_LSIRDY                               1
#define RCC_CSR_LSION                                0
/******************************************************************************************************/

#endif /* RCC_INC_RCC_MEMMAP_H_ */
