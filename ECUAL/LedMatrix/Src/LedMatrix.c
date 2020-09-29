/*
 *  File 	   : Keypad.c
 *  Created on : Sep 21, 2020
 *  Author	   : Mazen Shouman
 *  Version    :2.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_types.h"
#include "Bit_Math.h"
#include "Dio.h"
#include "SysTick.h"
#include "LedMatrix_Wrapper.h"
#include "LedMatrix_Cfg.h"
#include "LedMatrix.h"
#include "LedMatrix_Lcfg.h"

/************************************************************************
 *                           Macros&Types                               *
 ************************************************************************/
#define LEDMATRIX_ONE_CHARACTER                                         1
#define LEDMATRIX_NUMBER_OF_UNUSED_CHAR                                 32
/************************************************************************
 *                           Gloabal Variables                          *
 ************************************************************************/

static LedMatrix_NumberOfTicks_t LedMatrix_NumberOfTicks=0;

/*arr of characters*/
/*added const to place it in the flash memory
 * in other micro you have to make sure that this array placed in flash*/

/*this array is configured as LSB at top and column controlled*/
/*uint8 must be changed depending on the number of rows in the led matrix*/
const uint8 LedMatrix_characterArray[LEDMATRIX_SIZE_OF_DATA_ARRAY][LEDMATRIX_NUMBER_OF_COLUMNS]=
{
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x7E, 0x06, 0x0C, 0x0C, 0x06, 0x7E, 0x00},
		{0x00, 0x7C, 0x12, 0x12, 0x12, 0x12, 0x7C, 0x00},
		{0x00, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00},
		{0x00, 0x7F, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00},
		{0x00, 0x7E, 0x06, 0x0C, 0x18, 0x30, 0x7E, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const uint8 LedMatrix_CharacterAsciiArray[][LEDMATRIX_NUMBER_OF_COLUMNS]=
{
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},/*space*/
		{0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00, 0x00},/*!*/
		{0x00, 0x00, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x00},/*"*/
		{0x00, 0x24, 0x7E, 0x24, 0x24, 0x7E, 0x24, 0x00},/*#*/
		{0x00, 0x46, 0x4A, 0xFF, 0x52, 0x62, 0x00, 0x00},/*$*/
		{0x00, 0x46, 0x26, 0x10, 0x08, 0x64, 0x62, 0x00},/*%*/
		{0x00, 0x00, 0x26, 0x59, 0x59, 0x26, 0x50, 0x00},/*&*/
		{0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00},/*'*/
		{0x00, 0x00, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00},/*(*/
		{0x00, 0x00, 0x00, 0x42, 0x24, 0x18, 0x00, 0x00},/*)*/
		{0x00, 0x00, 0x00, 0x14, 0x0E, 0x14, 0x00, 0x00},/***/
		{0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, 0x00},/*+*/
		{0x00, 0x00, 0x00, 0x40, 0x30, 0x00, 0x00, 0x00},/*,*/
		{0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00},/*-*/
		{0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00},/*.*/
		{0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00},/*/*/
		{0x00, 0x00, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x00},/*0*/
		{0x00, 0x00, 0x00, 0x44, 0x7E, 0x40, 0x00, 0x00},/*1*/
		{0x00, 0x00, 0x64, 0x52, 0x52, 0x4C, 0x00, 0x00},/*2*/
		{0x00, 0x00, 0x22, 0x49, 0x49, 0x36, 0x00, 0x00},/*3*/
		{0x00, 0x00, 0x30, 0x28, 0x24, 0x7E, 0x20, 0x00},/*4*/
		{0x00, 0x00, 0x4E, 0x4A, 0x4A, 0x32, 0x00, 0x00},/*5*/
		{0x00, 0x00, 0x7F, 0x49, 0x49, 0x79, 0x00, 0x00},/*6*/
		{0x00, 0x00, 0x09, 0x09, 0x09, 0x7F, 0x00, 0x00},/*7*/
		{0x00, 0x00, 0x3E, 0x49, 0x49, 0x3E, 0x00, 0x00},/*8*/
		{0x00, 0x00, 0x2E, 0x49, 0x49, 0x3E, 0x00, 0x00},/*9*/
		{0x00, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00},/*:*/
		{0x00, 0x00, 0x00, 0x46, 0x36, 0x00, 0x00, 0x00},/*;*/
		{0x00, 0x00, 0x10, 0x28, 0x44, 0x82, 0x00, 0x00},/*<*/
		{0x00, 0x00, 0x28, 0x28, 0x28, 0x28, 0x00, 0x00},/*=*/
		{0x00, 0x00, 0x82, 0x44, 0x28, 0x10, 0x00, 0x00},/*>*/
		{0x00, 0x00, 0x04, 0x02, 0xB2, 0x0C, 0x00, 0x00},/*?*/
		{0x00, 0x1E, 0x21, 0x4D, 0x53, 0x5F, 0x20, 0x10},/*@*/
		{0x00, 0x7C, 0x12, 0x11, 0x11, 0x12, 0x7C, 0x00},/*A*/
		{0x00, 0x00, 0x7F, 0x49, 0x49, 0x49, 0x76, 0x00},/*B*/
		{0x00, 0x1C, 0x22, 0x41, 0x41, 0x41, 0x41, 0x00},/*C*/
		{0x00, 0x7F, 0x41, 0x41, 0x41, 0x22, 0x1C, 0x00},/*D*/
		{0x00, 0x00, 0x7F, 0x49, 0x49, 0x49, 0x00, 0x00},/*E*/
		{0x00, 0x00, 0x7F, 0x09, 0x09, 0x09, 0x00, 0x00},/*F*/
		{0x00, 0x1E, 0x21, 0xC0, 0xC8, 0x49, 0x7A, 0x00},/*G*/
		{0x00, 0x7F, 0x08, 0x08, 0x08, 0x08, 0x7F, 0x00},/*H*/
		{0x00, 0x41, 0x41, 0x7F, 0x41, 0x41, 0x00, 0x00},/*I*/
		{0x00, 0x00, 0x31, 0x41, 0x3F, 0x01, 0x00, 0x00},/*J*/
		{0x00, 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00},/*K*/
		{0x00, 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00},/*L*/
		{0x00, 0x7F, 0x02, 0x0C, 0x0C, 0x06, 0x7F, 0x00},/*M*/
		{0x00, 0x7F, 0x06, 0x0C, 0x18, 0x30, 0x7F, 0x00},/*N*/
		{0x00, 0x1C, 0x22, 0x41, 0x41, 0x22, 0x1C, 0x00},/*O*/
		{0x00, 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00},/*P*/
		{0x00, 0x1E, 0x21, 0x21, 0x61, 0x61, 0x5E, 0x00},/*Q*/
		{0x00, 0x7F, 0x09, 0x09, 0x09, 0x76, 0x00, 0x00},/*R*/
		{0x00, 0x46, 0x47, 0x4D, 0x79, 0x31, 0x00, 0x00},/*S*/
		{0x00, 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00},/*T*/
		{0x00, 0x1F, 0x20, 0x40, 0x40, 0x20, 0x1F, 0x00},/*U*/
		{0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x00},/*V*/
		{0x3F, 0x40, 0x40, 0x7F, 0x40, 0x40, 0x3F, 0x00},/*W*/
		{0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00},/*X*/
		{0x00, 0x07, 0x0C, 0x78, 0x78, 0x0C, 0x07, 0x00},/*Y*/
		{0x00, 0x61, 0x51, 0x49, 0x45, 0x43, 0x41, 0x00},/*Z*/
		{0x00, 0x00, 0x7E, 0x42, 0x42, 0x42, 0x00, 0x00},/*[*/
		{0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00},/*\*/
		{0x00, 0x00, 0x42, 0x42, 0x42, 0x7E, 0x00, 0x00},/*]*/
		{0x00, 0x00, 0x08, 0x04, 0x02, 0x04, 0x08, 0x00},/*^*/
		{0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00},/*_*/
		{0x00, 0x00, 0x00, 0x02, 0x0C, 0x00, 0x00, 0x00},/*`*/
		{0x00, 0x00, 0x32, 0x4A, 0x4A, 0x4A, 0x7C, 0x00},/*a*/
		{0x00, 0x00, 0x7E, 0x48, 0x48, 0x30, 0x00, 0x00},/*b*/
		{0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x00, 0x00},/*c*/
		{0x00, 0x00, 0x30, 0x48, 0x48, 0x7E, 0x00, 0x00},/*d*/
		{0x00, 0x00, 0x3C, 0x4A, 0x4A, 0x4C, 0x00, 0x00},/*e*/
		{0x00, 0x00, 0x7C, 0x0A, 0x0A, 0x0A, 0x00, 0x00},/*f*/
		{0x00, 0x00, 0x4C, 0x52, 0x52, 0x7C, 0x00, 0x00},/*g*/
		{0x00, 0x00, 0x7E, 0x10, 0x10, 0x60, 0x00, 0x00},/*h*/
		{0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x00},/*i*/
		{0x00, 0x00, 0x00, 0x20, 0x40, 0x3A, 0x00, 0x00},/*j*/
		{0x00, 0x00, 0x7E, 0x18, 0x24, 0x42, 0x00, 0x00},/*k*/
		{0x00, 0x00, 0x00, 0x42, 0x7E, 0x40, 0x00, 0x00},/*l*/
		{0x00, 0x02, 0x7C, 0x02, 0x7E, 0x02, 0x7C, 0x00},/*m*/
		{0x00, 0x02, 0x7C, 0x02, 0x02, 0x7C, 0x00, 0x00},/*n*/
		{0x00, 0x00, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x00},/*o*/
		{0x00, 0x00, 0x7C, 0x12, 0x12, 0x0C, 0x00, 0x00},/*p*/
		{0x00, 0x00, 0x0C, 0x12, 0x12, 0x7C, 0x00, 0x00},/*q*/
		{0x00, 0x00, 0x7E, 0x04, 0x02, 0x02, 0x02, 0x00},/*r*/
		{0x00, 0x00, 0x44, 0x4A, 0x52, 0x22, 0x00, 0x00},/*s*/
		{0x00, 0x00, 0x08, 0x3E, 0x48, 0x28, 0x00, 0x00},/*t*/
		{0x00, 0x00, 0x3C, 0x40, 0x40, 0x3C, 0x40, 0x00},/*u*/
		{0x00, 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00},/*v*/
		{0x00, 0x1C, 0x20, 0x40, 0x7C, 0x40, 0x20, 0x1C},/*w*/
		{0x00, 0x00, 0x48, 0x30, 0x30, 0x48, 0x00, 0x00},/*x*/
		{0x00, 0x00, 0x46, 0x48, 0x48, 0x3E, 0x00, 0x00},/*y*/
		{0x00, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00},/*z*/
		{0x00, 0x00, 0x08, 0x3E, 0x41, 0x00, 0x00, 0x00},/*{*/
		{0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00},/*|*/
		{0x00, 0x00, 0x00, 0x41, 0x41, 0x3E, 0x08, 0x00},/*}*/
		{0x00, 0x10, 0x08, 0x10, 0x20, 0x10, 0x00, 0x00},/*~*/
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
	uint8 local_columnOnValue=STD_HIGH;
	uint8 local_columnOffValue=STD_LOW;

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
		local_columnOnValue=local_CommonRowType;
		local_columnOffValue=!local_CommonRowType;

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
				LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_columnOnValue);

				/*wait for the predefined time in the global variable */
				LedMatrix_SetBusyWaitInTicks(LedMatrix_NumberOfTicks);

				/*disable the column*/
				LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_columnOffValue);
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
	uint16 local_TimeCountsValue=0;
	uint16 local_TimeLoopCounter=0;
	LedMatrix_CommonRowType_t local_CommonRowType=LEDMATRIX_COMMON_ROW_ANODE;
	uint8 local_columnOnValue=STD_HIGH;
	uint8 local_columnOffValue=STD_LOW;
	uint8 local_characterShiftsCounter=0;
	/*pointer to the first element of the data array*/
	uint8 *local_dataPtr=(uint8*)LedMatrix_characterArray[dataIndex];

	/*check Id*/
	if(LedMatrix_Id>LEDMATRIX_NUMBER_OF_CONFIGURED_MODULES)
	{
		returnValue=LEDMATRIX_E_NOT_OK;
	}
	else
	{
		/*calculating the number of loop to achieve the wanted time*/
		local_TimeCountsValue=ShiftingTimeInMs/(LEDMATRIX_NUMBER_OF_COLUMNS*LedMatrix_NumberOfTicks);

		/*this value is used in flipping the array values if the rows are common cathode  */
		local_CommonRowType=gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_CommonRowType;

		/*these values is used to turn on/off the column depending on common row type*/
		local_columnOnValue=local_CommonRowType;
		local_columnOffValue=!local_CommonRowType;

		/*this counter used to determine how many shifts needed to display all text*/
		local_characterShiftsCounter=(LEDMATRIX_SIZE_OF_DATA_ARRAY-1)*LEDMATRIX_NUMBER_OF_COLUMNS;

		for( ; local_characterShiftsCounter>0 ; local_characterShiftsCounter--)
		{
			for(local_TimeLoopCounter=0 ; local_TimeLoopCounter<local_TimeCountsValue ; local_TimeLoopCounter++)
			{
				/*loop on the columns */
				for(local_columnsCounter=0 ; local_columnsCounter<LEDMATRIX_NUMBER_OF_COLUMNS ; local_columnsCounter++)
				{
					/*set data on all row pins*/
					for(local_rowsCounter=0 ; local_rowsCounter<LEDMATRIX_NUMBER_OF_ROWS;local_rowsCounter++)
					{
						/*this line gets the current row of value and then set all of it's bits to the row pins*/
						/*XOR with local_CommonRowType to flip the values of the array if the rows were common cathode as main array in common row anode */
						LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_RowsChannelArr[local_rowsCounter] , (GET_BIT(local_dataPtr[local_columnsCounter] , local_rowsCounter)^local_CommonRowType));
					}

					/*enable column*/
					/*depending on the value common row type enable the column*/
					LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_columnOnValue);

					/*wait for the predefined time in the global variable */
					LedMatrix_SetBusyWaitInTicks(LedMatrix_NumberOfTicks);

					/*disable the column*/
					LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_columnOffValue);
				}
			}
			local_dataPtr++;
		}
	}

	return returnValue;
}

