/*
 *  File 	   : Port_MemMap.h
 *  Created on : Sep 2, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef PORTDRIVER_INC_PORT_MEMMAP_H_
#define PORTDRIVER_INC_PORT_MEMMAP_H_

/************************************************************************
 *                    H/W registers and Access mechanism                *
 ************************************************************************/
typedef uint32                                Port_RegSize_t;
typedef uint32                                Afio_RegSize_t;

typedef struct{
	Port_RegSize_t     CRL;
	Port_RegSize_t     CRH;
	Port_RegSize_t     IDR;
	Port_RegSize_t     ODR;
	Port_RegSize_t     BSRR;
	Port_RegSize_t     BRR;
	Port_RegSize_t     LCKR;
	Port_RegSize_t     Reserved[249];
}PORT_RegType;


#define PORT_BASE_ADDRESS                     ((volatile PORT_RegType*)(0x40010800))

typedef struct{
	Afio_RegSize_t     EVCR;
	Afio_RegSize_t     MAPR;
	Afio_RegSize_t     EXTICR1;
	Afio_RegSize_t     EXTICR2;
	Afio_RegSize_t     EXTICR3;
	Afio_RegSize_t     EXTICR4;
	Afio_RegSize_t     MAPR2;
}Afio_RegType;

#define AFIO_BASE_ADDRESS                     ((volatile AFIO_RegType*)(0x0x40010000))
#define AFIO_EXTI_CR_BASE_ADDRESS             ((volatile Afio_RegSize_t*)(0x0x40010008))

#endif /* PORTDRIVER_INC_PORT_MEMMAP_H_ */
