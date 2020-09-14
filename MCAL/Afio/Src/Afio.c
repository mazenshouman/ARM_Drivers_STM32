/*
 *  File 	   : Afio.c
 *  Created on : Sep 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_Types.h"
#include "Bit_Math.h"
#include "Afio.h"
#include "Afio_Cfg.h"
#include "Afio_Lcfg.h"


/************************************************************************
 *        Private Includes (macros used inside this file only)          *
 ************************************************************************/

#include "Afio_MemMap.h"



/************************************************************************
 *                              macros                                  *
 ************************************************************************/
#define AFIO_GET_EXTICR_REG(OFFSET)               (*(AFIO_EXTICR_BASE_ADDRESS+OFFSET))

#define AFIO_TWO_BITS_MASK                        0x3
#define AFIO_THREE_BITS_MASK                      0x7
#define AFIO_FOUR_BITS_MASK                       0xF
#define AFIO_NUMBER_OF_BITS_IN_REG                32

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/
/**************************************************************************************************************************************
 *  Function : Afio_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Afio_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to rempa peripheral and remap exti line to different lines          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Afio_ErrorStatus_t Afio_Init(void)
{
	Afio_ErrorStatus_t returnValue=AFIO_E_OK;
    uint8 local_ActualLineOffset=0;
    uint8 local_RegOffset=0;
    Afio_NumberOfRemappedPeripherals_t local_PerLoopCounter=0;
    Afio_NumberOfRemappedExtiLines_t   local_ExtiLoopCounter=0;

	/*loop on peripheral remap configuration structure*/
    for(local_PerLoopCounter=0 ; local_PerLoopCounter<AFIO_NUMBER_OF_REMAPPED_PERIPHERALS ; ++local_PerLoopCounter)
    {
    	/*check peripheral id*/
    	if(gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId>AFIO_SWJ)
    	{
    		returnValue=AFIO_E_NOT_OK;
    		break;
    	}

    	/*depending on peripheral id set the remap value in it's place*/
    	switch(gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId)
    	{
    		case AFIO_SPI1 ... AFIO_USART1:
				SET_VALUE_FOR_BIT_IN_REG(AFIO_BASE_ADDRESS->MAPR , gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId , gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].RemapValue);
    			break;
    		case AFIO_TIM1 ... AFIO_TIM3:
				SET_VALUE_FOR_BITS_IN_REG(AFIO_BASE_ADDRESS->MAPR , ~(AFIO_TWO_BITS_MASK<<gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId) , gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId ,  gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].RemapValue);
    			break;
    		case AFIO_HSE_PD01:
				SET_VALUE_FOR_BIT_IN_REG(AFIO_BASE_ADDRESS->MAPR , gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId , gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].RemapValue);
				break;
    		case AFIO_SWJ:
    			SET_VALUE_FOR_BITS_IN_REG(AFIO_BASE_ADDRESS->MAPR , ~(AFIO_THREE_BITS_MASK<<gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId) , gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].PeripheralId ,  gastr_AfioPeripheralRemapConfigArr[local_PerLoopCounter].RemapValue);
				break;
    		default:
    			returnValue=AFIO_E_NOT_OK;
    			break;
    	}

    	if(returnValue!=AFIO_E_NOT_OK)
    	{
    		/*loop on exti configuration structure */
    	    for(local_ExtiLoopCounter=0 ; local_ExtiLoopCounter<AFIO_NUMBER_OF_REMAPPED_EXTI_LINES ; ++local_ExtiLoopCounter)
    	    {
    	    	/*check line id*/
    	    	if(gastr_AfioExtiRemapConfigArr[local_ExtiLoopCounter].LineId > AFIO_EXTI_LINE15)
    	    	{
    	    		returnValue=AFIO_E_NOT_OK;
    	    		break;
    	    	}

				/*get the correct offset for the line in the regiter*/
    	    	local_ActualLineOffset=gastr_AfioExtiRemapConfigArr[local_ExtiLoopCounter].LineId%local_ActualLineOffset;

    	    	/*get register offset */
    	    	local_RegOffset=gastr_AfioExtiRemapConfigArr[local_ExtiLoopCounter].LineId/local_ActualLineOffset;

				/*set remap value for the line*/
    	    	SET_VALUE_FOR_BITS_IN_REG(AFIO_GET_EXTICR_REG(local_RegOffset) , ~(AFIO_FOUR_BITS_MASK<<local_ActualLineOffset) , local_ActualLineOffset , gastr_AfioExtiRemapConfigArr[local_ExtiLoopCounter].RemapValue);
    	    }
    	}

    }
    return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Afio_RemapPeripheral                                                                                                   *
 *  Param    : IN     : Name / PeripheralId                                                                                           *
 *                      Type / Afio_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / RemapValue                                                                                             *
 *                      Type / Afio_RemapValue_t                                                                                      *
 *                      Desc / takes predefined macro remap value                                                                     *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Afio_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function remap specific peripheral to different pins                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Afio_ErrorStatus_t Afio_RemapPeripheral(Afio_PeripheralId_t PeripheralId , Afio_RemapValue_t RemapValue)
{
	Afio_ErrorStatus_t returnValue=AFIO_E_OK;

	/*check peripheral id*/
	if(PeripheralId>AFIO_SWJ)
	{
		returnValue=AFIO_E_NOT_OK;
	}
	else
	{
		/*depending on peripheral id set the remap value in it's place*/
		switch(PeripheralId)
		{
			case AFIO_SPI1 ... AFIO_USART1:
				SET_VALUE_FOR_BIT_IN_REG(AFIO_BASE_ADDRESS->MAPR , PeripheralId , RemapValue);
				break;
			case AFIO_TIM1 ... AFIO_TIM3:
				SET_VALUE_FOR_BITS_IN_REG(AFIO_BASE_ADDRESS->MAPR , ~(AFIO_TWO_BITS_MASK<<PeripheralId) , PeripheralId ,  RemapValue);
				break;
			case AFIO_HSE_PD01:
				SET_VALUE_FOR_BIT_IN_REG(AFIO_BASE_ADDRESS->MAPR , PeripheralId , RemapValue);
				break;
			case AFIO_SWJ:
				SET_VALUE_FOR_BITS_IN_REG(AFIO_BASE_ADDRESS->MAPR , ~(AFIO_THREE_BITS_MASK<<PeripheralId) , PeripheralId ,  RemapValue);
				break;
			default:
				returnValue=AFIO_E_NOT_OK;
				break;
		}
	}
    return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Afio_RemapExtiLine                                                                                                     *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Afio_ExtiLineId_t                                                                                      *
 *                      Desc / takes predefined macro for Exti Line id                                                                *
 *                                                                                                                                    *
 *                      Name / RemapValue                                                                                             *
 *                      Type / Afio_ExtiRemapValue_t                                                                                  *
 *                      Desc / takes predefined macro for remap value                                                                 *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Afio_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function remap specific Exti Line to different Port                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Afio_ErrorStatus_t Afio_RemapExtiLine(Afio_ExtiLineId_t LineId , Afio_ExtiRemapValue_t RemapValue)
{
	Afio_ErrorStatus_t returnValue=AFIO_E_OK;
    uint8 local_ActualLineOffset=0;
    uint8 local_RegOffset=0;

	/*check line id*/
	if(LineId > AFIO_EXTI_LINE15)
	{
		returnValue=AFIO_E_NOT_OK;
	}
	else
	{
		/*get the correct offset for the line in the regiter*/
		local_ActualLineOffset=LineId%local_ActualLineOffset;

		/*get register offset */
		local_RegOffset=LineId/local_ActualLineOffset;

		/*set remap value for the line*/
		SET_VALUE_FOR_BITS_IN_REG(AFIO_GET_EXTICR_REG(local_RegOffset) , ~(AFIO_FOUR_BITS_MASK<<local_ActualLineOffset) , local_ActualLineOffset , RemapValue);
	}

    return returnValue;
}


/************************************************************************/
