/*
 *  File 	   : Pushbutton.c
 *  Created on : April 9, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_types.h"
#include "Dio.h"
#include "Dio_Lcfg.h"
#include "Pushbutton_Wrapper.h"
#include "Pushbutton_Cfg.h"
#include "Pushbutton.h"
#include "Pushbutton_Lcfg.h"

/************************************************************************
 *              private structure used to save Pushbutton status        *
 *                  and their callback functions                        *
 ************************************************************************/

#ifdef PUSHBUTTON_PERIODIC_UPDATE
typedef struct{
	Pushbutton_StateType					 Pushbutton_CurrentState;
	Pushbutton_StateCounterType				 Pushbutton_StateCounter;
	Pushbutton_PtrToFunctionType			 PushButton_ArrPtrToFunction[PUSHBUTTON_NUMBER_OF_STATES];
}PushButton_LocalButtonDetailsType;


/************************************************************************
 *                create instance of the local button details           *
 *                               structure                              *
 ************************************************************************/

static PushButton_LocalButtonDetailsType     astr_PushbuttonDetails[PUSHBUTTON_NUMBER_OF_CONFIGURED_BUTTONS];
#endif
/************************************************************************/

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/

#ifndef PUSHBUTTON_PERIODIC_UPDATE

/**************************************************************************************************************************************
 *  Function : PushButton_ReadButtonLevel                                                                                             *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for PushButton id                                                                      *
 *                                                                                                                                    *
 *             Output : Name / State                                                                                                  *
 *                      Type / Pushbutton_StateType*                                                                                  *
 *                      Desc / this pointer is used to return state to the caller function through pointer (pressed or released)      *
 *                                                                                                                                    *
 *  Return   : Pushbutton_ErrorStateType                                                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function reads the current level of the button and return the obtained level(used in                              *
 *             one time get value not on periodic matter) return only two states (pressed or released)                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Pushbutton_ErrorStateType Pushbutton_ReadButtonState(Pushbutton_IdType Pushbutton_Id , Pushbutton_StateType* State)
{

	Pushbutton_ErrorStateType    returnErrorState=PUSHBUTTON_E_OK;

	/*
	 * check the pointer for null pointer error
	 * */

	if(State == NULL)
	{
		returnErrorState=PUSHBUTTON_NULL_POINTER;
	}
	else
	{
		/*
		 * check if the pushButton ID is out of the limit or not
		 * */

		if(Pushbutton_Id >= PUSHBUTTON_NUMBER_OF_CONFIGURED_BUTTONS)
		{
			returnErrorState = PUSHBUTTON_ID_OUTOFRANGE;
		}
		else
		{
			/*
			 * read the active type of the pushbutton
			 * */
			switch(gastr_PushbuttonConfigArr[Pushbutton_Id].Pushbutton_ActiveState)
			{
				/*
				 * return the state of the pushbutton
				 *
				 * */
				case PUSHBUTTON_ACTIVE_LOW:
					if(Pushbutton_ReadChannel(gastr_PushbuttonConfigArr[Pushbutton_Id].Pushbutton_Channel)==STD_LOW)
					{
						*State=PUSHBUTTON_PRESSED_STATE;
					}
					else
					{
						*State=PUSHBUTTON_RELEASED_STATE;
					}
					break;
				case PUSHBUTTON_ACTIVE_HIGH:
					if(Pushbutton_ReadChannel(gastr_PushbuttonConfigArr[Pushbutton_Id].Pushbutton_Channel)==STD_HIGH)
					{
						*State=PUSHBUTTON_PRESSED_STATE;
					}
					else
					{
						*State=PUSHBUTTON_RELEASED_STATE;
					}
					break;
				default:
					returnErrorState= PUSHBUTTON_ACTIVE_TYPE_IS_NOT_DEFINED;
			}
		}
	}
	return returnErrorState;
}

#else

