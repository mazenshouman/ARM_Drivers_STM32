/*
 *  File 	   : Exti.c
 *  Created on : Sep 10, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Exti_Cfg.h"
#include "Exti.h"
#include "Exti_Lcfg.h"


/************************************************************************
 *        Private Includes (macros used inside this file only)          *
 ************************************************************************/
#include "Exti_MemMap.h"


/************************************************************************
 *                              macros                                  *
 ************************************************************************/
#define EXTI_PENDING_EXTI5_EXTI9_MASK                 0x000003E0
#define EXTI_LINE5_OFFSET                             5

/************************************************************************
 *                         Global Variables                             *
 ***********************************************************************/
/*array of pointer to functions used in the ISR*/
static Exti_PtrToFunction ga_ExtiPtrToFunction[EXTI_MAX_NUMBER_OF_LINES]={NULL};

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/
/**************************************************************************************************************************************
 *  Function : Exti_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to configure Lines define in                                        *
 *             Exti_LCFG and externed here to configure Lines                                                                         *
 *             Note: if you configured line to be event trigger then the pending flag won't be set and                                *
 *             we don't need to configure the NVIC nor to clear the pending flag in the ISR                                           *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_Init(void)
{
	Exti_ErrorStatus_t returnValue=EXTI_E_OK;
	Exti_NumberOfConfiguredLines_t local_Counter=0;

	/*loop on the given configuration array */
	for(local_Counter=0 ; local_Counter<EXTI_NUMBER_OF_CONFIGURED_LINES ; ++local_Counter )
	{
		/*check line id */
		if(gastr_ExtiConfigArr[local_Counter].LineId>(EXTI_MAX_NUMBER_OF_LINES-1))
		{
			returnValue=EXTI_E_NOT_OK;
			break;
		}

		/*set trigger source*/
		switch(gastr_ExtiConfigArr[local_Counter].Trigger)
		{
			case EXTI_TRIGGER_RISING_EDGE:
				SET_BIT(EXTI_BASE_ADDRESS->RTSR , gastr_ExtiConfigArr[local_Counter].LineId);
				break;
			case EXTI_TRIGGER_FAllING_EDGE:
				SET_BIT(EXTI_BASE_ADDRESS->FTSR , gastr_ExtiConfigArr[local_Counter].LineId);
				break;
			case EXTI_TRIGGER_ON_CHANGE:
				SET_BIT(EXTI_BASE_ADDRESS->RTSR , gastr_ExtiConfigArr[local_Counter].LineId);
				SET_BIT(EXTI_BASE_ADDRESS->FTSR , gastr_ExtiConfigArr[local_Counter].LineId);
				break;
			default:
				returnValue=EXTI_E_NOT_OK;
				break;
		}

		if(returnValue!=EXTI_E_NOT_OK)
		{
			/*check initial state to enable the line or not*/
			if(gastr_ExtiConfigArr[local_Counter].InitialState==EXTI_ENABLED)
			{
				/*set mode by enabling the mask register for the given line*/
				switch(gastr_ExtiConfigArr[local_Counter].Mode)
				{
					case EXTI_MODE_EVENT:
						SET_BIT(EXTI_BASE_ADDRESS->EMR , gastr_ExtiConfigArr[local_Counter].LineId);
						break;
					case EXTI_MODE_INTERRUPT:
						SET_BIT(EXTI_BASE_ADDRESS->IMR , gastr_ExtiConfigArr[local_Counter].LineId);
						break;
					default:
						returnValue=EXTI_E_NOT_OK;
						break;
				}
			}
		}
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Exti_EnableLine                                                                                                        *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / Mode                                                                                                   *
 *                      Type / Exti_Mode_t                                                                                            *
 *                      Desc / takes predefined macro for interrupt/event                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Enables interrupt/event for specific Line                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_EnableLine(Exti_LineId_t LineId , Exti_Mode_t Mode)
{
	Exti_ErrorStatus_t returnValue=EXTI_E_OK;

	/*check line id */
	if(LineId>(EXTI_MAX_NUMBER_OF_LINES-1))
	{
		returnValue=EXTI_E_NOT_OK;
	}

	else
	{
		/*set mode by enabling the mask register for the given line*/
		switch(Mode)
		{
			case EXTI_MODE_EVENT:
				SET_BIT(EXTI_BASE_ADDRESS->EMR , LineId);
				break;
			case EXTI_MODE_INTERRUPT:
				SET_BIT(EXTI_BASE_ADDRESS->IMR , LineId);
				break;
			default:
				returnValue=EXTI_E_NOT_OK;
				break;
		}
	}
	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Exti_DisableLine                                                                                                       *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / Mode                                                                                                   *
 *                      Type / Exti_Mode_t                                                                                            *
 *                      Desc / takes predefined macro for interrupt/event                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Disables interrupt/event for specific Line                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_DisableLine(Exti_LineId_t LineId , Exti_Mode_t Mode)
{
	Exti_ErrorStatus_t returnValue=EXTI_E_OK;

	/*check line id */
	if(LineId>(EXTI_MAX_NUMBER_OF_LINES-1))
	{
		returnValue=EXTI_E_NOT_OK;
	}

	else
	{
		/*disable line by clearing the corresponding bit in the mask register*/
		switch(Mode)
		{
			case EXTI_MODE_EVENT:
				CLEAR_BIT(EXTI_BASE_ADDRESS->EMR , LineId);
				break;
			case EXTI_MODE_INTERRUPT:
				CLEAR_BIT(EXTI_BASE_ADDRESS->IMR , LineId);

				/*clear pending flag by setting one in it's place*/
				SET_BIT_WITHOUT_READING(EXTI_BASE_ADDRESS->PR , LineId);
				break;
			default:
				returnValue=EXTI_E_NOT_OK;
				break;
		}
	}
	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Exti_SetTrigger                                                                                                        *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / Trigger                                                                                                *
 *                      Type / Exti_Trigger_t                                                                                         *
 *                      Desc / takes predefined macro for trigger type                                                                *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function select trigger for specific line                                                                         *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_SetTrigger(Exti_LineId_t LineId , Exti_Trigger_t Trigger)
{
	Exti_ErrorStatus_t returnValue=EXTI_E_OK;

	/*check line id */
	if(LineId>(EXTI_MAX_NUMBER_OF_LINES-1))
	{
		returnValue=EXTI_E_NOT_OK;
	}
	else
	{
		/*set trigger source*/
		switch(Trigger)
		{
			case EXTI_TRIGGER_RISING_EDGE:
				SET_BIT(EXTI_BASE_ADDRESS->RTSR , LineId);
				break;
			case EXTI_TRIGGER_FAllING_EDGE:
				SET_BIT(EXTI_BASE_ADDRESS->FTSR , LineId);
				break;
			case EXTI_TRIGGER_ON_CHANGE:
				SET_BIT(EXTI_BASE_ADDRESS->RTSR , LineId);
				SET_BIT(EXTI_BASE_ADDRESS->FTSR , LineId);
				break;
			default:
				returnValue=EXTI_E_NOT_OK;
				break;
		}
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Exti_GenerateSoftwareInterrupt                                                                                         *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function generate software interrupt/event on specific line                                                       *
 *             Note: software trigger is used for interrupt/event and is cleared in case of the interrupt be clearing the             *
 *             pending flag                                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_GenerateSoftwareInterrupt(Exti_LineId_t LineId)
{
	Exti_ErrorStatus_t returnValue=EXTI_E_OK;

	/*check line id */
	if(LineId>(EXTI_MAX_NUMBER_OF_LINES-1))
	{
		returnValue=EXTI_E_NOT_OK;
	}
	else
	{
		SET_BIT(EXTI_BASE_ADDRESS->SWIER , LineId);
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Exti_ClearPendingFlag                                                                                                  *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Clear pending flag for specific Line                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_ClearPendingFlag(Exti_LineId_t LineId)
{
	Exti_ErrorStatus_t returnValue=EXTI_E_OK;

	/*check line id */
	if(LineId>(EXTI_MAX_NUMBER_OF_LINES-1))
	{
		returnValue=EXTI_E_NOT_OK;
	}
	else
	{
		/*clear pending flag by setting one in it's place*/
		SET_BIT_WITHOUT_READING(EXTI_BASE_ADDRESS->PR , LineId);
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Exti_GetPendingFlag                                                                                                    *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_PendingFlagStatus_t                                                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function gets the pending flag status for specific line                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_PendingFlagStatus_t Exti_GetPendingFlag(Exti_LineId_t LineId)
{
	Exti_PendingFlagStatus_t returnValue;

	/*check line id */
	if(LineId>(EXTI_MAX_NUMBER_OF_LINES-1))
	{
		returnValue=EXTI_E_NOT_OK;
	}
	else
	{
		/*Read pending flag */
		returnValue=GET_BIT(EXTI_BASE_ADDRESS->PR , LineId);
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : Exti_SetCallback                                                                                                       *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / PtrToFunction                                                                                          *
 *                      Type / Exti_PtrToFunction                                                                                     *
 *                      Desc / takes the address of the call back function                                                            *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function set callback function for the wanted line                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_SetCallback(Exti_LineId_t LineId , Exti_PtrToFunction PtrToFunction)
{
	Exti_PendingFlagStatus_t returnValue;

	/*check line id and PtrToFunction*/
	if(LineId>(EXTI_MAX_NUMBER_OF_LINES-1)|| PtrToFunction==NULL)
	{
		returnValue=EXTI_E_NOT_OK;
	}
	else
	{
		/*set callback in the global array */
		ga_ExtiPtrToFunction[LineId]=PtrToFunction;
	}

	return returnValue;
}

/*************************************************************************************************************************************/

/**********************************************************
*                           ISR                           *
**********************************************************/
void EXTI0_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE0]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE0]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE0);
}

void EXTI1_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE1]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE1]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE1);
}

void EXTI2_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE2]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE2]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE2);
}

