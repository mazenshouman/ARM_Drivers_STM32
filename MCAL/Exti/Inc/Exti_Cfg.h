/*
 *  File 	   : Exti_Cfg.h
 *  Created on : Sep 10, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef EXTI_EXTI_CFG_H_
#define EXTI_EXTI_CFG_H_

/************************************************************************
 *                      Configuration macros                            *
 ************************************************************************/

/*
 *
 * number of configured Lines which is the size of the configuration array of structures
 *
 * */



typedef uint8 Exti_NumberOfConfiguredLines_t;
#define EXTI_NUMBER_OF_CONFIGURED_LINES            (Exti_NumberOfConfiguredLines_t)1



/*Max number of line in the device*/
typedef uint8 Exti_MaxNumberOfLines_t;
#define EXTI_MAX_NUMBER_OF_LINES                   (Exti_MaxNumberOfLines_t)20


/************************************************************************/

#endif /* EXTI_EXTI_CFG_H_ */
