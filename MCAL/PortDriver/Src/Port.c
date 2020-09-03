/*
 *  File 	   : Port.c
 *  Created on : Sep 2, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_Types.h"
#include "Bit_Math.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "Port_Lcfg.h"

    

/************************************************************************
 *        Private Includes (macros used inside this file only)          *
 ************************************************************************/
#include "Port_MemMap.h"



/************************************************************************
 *                              macros                                  *
 ************************************************************************/

#define PORT_NUMBER_OF_BITS_IN_REG                       16
#define PORT_GET_BASE_ADDRESS(PORT_OFFSET)               ((PORT_BASE_ADDRESS)+(PORT_OFFSET))
#define PORT_GET_EXTI_CR_REG(REG_OFFSET)                 (*(AFIO_EXTI_CR_BASE_ADDRESS+REG_OFFSET))
#define PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG             4
#define PORT_CONTROL_REG_BASE_MASK                       (Port_RegSize_t)(0x0000000F)
#define PORT_SHIFT_VALUE_PULL_UP_DOWN                    4
#define PORT_PIN_0                                       0
#define PORT_PIN_7                                       7
#define PORT_PIN_8                                       8
#define PORT_PIN_15                                      15
#define PORT_NUMBER_OF_PIN_CONT_REG                      8

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/


/**************************************************************************************************************************************
 *  Function : Dio_ReadChannel                                                                                                        *
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

Port_ErrorStatus_t Port_Init(void){
	volatile Port_ErrorStatus_t returnError=PORT_E_OK;
	Port_NumberOfConfiguredPinsType u8_localLoopCounter=0;
	Port_PortType u8_PortNumber=0;
	Port_PinType u8_PinActualNumber=0;

	for(u8_localLoopCounter=0 ; u8_localLoopCounter < NUMBER_OF_CONFIGURED_PINS ; ++u8_localLoopCounter){

		/*
		 * this line gets the port value which when added to the base address will access the correct CR reg
		 **/

		u8_PortNumber =(Port_PortType) ((gastr_PortConfigArr[u8_localLoopCounter].Channel_ID / PORT_NUMBER_OF_BITS_IN_REG));

		/*
		 * this line gets the actual pin number for the selected port so if the value of the entered pin is for ex 10 this means
		 * port C PIN 2
		 * */

		u8_PinActualNumber = (Port_PinType) (gastr_PortConfigArr[u8_localLoopCounter].Channel_ID % PORT_NUMBER_OF_BITS_IN_REG);

		/*
		 * check the pull-up and pull-down attachments
		 *
		 * */

		if(gastr_PortConfigArr[u8_localLoopCounter] . Channel_Direction==PORT_PIN_IN_PULL_DOWN)
		{
			SET_BIT_WITHOUT_READING(PORT_GET_BASE_ADDRESS(u8_PortNumber)->BRR,u8_PinActualNumber);
		}
		else if(gastr_PortConfigArr[u8_localLoopCounter] . Channel_Direction==PORT_PIN_IN_PULL_UP)
		{
			SET_BIT_WITHOUT_READING(PORT_GET_BASE_ADDRESS(u8_PortNumber)->BSRR,u8_PinActualNumber);

			/*reduce the value to the actual value of PORT_PIN_IN_PULL_UP*/
			gastr_PortConfigArr[u8_localLoopCounter] . Channel_Direction-=PORT_SHIFT_VALUE_PULL_UP_DOWN;
		}
		else
		{
			//do nothing
		}

		/*
		 * depending on the pin number switch between CRL and CRH to configure the pin
		 *
		 * */

		switch(u8_PinActualNumber)
		{
			case PORT_PIN_0 ... PORT_PIN_7:
			/*this line will mask the register in the wanted position by shifting base mask and flip it then shift the value of direction to the wanted position and finally or both values together and set them in the register*/
				SET_VALUE_FOR_BITS_IN_REG(PORT_GET_BASE_ADDRESS(u8_PortNumber)->CRL , ~(PORT_CONTROL_REG_BASE_MASK<<(u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG)),u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG, gastr_PortConfigArr[u8_localLoopCounter] . Channel_Direction);
				break;
			case PORT_PIN_8 ... PORT_PIN_15:
			/*here i had to subtract 8 from the value of the actual pin number so that we start from the beginning of the control high register */
				u8_PinActualNumber-=PORT_NUMBER_OF_PIN_CONT_REG;
				SET_VALUE_FOR_BITS_IN_REG(PORT_GET_BASE_ADDRESS(u8_PortNumber)->CRH , ~(PORT_CONTROL_REG_BASE_MASK<<(u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG)),u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG, gastr_PortConfigArr[u8_localLoopCounter] . Channel_Direction);
			break;
			default:
				returnError=PORT_E_NOT_OK;
				break;
		}
	}
	return returnError;
}


Port_ErrorStatus_t Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
	Port_ErrorStatus_t returnError=PORT_E_OK;
	Port_PortType u8_PortNumber=0;
	Port_PinType u8_PinActualNumber=0;
	/*
	 * this line gets the port value which when added to the base address will access the correct CR reg
	 **/

	u8_PortNumber =(Port_PortType) ((Pin / PORT_NUMBER_OF_BITS_IN_REG));

	/*
	 * this line gets the actual pin number for the selected port so if the value of the entered pin is for ex 10 this means
	 * port C PIN 2
	 * */

	u8_PinActualNumber = (Port_PinType) (Pin % PORT_NUMBER_OF_BITS_IN_REG);

	/*
	 * check the pull-up and pull-down attachments
	 *
	 * */

	if(Direction==PORT_PIN_IN_PULL_DOWN)
	{
		SET_BIT_WITHOUT_READING(PORT_GET_BASE_ADDRESS(u8_PortNumber)->BRR,u8_PinActualNumber);
	}
	else if(Direction==PORT_PIN_IN_PULL_UP)
	{
		SET_BIT_WITHOUT_READING(PORT_GET_BASE_ADDRESS(u8_PortNumber)->BSRR,u8_PinActualNumber);

		/*reduce the value to the actual value of PORT_PIN_IN_PULL_UP*/
		Direction-=PORT_SHIFT_VALUE_PULL_UP_DOWN;
	}
	else
	{
		//do nothing
	}

	/*
	 * depending on the pin number switch between CRL and CRH to configure the pin
	 *
	 * */

	switch(u8_PinActualNumber)
	{
		case PORT_PIN_0 ... PORT_PIN_7:
		/*this line will mask the register in the wanted position by shifting base mask and flip it then shift the value of direction to the wanted position and finally or both values together and set them in the register*/
			SET_VALUE_FOR_BITS_IN_REG(PORT_GET_BASE_ADDRESS(u8_PortNumber)->CRL , ~(PORT_CONTROL_REG_BASE_MASK<<(u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG)),u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG, Direction);
			break;
		case PORT_PIN_8 ... PORT_PIN_15:
		/*here i had to subtract 8 from the value of the actual pin number so that we start from the beginning of the control high register */
			u8_PinActualNumber-=PORT_NUMBER_OF_PIN_CONT_REG;
			SET_VALUE_FOR_BITS_IN_REG(PORT_GET_BASE_ADDRESS(u8_PortNumber)->CRH , ~(PORT_CONTROL_REG_BASE_MASK<<(u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG)),u8_PinActualNumber*PORT_NUMBER_OF_BITS_FOR_PIN_CONT_REG, Direction);
		break;
		default:
			returnError=PORT_E_NOT_OK;
			break;
	}

    return returnError;
}

/****************************************************************************/




