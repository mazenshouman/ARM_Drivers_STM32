/*
 *  File 	   : Keypad.c
 *  Created on : April 11, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_types.h"
#include "Dio_Lcfg.h"
#include "Dio.h"
#include "keypad_Wrapper.h"
#include "keypad_Cfg.h"
#include "keypad.h"
#include "Keypad_Lcfg.h"


/************************************************************************
 *              private structure used to save keypad status            *
 ************************************************************************/

#ifdef KEYPAD_PERIODIC_UPDATE

typedef struct{
	Keypad_StateType					 Keypad_CurrentState;
	Keypad_StateCounterType				 Keypad_StateCounter;
}Keypad_LocalDetailsType;


/************************************************************************
 *                create instance of the local Keypad details           *
 *                               structure                              *
 ************************************************************************/

static Keypad_LocalDetailsType     astr_KeypadDetails[KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS][KEYPAD_NUMBER_OF_ROWS][KEYPAD_NUMBER_OF_COLUMNS];

#endif
/************************************************************************/

/************************************************************************/

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/

/**************************************************************************************************************************************
 *  Function : Keypad_Init                                                                                                            *
 *  Param    : IN     : Name / none                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / none                                                                                                   *
 *                                                                                                                                    *
 *             Output : Name / none                                                                                                   *
 *                                                                                                                                    *
 *  Return   : none                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function initialize the output pins with high value and if the periodic check function is activated then          *
 *             it will init the local array which holds the states of the keys                                                        *                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Keypad_Init(void)
{
	Keypad_ConfigurationStrSizeType u8_localCounterForId=0;
	Keypad_NumberOfPinsType u8_localCounterForRows=0;
#ifdef KEYPAD_PERIODIC_UPDATE
	Keypad_NumberOfPinsType u8_localCounterForColumns=0;
#endif
	/*
	 * set output pins as high as initial value(Rows)
	 * */
	for(u8_localCounterForId=0 ; u8_localCounterForId<KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS ; ++u8_localCounterForId)
	{
		for(u8_localCounterForRows=0 ; u8_localCounterForRows<KEYPAD_NUMBER_OF_ROWS ; ++u8_localCounterForRows)
		{

			Keypad_WriteChannel(gastr_KeypadConfigArr[u8_localCounterForId].Keypad_RowsChannelArr[u8_localCounterForRows],STD_HIGH);
		}
	}

#ifdef KEYPAD_PERIODIC_UPDATE
	/*
	 * initialize the local state array if the periodic configuration parameter is activated
	 * */
	for(u8_localCounterForId=0 ; u8_localCounterForId<KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS ; ++u8_localCounterForId)
	{
		for(u8_localCounterForRows=0 ; u8_localCounterForRows<KEYPAD_NUMBER_OF_ROWS ; ++u8_localCounterForRows)
		{
			for(u8_localCounterForColumns=0 ; u8_localCounterForColumns<KEYPAD_NUMBER_OF_COLUMNS ; ++u8_localCounterForColumns)
			{
				astr_KeypadDetails[u8_localCounterForId][u8_localCounterForRows][u8_localCounterForColumns].Keypad_CurrentState=KEYPAD_RELEASED_STATE;
				astr_KeypadDetails[u8_localCounterForId][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=NUMBER_ZERO;
			}
		}
	}
#endif
}

#ifndef KEYPAD_PERIODIC_UPDATE

/**************************************************************************************************************************************
 *  Function : Keypad_GetKey                                                                                                          *
 *  Param    : IN     : Name / Keypad_Id                                                                                              *
 *                      Type / Keypad_IdType                                                                                          *
 *                      Desc / predefine macro for Keypad id                                                                          *
 *                                                                                                                                    *
 *             Output : Name / data                                                                                                   *
 *                      Type / keypad_OutputDataType*                                                                                 *
 *                      Desc / this pointer is used to return the data corresponding to the pressed key                               *
 *                                                                                                                                    *
 *  Return   : Keypad_ErrorStateType                                                                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return data corresponding to the pressed key if there is key pressed and it                              *
 *             won't block the system if there is no key pressed then this function will return pre-configured                        *
 *             symbol                                                                                                                 *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Keypad_ErrorStateType Keypad_GetKey(Keypad_IdType  Keypad_Id , keypad_OutputDataType* data)
{
	Keypad_ErrorStateType returnState=KEYPAD_E_OK;
	Keypad_NumberOfPinsType u8_localCounterForRows=0;
	Keypad_NumberOfPinsType u8_localCounterForColumns=0;
	if(Keypad_Id>KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS){
		returnState=KEYPAD_ID_OUTOFRANGE;
	}
	else
	{
		if(data==NULL)
		{
			returnState=KEYPAD_NULL_POINTER;
		}
		else
		{
			/*
			 * initialize the return variable with the preconfigured symbol so as if no key is pressed
			 * it will be returned to the caller function
			 * */
			*data=KEYPAD_NO_KEY_IS_PRESSED;

			for(u8_localCounterForRows=0 ; u8_localCounterForRows<KEYPAD_NUMBER_OF_ROWS ; ++u8_localCounterForRows)
			{
				/*
				 * set the each row to low with keeping all other rows as output high
				 * */
				Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_LOW);
				/*
				 * check if any key is pressed by checking all input pins for low value
				 * */
				for(u8_localCounterForColumns=0 ; u8_localCounterForColumns<KEYPAD_NUMBER_OF_COLUMNS ; ++u8_localCounterForColumns)
				{
					if(Keypad_ReadChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_ColumnsChannelArr[u8_localCounterForColumns])==STD_LOW)
					{
						*data=gastr_KeypadConfigArr[Keypad_Id].Keypad_ArrOutputCharacters[u8_localCounterForRows][u8_localCounterForColumns];
						Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_HIGH);
						break;
					}
				}
				Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_HIGH);
			}
		}
	}
	return returnState;
}