/**************************************************************************************************************************************
 *  Function : Pushbutton_Init                                                                                                        *
 *  Param    : IN     : Name / none                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / none                                                                                                   *
 *                                                                                                                                    *
 *             Output : Name / none                                                                                                   *
 *                                                                                                                                    *
 *  Return   : none                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function initialize the local structure used to store details for each switch used with periodic                  *
 *             update configuration                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Pushbutton_Init(void)
{
	/*
	 * initialize the local structure with the initial values
	 * */
	Pushbutton_ConfigurationStrSizeType u8_LocalCounter=0;
	uint8 u8_LocalCounterForStates=0;


	for(u8_LocalCounter=0 ; u8_LocalCounter<PUSHBUTTON_NUMBER_OF_CONFIGURED_BUTTONS ; ++u8_LocalCounter)
	{
		astr_PushbuttonDetails[u8_LocalCounter].Pushbutton_CurrentState=PUSHBUTTON_RELEASED_STATE;
		astr_PushbuttonDetails[u8_LocalCounter].Pushbutton_StateCounter=NUMBER_ZERO;
		for(u8_LocalCounterForStates=0 ; u8_LocalCounterForStates<PUSHBUTTON_NUMBER_OF_STATES ; ++u8_LocalCounterForStates)
		{
			astr_PushbuttonDetails[u8_LocalCounter].PushButton_ArrPtrToFunction[u8_LocalCounterForStates]=NULL;
		}
	}
}

/**************************************************************************************************************************************
 *  Function : PushButton_GetCurrentState                                                                                             *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for PushButton id                                                                      *
 *                                                                                                                                    *
 *             Output : Name / State                                                                                                  *
 *                      Type / Pushbutton_StateType*                                                                                  *
 *                      Desc / this pointer is used to return current state to the caller function through pointer                    *
 *                                                                                                                                    *
 *  Return   : Pushbutton_ErrorStateType                                                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the current state for the selected Push Button used in periodic check systems                     *
 *             returns on of the four states of the switch                                                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Pushbutton_ErrorStateType Pushbutton_GetCurrentState(Pushbutton_IdType Pushbutton_Id , Pushbutton_StateType* State)
{
	Pushbutton_ErrorStateType    returnErrorState=PUSHBUTTON_E_OK;

	/*
	 * check the pointer for null pointer error
	 * */

	if(State == NULL)
	{
		returnErrorState=PUSHBUTTON_NULL_POINTER;
	}
	else
	{
		/*
		 * check if the pushButton ID is out of the limit or not
		 * */

		if(Pushbutton_Id >= PUSHBUTTON_NUMBER_OF_CONFIGURED_BUTTONS)
		{
			returnErrorState = PUSHBUTTON_ID_OUTOFRANGE;
		}

		/*
		 * return the current state from the local arr of str
		 * */

		*State=astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_CurrentState;
	}
	return returnErrorState;
}


