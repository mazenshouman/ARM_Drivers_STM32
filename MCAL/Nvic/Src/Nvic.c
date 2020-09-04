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
#include "Nvic_Cfg.h"
#include "Nvic.h"
#include "Nvic_Lcfg.h"

/************************************************************************
 *        Private Includes (macros used inside this file only)          *
 ************************************************************************/
#include "Nvic_MemMap.h"


/************************************************************************
 *                              macros                                  *
 ************************************************************************/
#define NVIC_NUMBER_PERIPHERAL_REG                                32
#define NVIC_IPR_PRIORITY_VALUE_OFFSET                            4

/**************************************************************************************************************************************/
/************************************************************************
 *                    Private Function's Implementation                 *
 ***********************************************************************/

/**************************************************************************************************************************************
 *  Function : Nvic_SetInterruptSoftwarePriority                                                                                      *
 *  Param    : IN     : Name / GroupNumber                                                                                            *
 *                      Type / Nvic_PriorityValue_t                                                                                   *
 *                      Desc / takes predefined macro for Group number                                                                *
 *                      Name / SubgroupNumber                                                                                         *
 *                      Type / Nvic_PriorityValue_t                                                                                   *
 *                      Desc / takes predefined macro for Subgroup number                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function check the priority value and return error status value                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

static Nvic_ErrorStatus_t Nvic_CheckPriorityValue(Nvic_PriorityValue_t GroupNumber , Nvic_PriorityValue_t SubgroupNumber)
{
	Nvic_ErrorStatus_t returnValue=NVIC_E_OK;
	switch(NVIC_PRIORITY_GROUPING_VALUE)
	{
		case NVIC_PRIORITY_GROUPING_16GROUPS_0SUBGROUP:
			if(SubgroupNumber>NVIC_PRIORITY_SUBGROUP_0 || GroupNumber>NVIC_PRIORITY_GROUP_15)
			{
				returnValue=NVIC_E_NOT_OK;
			}
			break;
		case NVIC_PRIORITY_GROUPING_8GROUPS_2SUBGROUPS:
			if(SubgroupNumber>NVIC_PRIORITY_SUBGROUP_1 ||GroupNumber>NVIC_PRIORITY_GROUP_7)
			{
				returnValue=NVIC_E_NOT_OK;
			}
			break;
		case NVIC_PRIORITY_GROUPING_4GROUPS_4SUBGROUPS:
			if(SubgroupNumber>NVIC_PRIORITY_SUBGROUP_3 ||GroupNumber>NVIC_PRIORITY_GROUP_3)
			{
				returnValue=NVIC_E_NOT_OK;
			}
			break;
		case NVIC_PRIORITY_GROUPING_2GROUPS_8SUBGROUPS:
			if(SubgroupNumber>NVIC_PRIORITY_SUBGROUP_7 ||GroupNumber>NVIC_PRIORITY_GROUP_1)
			{
				returnValue=NVIC_E_NOT_OK;
			}
			break;
		case NVIC_PRIORITY_GROUPING_0GROUP_16SUBGROUPS:
			if(SubgroupNumber>NVIC_PRIORITY_SUBGROUP_15 ||GroupNumber>NVIC_PRIORITY_GROUP_1)
			{
				returnValue=NVIC_E_NOT_OK;
			}
		break;
		default:
			returnValue=NVIC_E_NOT_OK;
			break;
	}
	return returnValue;
}

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/


/**************************************************************************************************************************************
 *  Function : Nvic_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to configure Peripheral define in                                   *
 *             Nvic_LCFG and externed here to configure pins                                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_Init(void)
{
	Nvic_ErrorStatus_t returnValue=NVIC_E_OK;
	Nvic_NumberOfConfiguredPeripheralsType  local_counter=0;
	Nvic_PeripheralId_t local_PeripheralOffset=0;
	Nvic_PeripheralId_t local_RegOffset=0;
	/*this offset is used to set the software priority*/
	Nvic_PriorityValue_t local_ActualGroupValue=0;

	/*check peripheral Id value*/
	if(gastr_NvicConfigArr[local_counter].PeripheralId>NVIC_DMA2_Channel4_5)
	{
		returnValue=NVIC_E_NOT_OK;
	}
	else
	{
		/*loop on the configuration array*/
		for(local_counter=0;local_counter<NUMBER_OF_CONFIGURED_PERIPHERALS;++local_counter)
		{
			/*get the acutal peripheral bit in the register*/
			local_PeripheralOffset=gastr_NvicConfigArr[local_counter].PeripheralId%NVIC_NUMBER_PERIPHERAL_REG;

			/*get the Register offset in for the peripheral*/
			local_RegOffset=gastr_NvicConfigArr[local_counter].PeripheralId/NVIC_NUMBER_PERIPHERAL_REG;

			/*get the group priority Actual Value*/
			local_ActualGroupValue=gastr_NvicConfigArr[local_counter].PriorityGroupNumber<<NVIC_PRIORITY_GROUPING_VALUE;

			/*enable the specified peripheral*/
			SET_BIT_WITHOUT_READING(NVIC_BASE_ADDRESS->ISER[local_RegOffset] , local_PeripheralOffset);

			/*check the priority values*/
			returnValue=Nvic_CheckPriorityValue(gastr_NvicConfigArr[local_counter].PriorityGroupNumber , gastr_NvicConfigArr[local_counter].PrioritySubgroupNumber);

			/*set the software priority*/
			if(returnValue==NVIC_E_OK)
			{
				NVIC_BASE_ADDRESS->IPR[gastr_NvicConfigArr[local_counter].PeripheralId]=(local_ActualGroupValue|gastr_NvicConfigArr[local_counter].PrioritySubgroupNumber)<<NVIC_IPR_PRIORITY_VALUE_OFFSET;
			}
		}
	}
	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Nvic_EnableInterrupt                                                                                                   *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Enables interrupt for specific peripheral                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_EnableInterrupt(Nvic_PeripheralId_t PeripheralID)
{
	Nvic_ErrorStatus_t returnValue=NVIC_E_OK;
	Nvic_PeripheralId_t local_PeripheralOffset=0;
	Nvic_PeripheralId_t local_RegOffset=0;

	/*check peripheral Id value*/
	if(PeripheralID>NVIC_DMA2_Channel4_5)
	{
		returnValue=NVIC_E_NOT_OK;
	}
	else
	{
		/*get the acutal peripheral bit in the register*/
		local_PeripheralOffset=PeripheralID%NVIC_NUMBER_PERIPHERAL_REG;

		/*get the Register offset in for the peripheral*/
		local_RegOffset=PeripheralID/NVIC_NUMBER_PERIPHERAL_REG;

		/*enable the specified peripheral*/
		SET_BIT_WITHOUT_READING(NVIC_BASE_ADDRESS->ISER[local_RegOffset] , local_PeripheralOffset);
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Nvic_DisableInterrupt                                                                                                  *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Disables interrupt for specific peripheral                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_DisableInterrupt(Nvic_PeripheralId_t PeripheralID)
{
	Nvic_ErrorStatus_t returnValue=NVIC_E_OK;
	Nvic_PeripheralId_t local_PeripheralOffset=0;
	Nvic_PeripheralId_t local_RegOffset=0;

	/*check peripheral Id value*/
	if(PeripheralID>NVIC_DMA2_Channel4_5)
	{
		returnValue=NVIC_E_NOT_OK;
	}
	else
	{
		/*get the acutal peripheral bit in the register*/
		local_PeripheralOffset=PeripheralID%NVIC_NUMBER_PERIPHERAL_REG;

		/*get the Register offset in for the peripheral*/
		local_RegOffset=PeripheralID/NVIC_NUMBER_PERIPHERAL_REG;

		/*enable the specified peripheral*/
		SET_BIT_WITHOUT_READING(NVIC_BASE_ADDRESS->ICER[local_RegOffset] , local_PeripheralOffset);
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Nvic_SetPending                                                                                                        *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function set pending flag for specific peripheral                                                                 *
 *             Note: pending flag is automatically clearing at the start of the ISR                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_SetPending(Nvic_PeripheralId_t PeripheralID)
{
	Nvic_ErrorStatus_t returnValue=NVIC_E_OK;
	Nvic_PeripheralId_t local_PeripheralOffset=0;
	Nvic_PeripheralId_t local_RegOffset=0;

	/*check peripheral Id value*/
	if(PeripheralID>NVIC_DMA2_Channel4_5)
	{
		returnValue=NVIC_E_NOT_OK;
	}
	else
	{
		/*get the acutal peripheral bit in the register*/
		local_PeripheralOffset=PeripheralID%NVIC_NUMBER_PERIPHERAL_REG;

		/*get the Register offset in for the peripheral*/
		local_RegOffset=PeripheralID/NVIC_NUMBER_PERIPHERAL_REG;

		/*enable the specified peripheral*/
		SET_BIT_WITHOUT_READING(NVIC_BASE_ADDRESS->ISPR[local_RegOffset] , local_PeripheralOffset);
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Nvic_ClearPending                                                                                                      *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Clear pending flag for specific peripheral                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_ClearPending(Nvic_PeripheralId_t PeripheralID)
{
	Nvic_ErrorStatus_t returnValue=NVIC_E_OK;
	Nvic_PeripheralId_t local_PeripheralOffset=0;
	Nvic_PeripheralId_t local_RegOffset=0;

	/*check peripheral Id value*/
	if(PeripheralID>NVIC_DMA2_Channel4_5)
	{
		returnValue=NVIC_E_NOT_OK;
	}
	else
	{
		/*get the acutal peripheral bit in the register*/
		local_PeripheralOffset=PeripheralID%NVIC_NUMBER_PERIPHERAL_REG;

		/*get the Register offset in for the peripheral*/
		local_RegOffset=PeripheralID/NVIC_NUMBER_PERIPHERAL_REG;

		/*enable the specified peripheral*/
		SET_BIT_WITHOUT_READING(NVIC_BASE_ADDRESS->ICPR[local_RegOffset] , local_PeripheralOffset);
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Nvic_ReadActiveFlag                                                                                                    *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_InterruptActiveStatus_t                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the state of active flag for specific peripheral                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_InterruptActiveStatus_t Nvic_ReadActiveFlag(Nvic_PeripheralId_t PeripheralID)
{
	Nvic_InterruptActiveStatus_t returnValue;
	Nvic_PeripheralId_t local_PeripheralOffset=0;
	Nvic_PeripheralId_t local_RegOffset=0;

	/*check peripheral Id value*/
	if(PeripheralID>NVIC_DMA2_Channel4_5)
	{
		returnValue=NVIC_E_NOT_OK;
	}
	else
	{
		/*get the acutal peripheral bit in the register*/
		local_PeripheralOffset=PeripheralID%NVIC_NUMBER_PERIPHERAL_REG;

		/*get the Register offset in for the peripheral*/
		local_RegOffset=PeripheralID/NVIC_NUMBER_PERIPHERAL_REG;

		/*enable the specified peripheral*/
		returnValue=GET_BIT(NVIC_BASE_ADDRESS->IABR[local_RegOffset] , local_PeripheralOffset);
	}
	return returnValue;

}

/**************************************************************************************************************************************
 *  Function : Nvic_SetInterruptSoftwarePriority                                                                                      *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                      Name / GroupNumber                                                                                            *
 *                      Type / Nvic_PriorityValue_t                                                                                   *
 *                      Desc / takes predefined macro for Group number                                                                *
 *                      Name / SubgroupNumber                                                                                         *
 *                      Type / Nvic_PriorityValue_t                                                                                   *
 *                      Desc / takes predefined macro for Subgroup number                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function sets software priority for specific peripheral choose the right value for group and                      *
 *             group so theat the fucntion doesn't detect error in the given values                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_SetInterruptSoftwarePriority(Nvic_PeripheralId_t PeripheralID , Nvic_PriorityValue_t GroupNumber , Nvic_PriorityValue_t SubgroupNumber)
{
	Nvic_ErrorStatus_t returnValue=NVIC_E_OK;
	/*this offset is used to set the software priority*/
	Nvic_PriorityValue_t local_ActualGroupValue=0;

	/*check peripheral Id value*/
	if(PeripheralID>NVIC_DMA2_Channel4_5)
	{
		returnValue=NVIC_E_NOT_OK;
	}
	else
	{
		/*get the group priority Actual Value*/
		local_ActualGroupValue=GroupNumber<<NVIC_PRIORITY_GROUPING_VALUE;

		/*check the priority values*/
		returnValue=Nvic_CheckPriorityValue(GroupNumber , SubgroupNumber);

		/*set the software priority*/
		if(returnValue==NVIC_E_OK)
		{
			NVIC_BASE_ADDRESS->IPR[PeripheralID]=(local_ActualGroupValue|SubgroupNumber)<<NVIC_IPR_PRIORITY_VALUE_OFFSET;
		}
	}

	return returnValue;
}