/**************************************************************************************************************************************
 *  Function : Keypad_GetKeyAfterRelease                                                                                              *
 *  Param    : IN     : Name / Keypad_Id                                                                                              *
 *                      Type / Keypad_IdType                                                                                          *
 *                      Desc / predefine macro for Keypad id                                                                          *
 *                                                                                                                                    *
 *             Output : Name / data                                                                                                   *
 *                      Type / keypad_OutputDataType*                                                                                 *
 *                      Desc / this pointer is used to return the data corresponding to the pressed key                               *
 *                                                                                                                                    *
 *  Return   : Keypad_ErrorStateType                                                                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return data corresponding to the pressed key if there is key pressed and it                              *
 *             will block the system until the key is released. if there is no key pressed then this function will                    *
 *             return pre-configured symbol                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Keypad_ErrorStateType Keypad_GetKeyAfterRelease(Keypad_IdType  Keypad_Id , keypad_OutputDataType* data)
{
	Keypad_ErrorStateType returnState=KEYPAD_E_OK;
	Keypad_NumberOfPinsType u8_localCounterForRows=0;
	Keypad_NumberOfPinsType u8_localCounterForColumns=0;
	if(Keypad_Id>KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS){
		returnState=KEYPAD_ID_OUTOFRANGE;
	}
	else
	{
		if(data==NULL)
		{
			returnState=KEYPAD_NULL_POINTER;
		}
		else
		{
			/*
			 * initialize the return variable with the preconfigured symbol so as if no key is pressed
			 * it will be returned to the caller function
			 * */
			*data=KEYPAD_NO_KEY_IS_PRESSED;

			for(u8_localCounterForRows=0 ; u8_localCounterForRows<KEYPAD_NUMBER_OF_ROWS ; ++u8_localCounterForRows)
			{
				/*
				 * set the each row to low with keeping all other rows as output high
				 * */
				Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_LOW);
				/*
				 * check if any key is pressed by checking all input pins for low value
				 * */
				for(u8_localCounterForColumns=0 ; u8_localCounterForColumns<KEYPAD_NUMBER_OF_COLUMNS ; ++u8_localCounterForColumns)
				{
					if(Keypad_ReadChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_ColumnsChannelArr[u8_localCounterForColumns])==STD_LOW)
					{
						/*
						 * block the system until the key is released
						 * */
						while(Keypad_ReadChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_ColumnsChannelArr[u8_localCounterForColumns])==STD_LOW);
//						*(uint8*)(0x38)=0xFF;
						*data=gastr_KeypadConfigArr[Keypad_Id].Keypad_ArrOutputCharacters[u8_localCounterForRows][u8_localCounterForColumns];
						Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_HIGH);
						break;
					}
				}
				Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_HIGH);
			}
		}
	}
	return returnState;
}

/*
 * periodic check will need queue so i will implement the queue first and port RTOS to this drivers then and i will implement it

 * */

#else