/**************************************************************************************************************************************
 *  Function : Pushbutton_GetCurrentState                                                                                             *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for PushButton id                                                                      *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Pushbutton_ErrorStateType                                                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used with periodic calls to update the state of certain switch                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Pushbutton_ErrorStateType Pushbutton_UpdateState(Pushbutton_IdType Pushbutton_Id)
{
	Pushbutton_ErrorStateType    returnErrorState=PUSHBUTTON_E_OK;
	Pushbutton_ConfigurationStrSizeType u8_LocalCounter=0;
	Pushbutton_StateType u8_localCurrentState;

	/*
	 * check if the pushButton ID is out of the limit or not
	 * */

	if(Pushbutton_Id >= PUSHBUTTON_NUMBER_OF_CONFIGURED_BUTTONS)
	{
		returnErrorState = PUSHBUTTON_ID_OUTOFRANGE;
	}
	else
	{
		/*loop on all switches and check their:
		 * 1-Active Type to determine state
		 * 2-read the current state from the Dio Pin
		 * 3-update the counter or move to the next state
		 * */
		for(u8_LocalCounter=0 ; u8_LocalCounter<PUSHBUTTON_NUMBER_OF_CONFIGURED_BUTTONS ; ++u8_LocalCounter)
		{
			switch(gastr_PushbuttonConfigArr[Pushbutton_Id].Pushbutton_ActiveState)
			{
				/*
				 * depending on the active type of the switch get the state of it from two states (pressed/notpressed)
				 * save it to local variable as it will be used in the next switch case to determine the action to
				 * be taken (move to the next state or continue on the current state)
				 * */
				case PUSHBUTTON_ACTIVE_LOW:
					if(Pushbutton_ReadChannel(gastr_PushbuttonConfigArr[Pushbutton_Id].Pushbutton_Channel)==STD_LOW)
					{
						u8_localCurrentState=PUSHBUTTON_PRESSED_STATE;
					}
					else
					{
						u8_localCurrentState=PUSHBUTTON_RELEASED_STATE;
					}
					break;
				case PUSHBUTTON_ACTIVE_HIGH:
					if(Pushbutton_ReadChannel(gastr_PushbuttonConfigArr[Pushbutton_Id].Pushbutton_Channel)==STD_HIGH)
					{
						u8_localCurrentState=PUSHBUTTON_PRESSED_STATE;
					}
					else
					{
						u8_localCurrentState=PUSHBUTTON_RELEASED_STATE;
					}
					break;
				default:
					returnErrorState= PUSHBUTTON_ACTIVE_TYPE_IS_NOT_DEFINED;
			}
			/*
			 * if there is no error
			 * */
			if(returnErrorState==PUSHBUTTON_E_OK)
			{
				/*
				 * check the current state to update it
				 * */
				switch(astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_CurrentState)
				{
					case PUSHBUTTON_RELEASED_STATE:
						/*if the push button detected as pressed*/
						if(u8_localCurrentState==PUSHBUTTON_PRESSED_STATE)
						{
							/*increase counter*/
							++astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter;
							/*check if the counter reached the number of counts needed to move to the next state*/
							if(astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter>=PUSHBUTTON_COUNTER_VALUE)
							{
								/*
								 * if there is function to be executed for the next state lunch it
								 * */
								if(astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_PRE_PRESSED_STATE]!=NULL)
								{
									astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_PRE_PRESSED_STATE]();
								}
								/*
								 * then change the current state to the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_CurrentState = PUSHBUTTON_PRE_PRESSED_STATE;
								/*
								 *reset the counter of the state to start from zero for the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
							}
						}
						/*
						 * if the pushbutton state was released then start from beginning for this state
						 * */
						else
						{
							astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
						}
						break;
					case PUSHBUTTON_PRE_PRESSED_STATE:
						/*if the push button detected as pressed*/
						if(u8_localCurrentState==PUSHBUTTON_PRESSED_STATE)
						{
							/*increase counter*/
							++astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter;
							/*check if the counter reached the number of counts needed to move to the next state*/
							if(astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter>=PUSHBUTTON_COUNTER_VALUE)
							{
								/*
								 * if there is function to be executed here lunch it
								 * */
								if(astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_PRESSED_STATE]!=NULL)
								{
									astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_PRESSED_STATE]();
								}
								/*
								 * then change the current state to the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_CurrentState = PUSHBUTTON_PRESSED_STATE;
								/*
								 *reset the counter of the state to start from zero for the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
							}
						}
						/*
						 * if the pushbutton state was released then start from beginning for this state
						 * */
						else
						{
							astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
						}
						break;
					case PUSHBUTTON_PRESSED_STATE:
						/*if the push button detected as Released*/
						if(u8_localCurrentState==PUSHBUTTON_RELEASED_STATE)
						{
							/*increase counter*/
							++astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter;
							/*check if the counter reached the number of counts needed to move to the next state*/
							if(astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter>=PUSHBUTTON_COUNTER_VALUE)
							{
								/*
								 * if there is function to be executed here lunch it
								 * */
								if(astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_PRE_RELEASED_STATE]!=NULL)
								{
									/*the function must be as small as possible for performance and accuracy wise*/
									astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_PRE_RELEASED_STATE]();
								}
								/*
								 * then change the current state to the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_CurrentState = PUSHBUTTON_PRE_RELEASED_STATE;
								/*
								 *reset the counter of the state to start from zero for the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
							}
						}
						/*
						 * if the pushbutton state was released then start from beginning for this state
						 * */
						else
						{
							astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
						}
						break;
					case PUSHBUTTON_PRE_RELEASED_STATE:
						/*if the push button detected as Released*/
						if(u8_localCurrentState==PUSHBUTTON_RELEASED_STATE)
						{
							/*increase counter*/
							++astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter;
							/*check if the counter reached the number of counts needed to move to the next state*/
							if(astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter>=PUSHBUTTON_COUNTER_VALUE)
							{
								/*
								 * if there is function to be executed here lunch it
								 * */
								if(astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_RELEASED_STATE]!=NULL)
								{
									/*the function must be as small as possible for performance and accuracy wise*/
									astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[PUSHBUTTON_RELEASED_STATE]();
								}
								/*
								 * then change the current state to the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_CurrentState = PUSHBUTTON_RELEASED_STATE;
								/*
								 *reset the counter of the state to start from zero for the next state
								 * */
								astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
							}
						}
						/*
						 * if the pushbutton state was released then start from beginning for this state
						 * */
						else
						{
							astr_PushbuttonDetails[Pushbutton_Id].Pushbutton_StateCounter=0;
						}
						break;
					default:
						/*no error can be happened here*/
						break;
				}
			}
		}

	}
	return returnErrorState;
}

