/*
 *  File 	   : Afio_Lcfg.c
 *  Created on : Sep 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_Types.h"
#include "Afio_Cfg.h"
#include "Afio.h"
#include "Afio_Lcfg.h"

/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/


Afio_PeripheralRemapConfigType gastr_AfioPeripheralRemapConfigArr[AFIO_NUMBER_OF_REMAPPED_PERIPHERALS]=
/*            Peripheral ID                             RemapValue                  */
{
 {             AFIO_SPI1         ,             AFIO_SPI1_REMAP_A4_7_TO_A15_B3_5      },
};



Afio_ExtiRemapConfigType gastr_AfioExtiRemapConfigArr[AFIO_NUMBER_OF_REMAPPED_EXTI_LINES]=
/*              Line ID                                 RemapValue                  */
{
 {             AFIO_EXTI_LINE0         ,         AFIO_EXTI_REMAP_PORT_B      },
};



/*********************************************************************************************************/
