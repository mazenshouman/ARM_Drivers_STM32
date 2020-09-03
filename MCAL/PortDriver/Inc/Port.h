/*
 *  File 	   : Port.h
 *  Created on : Sep 2, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef PORTDRIVER_INC_PORT_H_
#define PORTDRIVER_INC_PORT_H_

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Port_Cfg.h"

/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/

typedef uint8 Port_PinType;

#define PORT_CHANNEL_A0              (Port_PinType)0
#define PORT_CHANNEL_A1              (Port_PinType)1
#define PORT_CHANNEL_A2              (Port_PinType)2
#define PORT_CHANNEL_A3              (Port_PinType)3
#define PORT_CHANNEL_A4              (Port_PinType)4
#define PORT_CHANNEL_A5              (Port_PinType)5
#define PORT_CHANNEL_A6              (Port_PinType)6
#define PORT_CHANNEL_A7              (Port_PinType)7
#define PORT_CHANNEL_A8              (Port_PinType)8
#define PORT_CHANNEL_A9              (Port_PinType)9
#define PORT_CHANNEL_A10             (Port_PinType)10
#define PORT_CHANNEL_A11             (Port_PinType)11
#define PORT_CHANNEL_A12             (Port_PinType)12
#define PORT_CHANNEL_A13             (Port_PinType)13
#define PORT_CHANNEL_A14             (Port_PinType)14
#define PORT_CHANNEL_A15             (Port_PinType)15


#define PORT_CHANNEL_B0              (Port_PinType)16
#define PORT_CHANNEL_B1              (Port_PinType)17
#define PORT_CHANNEL_B2              (Port_PinType)18
#define PORT_CHANNEL_B3              (Port_PinType)19
#define PORT_CHANNEL_B4              (Port_PinType)20
#define PORT_CHANNEL_B5              (Port_PinType)21
#define PORT_CHANNEL_B6              (Port_PinType)22
#define PORT_CHANNEL_B7              (Port_PinType)23
#define PORT_CHANNEL_B8              (Port_PinType)24
#define PORT_CHANNEL_B9              (Port_PinType)25
#define PORT_CHANNEL_B10             (Port_PinType)26
#define PORT_CHANNEL_B11             (Port_PinType)27
#define PORT_CHANNEL_B12             (Port_PinType)28
#define PORT_CHANNEL_B13             (Port_PinType)29
#define PORT_CHANNEL_B14             (Port_PinType)30
#define PORT_CHANNEL_B15             (Port_PinType)31


#define PORT_CHANNEL_C13             (Port_PinType)45
#define PORT_CHANNEL_C14             (Port_PinType)46
#define PORT_CHANNEL_C15             (Port_PinType)47


typedef enum{
	PORT_PIN_IN_ANALOG,
	PORT_PIN_OUT_10_MHZ_PUSH_PULL,
	PORT_PIN_OUT_2_MHZ_PUSH_PULL,
	PORT_PIN_OUT_50_MHZ_PUSH_PULL,
	PORT_PIN_IN_FLAOTING,
	PORT_PIN_OUT_10_MHZ_OPEN_DRAIN,
	PORT_PIN_OUT_2_MHZ_OPEN_DRAIN,
	PORT_PIN_OUT_50_MHZ_OPEN_DRAIN,
	PORT_PIN_IN_PULL_DOWN,
	PORT_PIN_OUT_10_MHZ_AF_PUSH_PULL,
	PORT_PIN_OUT_2_MHZ_AF_PUSH_PULL,
	PORT_PIN_OUT_50_MHZ_AF_PUSH_PULL,
	PORT_PIN_IN_PULL_UP,
	PORT_PIN_OUT_10_MHZ_AF_OPEN_DRAIN,
	PORT_PIN_OUT_2_MHZ_AF_OPEN_DRAIN,
	PORT_PIN_OUT_50_MHZ_AF_OPEN_DRAIN,
}Port_PinDirectionType;

/*typedef enum{
	NO_RES,
	PULL_UP_RES
}Port_PinAttachmentType;
*/
/************************************************************************
 *                           Error macros                               *
 ************************************************************************/
typedef uint8 Port_ErrorStatus_t;
#define PORT_E_OK                    (Port_ErrorStatus_t)0
#define PORT_E_NOT_OK                (Port_ErrorStatus_t)1
#define PORT_PULL_UP_RES_WRONG_USE   (Port_ErrorStatus_t)2
#define PORT_PIN_NUMBER_OUT_OF_RANGE (Port_ErrorStatus_t)3

/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/

typedef uint8 Port_PortType;
#define PORTA                        (Port_PortType)0
#define PORTB                        (Port_PortType)1
#define PORTC                        (Port_PortType)2

/************************************************************************/

/************************************************************************
 *                    PORT functions' prototypes                        *
 ************************************************************************/

/**************************************************************************************************************************************
 *  Function : Port_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : ErrorStatus_t                                                                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to configure pins define in                                         *
 *             PORT_LCFG and externed here to configure pins                                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Port_ErrorStatus_t Port_Init(void);

#if PortSetPinDirectionApi
Port_ErrorStatus_t Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
#endif

#endif /* PORTDRIVER_INC_PORT_H_ */
