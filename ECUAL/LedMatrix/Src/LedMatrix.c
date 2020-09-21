/*
 *  File 	   : Keypad.c
 *  Created on : Sep 20, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_types.h"
#include "Bit_Math.h"
#include "Dio_Lcfg.h"
#include "Dio.h"
#include "SysTick.h"
#include "LedMatrix_Wrapper.h"
#include "LedMatrix_Cfg.h"
#include "LedMatrix.h"
#include "LedMatrix_Lcfg.h"

/************************************************************************
 *                           Macros&Types                               *
 ************************************************************************/


/************************************************************************
 *                           Gloabal Variables                          *
 ************************************************************************/

static LedMatrix_NumberOfTicks_t LedMatrix_NumberOfTicks=0;

/*arr of characters*/
/*added const to place it in the flash memory
 * in other micro you have to make sure that this array placed in flash*/

/*this array is configured as LSB at top and column controlled*/
const uint8 LedMatrix_characterArray[LEDMATRIX_SIZE_OF_DATA_ARRAY][LEDMATRIX_NUMBER_OF_ROWS]=
{
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x7E, 0x06, 0x0C, 0x0C, 0x06, 0x7E, 0x00},
		{0x00, 0x7C, 0x12, 0x12, 0x12, 0x12, 0x7C, 0x00},
		{0x00, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00},
		{0x00, 0x7F, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00},
		{0x00, 0x7E, 0x06, 0x0C, 0x18, 0x30, 0x7E, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};



/************************************************************************/

/************************************************************************/

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/

/**************************************************************************************************************************************
 *  Function : LedMatrix_Init                                                                                                         *
 *  Param    : IN     : Name / none                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / none                                                                                                   *
 *                                                                                                                                    *
 *             Output : Name / none                                                                                                   *
 *                                                                                                                                    *
 *  Return   : none                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function initialize initialize the timer if it was configured to be controlled using it and set all columns       *
 *             pins to there default state                                                                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void LedMatrix_Init(void)
{

	LedMatrix_ConfigurationStrSize_t local_loopCounter=0;
	uint8 local_idelLevelValue=0;
	LedMatrix_NumberOfPins_t local_pinCounter=0;

	/*loop on the configuration array*/
	for(local_loopCounter=0 ; local_loopCounter<LEDMATRIX_NUMBER_OF_CONFIGURED_MODULES ; local_loopCounter++)
	{
		/*switch on the common row type value */
		/*if it was common row anode*/
		if(gastr_LedMatrixConfigArr[local_loopCounter].LedMatrix_CommonRowType==LEDMATRIX_COMMON_ROW_ANODE)
		{
			/*set all column pins to HIGH*/
			local_idelLevelValue=STD_HIGH;
		}
		/*else if it was common row cathode*/
		else if(gastr_LedMatrixConfigArr[local_loopCounter].LedMatrix_CommonRowType==LEDMATRIX_COMMON_ROW_CATHODE)
		{
			/*set all column pins to low*/
			local_idelLevelValue=STD_LOW;
		}
		else
		{
			/*report error*/
		}

		/*loop on all columns and set them to the default value*/
		for(local_pinCounter=0 ; local_pinCounter<LEDMATRIX_NUMBER_OF_COLUMNS ; local_pinCounter++)
		{
			LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[local_loopCounter].LedMatrix_ColumnsChannelArr[local_pinCounter] , local_idelLevelValue);
		}

	}

	/*check LEDMATRIX_TIMING_SYSTEM macro if it was configured as timer then we have to set timing in global variabel
	 * so that we can make timer wait on it in case of synch function
	 * for asych user must set the call back function and the timing requirement in the application
	 */
#if LEDMATRIX_TIMING_SYSTEM==LEDMATRIX_TIMING_USING_TIMER

	/*number of ticks needed = (wanted time)/(1/freq)*/

	/*wanted time for each row = (total time for all frames (1s)/(number of row * nubmber of frames in sec)*/

	LedMatrix_NumberOfTicks=1000000/((LedMatrix_NumberOfTicks_t)(LEDMATRIX_NUMBER_OF_FRAMES_PER_SECOND*LEDMATRIX_NUMBER_OF_COLUMNS));

	/*number of ticks = wanted time in microsec/ticktime */
	/*not used yet*/

	/*init timer*/
	LedMatrix_TimerInit();
#endif
}

