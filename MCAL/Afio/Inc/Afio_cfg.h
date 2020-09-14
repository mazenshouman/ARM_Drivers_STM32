/*
 *  File 	   : Afio_Cfg.h
 *  Created on : Sep 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef AFIO_INC_AFIO_CFG_H_
#define AFIO_INC_AFIO_CFG_H_

/************************************************************************
 *                      Configuration macros                            *
 ************************************************************************/

/*
 *
 * number of remapped peripheral which is the size of the configuration array of structures
 *
 * */

typedef uint8 Afio_NumberOfRemappedPeripherals_t;
#define AFIO_NUMBER_OF_REMAPPED_PERIPHERALS            (Afio_NumberOfRemappedPeripherals_t)1


/*
 *
 * number of remapped EXxti Lines which is the size of the configuration array of structures
 *
 * */
typedef uint8 Afio_NumberOfRemappedExtiLines_t;
#define AFIO_NUMBER_OF_REMAPPED_EXTI_LINES            (Afio_NumberOfRemappedExtiLines_t)1



#endif /* AFIO_INC_AFIO_CFG_H_ */
