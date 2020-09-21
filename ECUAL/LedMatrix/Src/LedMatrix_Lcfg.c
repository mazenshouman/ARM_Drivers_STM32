/*
 *  File 	   : LedMatrix_Lcfg.c
 *  Created on : Sep 20, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Std_types.h"
#include "Dio_Lcfg.h"
#include "Dio.h"
#include "SysTick.h"
#include "LedMatrix_Wrapper.h"
#include "LedMatrix_Cfg.h"
#include "LedMatrix.h"
#include "LedMatrix_Lcfg.h"


/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/

LedMatrix_ConfigType gastr_LedMatrixConfigArr[LEDMATRIX_NUMBER_OF_CONFIGURED_MODULES]=
/*                                                            RowsChannelIds                           	                                                                                                      ColumnsChannelIds                                                                                         CommonRowTyoe                                 */
{
   /*first LedMatrix*/
		{     {DIO_CHANNEL_A0,DIO_CHANNEL_A1,DIO_CHANNEL_A2,DIO_CHANNEL_A3,DIO_CHANNEL_A4,DIO_CHANNEL_A5,DIO_CHANNEL_A6,DIO_CHANNEL_A7}         ,            {DIO_CHANNEL_B5, DIO_CHANNEL_B6, DIO_CHANNEL_B7, DIO_CHANNEL_B8, DIO_CHANNEL_B9, DIO_CHANNEL_B10, DIO_CHANNEL_B11 ,DIO_CHANNEL_B12}     ,             LEDMATRIX_COMMON_ROW_CATHODE}/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------**/

};



/****************************************************************************/



