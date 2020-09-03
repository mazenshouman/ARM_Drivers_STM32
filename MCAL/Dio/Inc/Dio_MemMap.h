/*
 *  File 	   : Dio_MemMap.h
 *  Created on : April 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef DIO_INC_DIO_MEMMAP_H_
#define DIO_INC_DIO_MEMMAP_H_

/************************************************************************
 *                    H/W registers and Access mechanism                *
 ************************************************************************/
typedef uint32                                Dio_RegSize_t;

typedef struct{
	Dio_RegSize_t     CRL;
	Dio_RegSize_t     CRH;
	Dio_RegSize_t     IDR;
	Dio_RegSize_t     ODR;
	Dio_RegSize_t     BSRR;
	Dio_RegSize_t     BRR;
	Dio_RegSize_t     LCKR;
	Dio_RegSize_t     Reserved[249];
}Dio_RegType;


#define DIO_BASE_ADDRESS                     ((volatile Dio_RegType*)(0x40010800))


#endif /* DIO_INC_DIO_MEMMAP_H_ */
