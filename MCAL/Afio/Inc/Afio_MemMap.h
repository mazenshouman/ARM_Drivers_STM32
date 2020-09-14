/*
 *  File 	   : Afio_MemMap.h
 *  Created on : April 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef AFIO_INC_AFIO_MEMMAP_H_
#define AFIO_INC_AFIO_MEMMAP_H_

/************************************************************************
 *                    H/W registers and Access mechanism                *
 ***********************************************************************/
typedef uint32                                Afio_RegSize_t;


typedef struct{
	Afio_RegSize_t     EVCR;
	Afio_RegSize_t     MAPR;
	Afio_RegSize_t     EXTICR1;
	Afio_RegSize_t     EXTICR2;
	Afio_RegSize_t     EXTICR3;
	Afio_RegSize_t     EXTICR4;
	Afio_RegSize_t     MAPR2;
}Afio_RegType;


#define AFIO_BASE_ADDRESS                     ((volatile Afio_RegType*)(0x40010000))
#define AFIO_EXTICR_BASE_ADDRESS              ((volatile Afio_RegSize_t*)(0x40010008))

#endif /* AFIO_INC_AFIO_MEMMAP_H_ */
