/*
 *  File 	   : SysTick.c
 *  Created on : Sep 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "SysTick_Cfg.h"
#include "SysTick.h"
#include "SysTick_Lcfg.h"

/************************************************************************
 *        Private Includes (macros used inside this file only)          *
 ************************************************************************/
#include "SysTick_MemMap.h"

/************************************************************************
 *                              macros                                  *
 ************************************************************************/
typedef uint8 Systick_Intervaltype_t;
#define SYSTICK_INTERVAL_SINGLE          (Systick_Intervaltype_t)0
#define SYSTICK_INTERVAL_PERIODIC        (Systick_Intervaltype_t)1
/************************************************************************
 *                        Global Variables                              *
 ************************************************************************/

/************************************************
 *          Callback pointer to function        *
 ***********************************************/
static SysTick_PtrToFunction_t SysTick_PtrToFunction=NULL;
/**************************************************/

/*this variable use as clockfreq to obtain the tick time for the peripheral*/
static volatile uint32 SysTick_ClockFreq=0;

/*this variable used as flag to check if we want single interval in the ISR or not*/
static volatile uint32 SysTick_IntervalType=SYSTICK_INTERVAL_SINGLE;

/*this variable is used as counter inside the ISR*/
static volatile uint32 SysTick_Counter=0;

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/
/**************************************************************************************************************************************
 *  Function : SysTick_Init                                                                                                           *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function pre-compile configuration to set clock source                                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_Init(void)
{

	/*set clock source to the configured value and set global clock freq variable to the current clock freq*/
	switch(SYSTICK_CLOCK_SOURCE)
	{
		case SYSTICK_CLOCK_SOURCE_HCLK_DIVIDED_8:
			SYSTICK_BASE_ADDRESS->CTRL=SYSTICK_CLOCK_SOURCE;
			SysTick_ClockFreq=SYSTICK_HCLK_FREQ/NUMBER_EIGHT;
			break;
		case SYSTICK_CLOCK_SOURCE_HCLK:
			SET_BIT_WITHOUT_READING(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_CLKSOURCE);
			SysTick_ClockFreq=SYSTICK_HCLK_FREQ;
			break;
		default:
			break;
	}
	/*another way to set the values*/
#if 0
	/*set clock source to the default value*/
	SYSTICK_BASE_ADDRESS->CTRL=SYSTICK_CLOCK_SOURCE<<SYSTICK_CTRL_CLKSOURCE;

	SysTick_ClockFreq=SYSTICK_HCLK_FREQ/(NUMBER_ONE<<((!SYSTICK_CLOCK_SOURCE)*3));
#endif
}


/**************************************************************************************************************************************
 *  Function : SysTick_SetBusyWaitInTicks                                                                                             *
 *  Param    : IN     : Name / NumberOfTicks                                                                                          *
 *                      Type / SysTick_LoadValue_t                                                                                    *
 *                      Desc / value to be set to the load register max 24 bit                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function is a synchronous function used to make busy wait for specific time                                       *
 *             specified in number of ticks                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_SetBusyWaitInTicks(SysTick_LoadValue_t NumberOfTicks)
{
	/*disable peripheral to ensure that nothing will interrupt this configuration*/
	CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);

	/*disable interrupt*/
	/*as if we want to make busy waiting without interrupt*/
	CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_TICKINT);

	/*set load value*/
	/*we don't need to clear the value register as when we enable the peripheral it will take the value in load register*/
	SYSTICK_BASE_ADDRESS->LOAD=NumberOfTicks;

	/*enable peripheral*/
	SET_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);

	/*wait of the underflow flag*/
	while(!GET_BIT(SYSTICK_BASE_ADDRESS->CTRL , SYSTICK_CTRL_COUNTFLAG));

	/*execute call back fucntion if it was set*/
	if(SysTick_PtrToFunction!=NULL)
	{
		SysTick_PtrToFunction();
	}

	/*disable peripheral*/
	CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);
}

/**************************************************************************************************************************************
 *  Function : SysTick_SetIntervalSingleInTicks                                                                                             *
 *  Param    : IN     : Name / NumberOfTicks                                                                                          *
 *                      Type / SysTick_LoadValue_t                                                                                    *
 *                      Desc / value to be set to the load register max 24 bit                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function is a Asynchronous function used to make Single interval for specific time                                       *
 *             specified in number of ticks                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_SetIntervalSingleInTicks(SysTick_LoadValue_t NumberOfTicks)
{
	/*disable peripheral to ensure that nothing will interrupt this configuration*/
	CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);

	/*set load value*/
	/*we don't need to clear the value register as when we enable the peripheral it will take the value in load register*/
	SYSTICK_BASE_ADDRESS->LOAD=NumberOfTicks;

	/*enable interrupt*/
	SET_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_TICKINT);

	/*set interval variable to single interval*/
	SysTick_IntervalType=SYSTICK_INTERVAL_SINGLE;

	/*enable peripheral*/
	SET_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);
}


