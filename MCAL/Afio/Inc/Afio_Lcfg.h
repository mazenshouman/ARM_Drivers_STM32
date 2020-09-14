/*
 *  File 	   : Afio_Lcfg.h
 *  Created on : Sep 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


#ifndef AFIO_INC_AFIO_LCFG_H_
#define AFIO_INC_AFIO_LCFG_H_

/************************************************************************
 *                      Configuration Structure                         *
 ***********************************************************************/

/*peripheral remap configuration structure*/

typedef struct{
	Afio_PeripheralId_t            PeripheralId;
	Afio_RemapValue_t              RemapValue;
}Afio_PeripheralRemapConfigType;



/*Exti remap configuration structure*/

typedef struct{
	Afio_ExtiLineId_t              LineId;
	Afio_ExtiRemapValue_t          RemapValue;
}Afio_ExtiRemapConfigType;



/************************************************************************
 *                      Externed Structure instance                     *
 ***********************************************************************/

extern Afio_PeripheralRemapConfigType gastr_AfioPeripheralRemapConfigArr[];


extern Afio_ExtiRemapConfigType gastr_AfioExtiRemapConfigArr[];

/************************************************************************/

#endif /* AFIO_INC_AFIO_LCFG_H_ */