/**************************************************************************************************************************************
 *  Function : LedMatrix_DisplayCharSynch                                                                                             *
 *  Param    : IN     : Name / LedMatrix_Id                                                                                           *
 *                      Type / LedMatrix_Id_t                                                                                         *
 *                      Desc / predefine macro for LedMatrix id                                                                       *
 *                                                                                                                                    *
 *                      Name / dataIndex                                                                                              *
 *                      Type / LedMatrix_data_t                                                                                       *
 *                      Desc / takes the character wanted to be displayed on led matrix from the predefined array                     *
 *                                                                                                                                    *
 *                      Name / TimeInMs                                                                                               *
 *                      Type / LedMatrix_timeInMs_t                                                                                   *
 *                      Desc / takes the time which the character will be displayed for and time must be higher than                  *
 *                             character time                                                                                         *
 *                                                                                                                                    *
 *  Return   : LedMatrix_ErrorState_t                                                                                                 *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used to display character for specific time then it will disappear by displaying column by               *
 *             column using the predefine rate in the cfg file and it's synchronous function                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

LedMatrix_ErrorState_t LedMatrix_DisplayCharSynch(LedMatrix_Id_t  LedMatrix_Id , LedMatrix_dataIndex_t dataIndex , LedMatrix_timeInMs_t TimeInMs)
{
	LedMatrix_ErrorState_t returnValue=LEDMATRIX_E_OK;
	LedMatrix_NumberOfPins_t local_columnsCounter=0;
	LedMatrix_NumberOfPins_t local_rowsCounter=0;
	uint16 local_TimeLoopCounter=0;
	LedMatrix_CommonRowType_t local_CommonRowType=LEDMATRIX_COMMON_ROW_ANODE;
	uint8 local_OnValue=STD_HIGH;
	uint8 local_OffValue=STD_LOW;

	/*check Id*/
	if(LedMatrix_Id>LEDMATRIX_NUMBER_OF_CONFIGURED_MODULES)
	{
		returnValue=LEDMATRIX_E_NOT_OK;
	}
	else
	{

		/*calculating the number of loop to achieve the wanted time*/
		local_TimeLoopCounter=TimeInMs/(LEDMATRIX_NUMBER_OF_COLUMNS*LedMatrix_NumberOfTicks);

		/*this value is used in flipping the array values if the rows are common cathode  */
		local_CommonRowType=gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_CommonRowType;

		/*these values is used to turn on/off the column depending on common row type*/
		local_OnValue=local_CommonRowType;
		local_OffValue=!local_CommonRowType;

		for( ; local_TimeLoopCounter>0 ; local_TimeLoopCounter--)
		{
			/*loop on the columns */
			for(local_columnsCounter=0 ; local_columnsCounter<LEDMATRIX_NUMBER_OF_COLUMNS ; local_columnsCounter++)
			{
				/*set data on all row pins*/
				for(local_rowsCounter=0 ; local_rowsCounter<LEDMATRIX_NUMBER_OF_ROWS;local_rowsCounter++)
				{
					/*this line gets the current row of value and then set all of it's bits to the row pins*/
					/*XOR with local_CommonRowType to flip the values of the array if the rows were common cathode as main array in common row anode */
					LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_RowsChannelArr[local_rowsCounter] , (GET_BIT(LedMatrix_characterArray[dataIndex][local_columnsCounter] , local_rowsCounter)^local_CommonRowType));
				}

				/*enable column*/
				/*depending on the value common row type enable the column*/
				LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_OnValue);

				/*wait for the predefined time in the global variable */
				LedMatrix_SetBusyWaitInTicks(LedMatrix_NumberOfTicks);

				/*disable the column*/
				LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_OffValue);
			}
		}
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : LedMatrix_DisplayTextSynch                                                                                             *
 *  Param    : IN     : Name / LedMatrix_Id                                                                                           *
 *                      Type / LedMatrix_Id_t                                                                                         *
 *                      Desc / predefine macro for LedMatrix id                                                                       *
 *                                                                                                                                    *
 *                      Name / dataIndex                                                                                              *
 *                      Type / LedMatrix_data_t                                                                                       *
 *                      Desc / takes starting index of the text wanted to be displayed on led matrix                                  *
 *                                                                                                                                    *
 *                      Name / ShiftingTimeInMs                                                                                       *
 *                      Type / LedMatrix_timeInMs_t                                                                                   *
 *                      Desc / takes the time which the character will be shifted after , and time must be higher than                *
 *                              character display time                                                                                *
 *                                                                                                                                    *
 *  Return   : LedMatrix_ErrorState_t                                                                                                 *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used to display predefined array of character from any position of the array and with specific           *
 *             time for shifting                                                                                                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