/**************************************************************************************************************************************
 *  Function : Keypad_CheckKeys                                                                                                       *
 *  Param    : IN     : Name / Keypad_Id                                                                                              *
 *                      Type / Keypad_IdType                                                                                          *
 *                      Desc / predefine macro for Keypad id                                                                          *
 *                                                                                                                                    *
 *             Output : Name / data                                                                                                   *
 *                      Type / keypad_OutputDataType*                                                                                 *
 *                      Desc / this pointer is used to return the data corresponding to the pressed key                               *
 *                                                                                                                                    *
 *  Return   : Keypad_ErrorStateType                                                                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : this function periodically check all keys for any pressed state if there is any key pressed it will be added to        *
 *             the queue of switches pressed and after updating all keys it will return the firsl key on the queue to the caller      *
 *             function if there is no key in the queue the function will return the pre-defined symbol to the caller function        *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Keypad_ErrorStateType Keypad_CheckKeys(Keypad_IdType  Keypad_Id , keypad_OutputDataType* data)
{
	Keypad_ErrorStateType returnState=KEYPAD_E_OK;
	Keypad_NumberOfPinsType u8_localCounterForRows=0;
	Keypad_NumberOfPinsType u8_localCounterForColumns=0;
	Keypad_StateType u8_localCurrentState;

	if(Keypad_Id>KEYPAD_NUMBER_OF_CONFIGURED_KEYPADS || Keypad_Id<NUMBER_ZERO){
		returnState=KEYPAD_ID_OUTOFRANGE;
	}
	else
	{
		if(data==NULL)
		{
			returnState=KEYPAD_NULL_POINTER;
		}
		else
		{
			/*
			 * initialize the return variable with the preconfigured symbol so as if no key is pressed
			 * it will be returned to the caller function
			 * */
			*data=KEYPAD_NO_KEY_IS_PRESSED;

			for(u8_localCounterForRows=0 ; u8_localCounterForRows<KEYPAD_NUMBER_OF_ROWS ; ++u8_localCounterForRows)
			{
				/*
				 * set the each row to low with keeping all other rows as output high
				 * */
				Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_LOW);
				/*
				 * check if any key is pressed by checking all input pins for low value
				 * */
				for(u8_localCounterForColumns=0 ; u8_localCounterForColumns<KEYPAD_NUMBER_OF_COLUMNS ; ++u8_localCounterForColumns)
				{
					/*check the current state of the switch if it was pressed or not*/
					if(Keypad_ReadChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_ColumnsChannelArr[u8_localCounterForColumns])==STD_LOW)
					{
						u8_localCurrentState=KEYPAD_PRESSED_STATE;
					}
					else
					{
						u8_localCurrentState=KEYPAD_RELEASED_STATE;
					}
					/*switch on the current state of the key from the local details array*/
					switch(astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_CurrentState)
					{
						case KEYPAD_RELEASED_STATE:
							/*if the push button detected as pressed*/
							if(u8_localCurrentState==KEYPAD_PRESSED_STATE)
							{
								/*increase counter*/
								++astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter;
								/*check if the counter reached the number of counts needed to move to the next state*/
								if(astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter>=KEYPAD_COUNTER_VALUE)
								{
									/*
									 * if there is function to be executed for the next state lunch it
									 * */
									/*depending on the wanted action to be happen we can add this button to the queue of the characters*/
									/*
									 * then change the current state to the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_CurrentState = KEYPAD_PRE_PRESSED_STATE;
									/*
									 *reset the counter of the state to start from zero for the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
								}
							}
							/*
							 * if the pushbutton state was released then start from beginning for this state
							 * */
							else
							{
								astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
							}
							break;
						case KEYPAD_PRE_PRESSED_STATE:
							/*if the push button detected as pressed*/
							if(u8_localCurrentState==KEYPAD_PRESSED_STATE)
							{
								/*increase counter*/
								++astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter;
								/*check if the counter reached the number of counts needed to move to the next state*/
								if(astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter>=KEYPAD_COUNTER_VALUE)
								{
									/*return the first key which reaches to the pressed state*/

									if(data==KEYPAD_NO_KEY_IS_PRESSED)
									{
										*data=gastr_KeypadConfigArr[Keypad_Id].Keypad_ArrOutputCharacters[u8_localCounterForRows][u8_localCounterForColumns];
									}
									/*
									 * then change the current state to the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_CurrentState = KEYPAD_PRESSED_STATE;
									/*
									 *reset the counter of the state to start from zero for the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
								}
							}
							/*
							 * if the pushbutton state was released then start from beginning for this state
							 * */
							else
							{
								astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
							}
							break;
						case KEYPAD_PRESSED_STATE:
							/*if the push button detected as Released*/
							if(u8_localCurrentState==KEYPAD_RELEASED_STATE)
							{
								/*increase counter*/
								++astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter;
								/*check if the counter reached the number of counts needed to move to the next state*/
								if(astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter>=KEYPAD_COUNTER_VALUE)
								{

									/*
									 * then change the current state to the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_CurrentState = KEYPAD_PRE_RELEASED_STATE;
									/*
									 *reset the counter of the state to start from zero for the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
								}
							}
							/*
							 * if the pushbutton state was released then start from beginning for this state
							 * */
							else
							{
								astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
							}
							break;
						case KEYPAD_PRE_RELEASED_STATE:
							/*if the push button detected as Released*/
							if(u8_localCurrentState==KEYPAD_RELEASED_STATE)
							{
								/*increase counter*/
								++astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter;
								/*check if the counter reached the number of counts needed to move to the next state*/
								if(astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter>=KEYPAD_COUNTER_VALUE)
								{

									/*
									 * then change the current state to the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_CurrentState = KEYPAD_RELEASED_STATE;
									/*
									 *reset the counter of the state to start from zero for the next state
									 * */
									astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
								}
							}
							/*
							 * if the pushbutton state was released then start from beginning for this state
							 * */
							else
							{
								astr_KeypadDetails[Keypad_Id][u8_localCounterForRows][u8_localCounterForColumns].Keypad_StateCounter=0;
							}
							break;
						default:
							/*no error can be happened here*/
							break;

					}
				}
				Keypad_WriteChannel(gastr_KeypadConfigArr[Keypad_Id].Keypad_RowsChannelArr[u8_localCounterForRows],STD_HIGH);
			}
		}
	}
	return returnState;
}

#endif