/**************************************************************************************************************************************
 *  Function : LedMatrix_DisplayStringSynch                                                                                           *
 *  Param    : IN     : Name / LedMatrix_Id                                                                                           *
 *                      Type / LedMatrix_Id_t                                                                                         *
 *                      Desc / predefine macro for LedMatrix id                                                                       *
 *                                                                                                                                    *
 *                      Name / String                                                                                                 *
 *                      Type / LedMatrix_data_t*                                                                                      *
 *                      Desc / takes string from the user                                                                             *
 *                                                                                                                                    *
 *                      Name / StringLength                                                                                           *
 *                      Type / const LedMatrix_StringSize_t                                                                           *
 *                      Desc / takes the size of the given string without Null Character                                              *
 *                                                                                                                                    *
 *                      Name / ShiftingTimeInMs                                                                                       *
 *                      Type / LedMatrix_timeInMs_t                                                                                   *
 *                      Desc / takes the time which the character will be shifted after , and time must be higher than                *
 *                              character display time                                                                                *
 *                                                                                                                                    *
 *  Return   : LedMatrix_ErrorState_t                                                                                                 *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used to display string of ascii values and display it on the led matrix with the given shifting          *
 *             timing                                                                                                                 *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

LedMatrix_ErrorState_t LedMatrix_DisplayStringSynch(LedMatrix_Id_t  LedMatrix_Id , const LedMatrix_data_t* String ,LedMatrix_StringSize_t StringLength,  LedMatrix_timeInMs_t ShiftingTimeInMs)
{
	LedMatrix_ErrorState_t returnValue=LEDMATRIX_E_OK;
	LedMatrix_NumberOfPins_t local_columnsCounter=0;
	LedMatrix_NumberOfPins_t local_rowsCounter=0;

	LedMatrix_CommonRowType_t local_CommonRowType=LEDMATRIX_COMMON_ROW_ANODE;

	uint16 local_TimeCountsValue=0;
	uint16 local_TimeLoopCounter=0;

	uint8 local_columnOnValue=STD_HIGH;
	uint8 local_columnOffValue=STD_LOW;

	/*this variable must be big enough to hold the value of (string size*# of columns)*/
	uint16 local_characterShiftsCounter=0;

	/*current index in the string */
	LedMatrix_StringSize_t local_CurrentLetterIndex=0;

	/*current index for the column*/
	LedMatrix_NumberOfPins_t local_CurrentLetterColumnIndex;

	/*current wanted value index in the ascii array*/
	uint16 local_currentIndex;

	/*pointer to the first element of the data array*/
	uint8 *local_dataPtr=(uint8*)LedMatrix_CharacterAsciiArray;

	/*check if size of string ==1*/
	if(LedMatrix_Id>LEDMATRIX_NUMBER_OF_CONFIGURED_MODULES)
	{
		returnValue=LEDMATRIX_E_NOT_OK;
	}
	else
	{
		if(StringLength==LEDMATRIX_ONE_CHARACTER)
		{
			/*if so display only one character*/
		}
		else
		{

			/*calculating the number of loop to achieve the wanted time*/
			local_TimeCountsValue=ShiftingTimeInMs/(LEDMATRIX_NUMBER_OF_COLUMNS*LedMatrix_NumberOfTicks);

			/*this value is used in flipping the array values if the rows are common cathode  */
			local_CommonRowType=gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_CommonRowType;

			/*these values is used to turn on/off the column depending on common row type*/
			local_columnOnValue=local_CommonRowType;
			local_columnOffValue=!local_CommonRowType;

			/*this variable to indicate the current character index to be displayed*/
			local_CurrentLetterIndex=0;

			local_CurrentLetterColumnIndex=0;
			/*this counter used to determine how many shifts needed to display all text*/
			local_characterShiftsCounter=(StringLength-1)*LEDMATRIX_NUMBER_OF_COLUMNS;

			/*loop on until all character is displayed*/
			/*which means shift all columns = ((string size-1) * # of columns)*/
			for( ; local_characterShiftsCounter>0 ; local_characterShiftsCounter--)
			{
				if(local_CurrentLetterColumnIndex==LEDMATRIX_NUMBER_OF_COLUMNS)
				{
					local_CurrentLetterColumnIndex=0;
					local_CurrentLetterIndex++;
				}
				for(local_TimeLoopCounter=0 ; local_TimeLoopCounter<local_TimeCountsValue ; local_TimeLoopCounter++)
				{

					/*loop on the columns */
					for(local_columnsCounter=0 ; local_columnsCounter<LEDMATRIX_NUMBER_OF_COLUMNS ; local_columnsCounter++)
					{
						if(local_CurrentLetterColumnIndex+local_columnsCounter<LEDMATRIX_NUMBER_OF_COLUMNS)
						{
							/*current column belongs to the first character*/
							/*to get the position of the current column value in the ascii array we have to get the value from the string and
							 * then mul it by the number of columns in the array now we are the starting address of the wanted character array of columns
							 * to specify the wanted columns we need to add the offset to current value*/
							/*I subtracted 32 from the value as the my ascii values starts from space character*/

							local_currentIndex=((((uint16)String[local_CurrentLetterIndex])-LEDMATRIX_NUMBER_OF_UNUSED_CHAR)*LEDMATRIX_NUMBER_OF_COLUMNS)+(local_CurrentLetterColumnIndex+local_columnsCounter);
						}
						else
						{
							/*current column belongs to the second character*/
							local_currentIndex=((((uint16)String[local_CurrentLetterIndex+1])-LEDMATRIX_NUMBER_OF_UNUSED_CHAR)*LEDMATRIX_NUMBER_OF_COLUMNS)+((local_CurrentLetterColumnIndex+local_columnsCounter)%LEDMATRIX_NUMBER_OF_COLUMNS);
						}

						/*set data on all row pins*/
						for(local_rowsCounter=0 ; local_rowsCounter<LEDMATRIX_NUMBER_OF_ROWS;local_rowsCounter++)
						{
							/*this line gets the current row of value and then set all of it's bits to the row pins*/
							/*XOR with local_CommonRowType to flip the values of the array if the rows were common cathode as main array in common row anode */
							LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_RowsChannelArr[local_rowsCounter] , (GET_BIT(local_dataPtr[local_currentIndex] , local_rowsCounter)^local_CommonRowType));
						}

						/*enable column*/
						/*depending on the value common row type enable the column*/
						LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_columnOnValue);

						/*wait for the predefined time in the global variable */
						LedMatrix_SetBusyWaitInTicks(LedMatrix_NumberOfTicks);

						/*disable the column*/
						LedMatrix_WriteChannel(gastr_LedMatrixConfigArr[LedMatrix_Id].LedMatrix_ColumnsChannelArr[local_columnsCounter] , local_columnOffValue);
					}
				}

				/*the current column is updated after each shift*/
				local_CurrentLetterColumnIndex++;
			}
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



