/*
 *  File 	   : Port_Lcfg.h
 *  Created on : Sep 2, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef PORTDRIVER_INC_PORT_CFG_H_
#define PORTDRIVER_INC_PORT_CFG_H_

/************************************************************************
 *                      Configuration macros                            *
 ************************************************************************/
/*
 * this configuration used by port.h to enable or disable runtime API for
 * configuration for port
 *
 * */

#define PortSetPinDirectionApi			1


/*
 *
 * number of configured pins must be between 0 and 35
 * which will be the size of the configuration array of structures
 *
 * */

typedef uint8 Port_NumberOfConfiguredPinsType;
#define NUMBER_OF_CONFIGURED_PINS      (Port_NumberOfConfiguredPinsType)1
/*21 for app 6*/

/****************************************************************************/

#endif /* PORTDRIVER_INC_PORT_CFG_H_ */