LedMatrix_ErrorState_t LedMatrix_DisplayTextSynch(LedMatrix_Id_t  LedMatrix_Id , LedMatrix_dataIndex_t dataIndex , LedMatrix_timeInMs_t ShiftingTimeInMs)
{
	LedMatrix_ErrorState_t returnValue=LEDMATRIX_E_OK;
	LedMatrix_NumberOfPins_t local_columnsCounter=0;
	LedMatrix_NumberOfPins_t local_rowsCounter=0;
	uint16 local_TimeValue=0;
	uint16 local_TimeLoopCounter=0;
	LedMatrix_CommonRowType_t local_CommonRowType=LEDMATRIX_COMMON_ROW_ANODE;
	uint8 local_OnValue=STD_HIGH;
	uint8 local_OffValue=STD_LOW;
	uint8 characterShiftsCounter=0;
	/*pointer to the first element of the data array*/
	uint8 *dataPtr=(uint8*)LedMatrix_characterArray[dataIndex];

	/*check Id*/
	if(LedMatrix_Id>LEDMATRIX_NUMBER_OF_CONFIGURED_MODULES)
	{
		returnValue=LEDMATRIX_E_NOT_OK;
	}
	else
	{
		/*calculating the number of loop to achieve the wanted time*/
		local_TimeValue=ShiftingTimeInMs/(LEDMATRIX_NUMBER_OF_COLUMNS*LedMatrix_NumberOfTicks);

		/*this value is used in flipping the array values if the rows are common cathode  */
		local_CommonRowType=gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_CommonRowType;

		/*these values is used to turn on/off the column depending on common row type*/
		local_OnValue=local_CommonRowType;
		local_OffValue=!local_CommonRowType;

		/*this counter used to determine how many shifts needed to display all text*/
		characterShiftsCounter=(LEDMATRIX_SIZE_OF_DATA_ARRAY-1)*LEDMATRIX_NUMBER_OF_COLUMNS;

		for( ; characterShiftsCounter>0 ; characterShiftsCounter--)
		{
			for(local_TimeLoopCounter=0 ; local_TimeLoopCounter<local_TimeValue ; local_TimeLoopCounter++)
			{
				/*loop on the columns */
				for(local_columnsCounter=0 ; local_columnsCounter<LEDMATRIX_NUMBER_OF_COLUMNS ; local_columnsCounter++)
				{
					/*set data on all row pins*/
					for(local_rowsCounter=0 ; local_rowsCounter<LEDMATRIX_NUMBER_OF_ROWS;local_rowsCounter++)
					{
						/*this line gets the current row of value and then set all of it's bits to the row pins*/
						/*XOR with local_CommonRowType to flip the values of the array if the rows were common cathode as main array in common row anode */
						LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_RowsChannelArr[local_rowsCounter] , (GET_BIT(dataPtr[local_columnsCounter] , local_rowsCounter)^local_CommonRowType));
					}

					/*enable column*/
					/*depending on the value common row type enable the column*/
					LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_OnValue);

					/*wait for the predefined time in the global variable */
					LedMatrix_SetBusyWaitInTicks(LedMatrix_NumberOfTicks);

					/*disable the column*/
					LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_OffValue);
				}
			}
			dataPtr++;
		}
	}

	return returnValue;
}
///**************************************************************************************************************************************
// *  Function : LedMatrix_DisplayCharAsynch                                                                                            *
// *  Param    : IN     : Name / LedMatrix_Id                                                                                           *
// *                      Type / LedMatrix_Id_t                                                                                         *
// *                      Desc / predefine macro for LedMatrix id                                                                       *
// *                                                                                                                                    *
// *             Output : Name / data                                                                                                   *
// *                      Type / LedMatrix_data_t                                                                                       *
// *                      Desc / takes the character wanted to be dispalyed on led matrix                                               *
// *                                                                                                                                    *
// *  Return   : LedMatrix_CurrentState_t                                                                                               *
// *                                                                                                                                    *
// *                                                                                                                                    *
// *  Desc     : This function used to display character on the led matrix by displaying column by column using the                     *
// *             predefine rate in the cfg file by using state machine so that it won't block the system and user must sit it           *
// *             as call bakck funtion in the timer                                                                                     *
// *                                                                                                                                    *
// *                                                                                                                                    *
// *                                                                                                                                    *
// *************************************************************************************************************************************/
//
//LedMatrix_CurrentState_t LedMatrix_DisplayCharAsynch(LedMatrix_Id_t  LedMatrix_Id , LedMatrix_data_t data)
//{
//	LedMatrix_CurrentState_t returnValue=LEDMATRIX_STATE_NOT_FINISHED;
//
//
//	return returnValue;
//}