/**************************************************************************************************************************************
 *  Function : SysTick_SetIntervalSingleInTicks                                                                                       *
 *  Param    : IN     : Name / NumberOfTicks                                                                                          *
 *                      Type / SysTick_LoadValue_t                                                                                    *
 *                      Desc / value to be set to the load register max 24 bit                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function is a Asynchronous function used to make periodic interval for specific time                              *
 *             specified in number of ticks                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_SetIntervalPeriodicInTicks(SysTick_LoadValue_t NumberOfTicks)
{
	/*disable peripheral to ensure that nothing will interrupt this configuration*/
	CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);

	/*set load value with value-1 as the data sheet specified this information*/
	/*we don't need to clear the value register as when we enable the peripheral it will take the value in load register*/
	SYSTICK_BASE_ADDRESS->LOAD=NumberOfTicks-1;

	/*enable interrupt*/
	SET_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_TICKINT);

	/*set interval variable to periodic interval*/
	SysTick_IntervalType=SYSTICK_INTERVAL_PERIODIC;

	/*enable peripheral*/
	SET_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);

}


/**************************************************************************************************************************************
 *  Function : SysTick_StopInterval                                                                                                   *
 *  Param    : IN     : Noe                                                                                                           *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function stops the ongoing interval by disabling the peripheral                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_StopInterval(void)
{
	/*disable peripheral to ensure that nothing will interrupt this configuration*/
	CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);
}

/**************************************************************************************************************************************
 *  Function : SytTick_GetElapsedTimeInTicks                                                                                          *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the time in tick since the timer started this interval                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

SysTick_LoadValue_t SytTick_GetElapsedTimeInTicks(void)
{
	/*is the interval is periodic take in consideration that the first interval will be ticks-1 so the elapse value for
	 * the first interval will be short by one tick*/
	return ((SYSTICK_BASE_ADDRESS->LOAD - SYSTICK_BASE_ADDRESS->VAL)+(SysTick_Counter*SYSTICK_BASE_ADDRESS->LOAD));
}

/**************************************************************************************************************************************
 *  Function : SytTick_GetRemainingTimeInTicks                                                                                        *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the remaining time in tick until the value register reach zero                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

SysTick_LoadValue_t SytTick_GetRemainingTimeInTicks(void)
{
	return SYSTICK_BASE_ADDRESS->VAL;
}

/**************************************************************************************************************************************
 *  Function : SysTick_SetCallback                                                                                                    *
 *  Param    : IN     : Name / PtrToFunction                                                                                          *
 *                      Type / SysTick_PtrToFunction_t                                                                                *
 *                      Desc / takes the address of the function wanted to be callback                                                *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : SysTick_ErrorStatus_t                                                                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function set the callback function                                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

SysTick_ErrorStatus_t SysTick_SetCallback(SysTick_PtrToFunction_t PtrToFunction)
{
	SysTick_ErrorStatus_t returnValue=SYSTICK_E_OK;

	/*check for NULL pointer*/
	if(PtrToFunction==NULL)
	{
		returnValue=SYSTICK_E_NOT_OK;
	}
	else
	{
		SysTick_PtrToFunction=PtrToFunction;
	}
	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : SysTick_DeInit                                                                                                           *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function pre-compile configuration to set clock source and initialize the module                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/
void SysTick_Deinit(void)
{

	/*clear load and value register*/
	SYSTICK_BASE_ADDRESS->LOAD=0;

	/*this clear the val register and clear the flag*/
	SYSTICK_BASE_ADDRESS->VAL=0;

	/*disable the peripheral*/
	/*disable interrupt */
	/*set clock source to the default value*/
	SYSTICK_BASE_ADDRESS->CTRL=0;

	/*set pointer to function to NULL*/
	SysTick_PtrToFunction=NULL;
}

/**************************************************************************************************/

/*****************************************
 *                ISR                    *
 ****************************************/

void SysTick_Handler(void)
{
	/*if not cleared it will overflow eventually*/
	SysTick_Counter++;

	if(SysTick_IntervalType==SYSTICK_INTERVAL_SINGLE)
	{
		/*disable peripheral*/
		CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_ENABLE);

		/*disable interrupt*/
		/*as if we want to make busy waiting without interrupt*/
		CLEAR_BIT(SYSTICK_BASE_ADDRESS->CTRL,SYSTICK_CTRL_TICKINT);

		/*clear value register to clear flag and reset the register*/
		SYSTICK_BASE_ADDRESS->VAL=0;
	}

	/*execute call back function if it was set*/
	if(SysTick_PtrToFunction!=NULL)
	{
		SysTick_PtrToFunction();
	}
}

/**************************************************************************************************************************************/