/**************************************************************************************************************************************
 *  Function : Pushbutton_SetCallBackFunction                                                                                         *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for PushButton id                                                                      *
 *                                                                                                                                    *
 *                      Name / PtrToFunction                                                                                          *
 *                      Type / Pushbutton_StateCounterType                                                                           *
 *                      Desc / takes Pointer to function which wanted to be executed when certain state is reached                    *
 *                                                                                                                                    *
 *                      Name / State                                                                                                  *
 *                      Type / Pushbutton_StateType                                                                                   *
 *                      Desc / predefine macro for PushButton state                                                                   *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Pushbutton_ErrorStateType                                                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used with periodic calls to set callback functions for PushButton for certain state                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Pushbutton_ErrorStateType Pushbutton_SetCallBackFunction(Pushbutton_IdType Pushbutton_Id , Pushbutton_PtrToFunctionType PtrToFunction  , Pushbutton_StateType  State)
{
	Pushbutton_ErrorStateType    returnErrorState=PUSHBUTTON_E_OK;

	/*
	 * check the pointer for null pointer error
	 * */

	if(PtrToFunction==NULL)
	{
		returnErrorState=PUSHBUTTON_NULL_POINTER;
	}
	else
	{
		/*
		 * check if the pushButton ID is out of the limit or not
		 * */

		if(Pushbutton_Id >= PUSHBUTTON_NUMBER_OF_CONFIGURED_BUTTONS)
		{
			returnErrorState = PUSHBUTTON_ID_OUTOFRANGE;
		}
		else
		{
			/*
			 * check the given state if it was in range or undefined
			 * */
			if(State<PUSHBUTTON_RELEASED_STATE || State>=PUSHBUTTON_NUMBER_OF_STATES)
			{
				returnErrorState=PUSHBUTTON_UNDEFINED_STATE;
			}
			else
			{
				/*
				 * add pointer to function to the array
				 * */
				astr_PushbuttonDetails[Pushbutton_Id].PushButton_ArrPtrToFunction[State]=PtrToFunction;
			}
		}
	}
	return returnErrorState;
}

#endif