void EXTI3_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE3]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE3]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE3);
}

void EXTI4_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE4]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE4]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE4);
}

/*I took an assumption that it is not possible to generate two concurrent interrupt for the same handler as one
 * will will be pending and the other one will be active in the ISR (maybe I misunderstood this part)*/
void EXTI9_5_IRQHandler(void)
{

	if((Exti_GetPendingFlag(EXTI_LINE5)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE5]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE5]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE5);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE6)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE6]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE6]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE6);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE7)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE7]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE7]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE7);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE8)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE8]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE8]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE8);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE9)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE9]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE9]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE9);
	}
	else
	{

	}
}

/*I took an assumption that it is not possible to generate two concurrent interrupt for the same handler as one
 * will will be pending and the other one will be active in the ISR (maybe I misunderstood this part)*/
void EXTI15_10_IRQHandler(void)
{

	if((Exti_GetPendingFlag(EXTI_LINE10)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE10]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE10]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE10);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE11)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE11]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE11]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE11);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE12)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE12]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE12]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE12);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE13)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE13]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE13]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE13);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE14)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE14]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE14]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE14);
	}
	else if((Exti_GetPendingFlag(EXTI_LINE15)==EXTI_PENDING_FLAG_SET) && (ga_ExtiPtrToFunction[EXTI_LINE15]!=NULL))
	{
		ga_ExtiPtrToFunction[EXTI_LINE15]();

		/*Clear Pending Flag*/
		Exti_ClearPendingFlag(EXTI_LINE15);
	}
	else
	{

	}
}

void PVD_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE16_PVD]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE16_PVD]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE16_PVD);
}

void RTCAlarm_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE17_RTC_ALARM]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE17_RTC_ALARM]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE17_RTC_ALARM);
}


void USBWakeUp_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE18_USB_WAKEUP]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE18_USB_WAKEUP]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE18_USB_WAKEUP);
}

void ETH_WKUP_IRQHandler(void)
{
	/*execute callback function*/
	if(ga_ExtiPtrToFunction[EXTI_LINE19_ETHERNET_WAKEUP]!=NULL)
	{
		ga_ExtiPtrToFunction[EXTI_LINE19_ETHERNET_WAKEUP]();
	}

	/*Clear Pending Flag*/
	Exti_ClearPendingFlag(EXTI_LINE19_ETHERNET_WAKEUP);
}

/**************************************************************************************************************************************/
