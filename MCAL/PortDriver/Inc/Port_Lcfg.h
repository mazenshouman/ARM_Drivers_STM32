/*
 *  File 	   : Port_Lcfg.h
 *  Created on : April 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


#ifndef PORTDRIVER_INC_PORT_LCFG_H_
#define PORTDRIVER_INC_PORT_LCFG_H_



/************************************************************************
 *                      Configuration Structure                         *
 ************************************************************************/
typedef struct{
	Port_PinType            Channel_ID;
	Port_PinDirectionType   Channel_Direction;
}Port_ConfigType;

/************************************************************************
 *                      Externed Structure instance                     *
 ************************************************************************/

extern Port_ConfigType gastr_PortConfigArr[];


/************************************************************************/

#endif /* PORTDRIVER_INC_PORT_LCFG_H_ */
