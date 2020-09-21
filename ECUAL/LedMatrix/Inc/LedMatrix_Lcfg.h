/*
 *  File 	   : LedMatrix_Lcfg.h
 *  Created on : Sep 20, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LEDMATRIX_INC_LEDMATRIX_LCFG_H_
#define LEDMATRIX_INC_LEDMATRIX_LCFG_H_

/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/
typedef uint8 LedMatrix_CommonRowType_t;
#define LEDMATRIX_COMMON_ROW_ANODE                              (LedMatrix_CommonRowType_t)0
#define LEDMATRIX_COMMON_ROW_CATHODE                            (LedMatrix_CommonRowType_t)1

/************************************************************************
 *                      Configuration Structure                         *
 ************************************************************************/

typedef struct{
	LedMatrix_ChannelType                   LedMatrix_RowsChannelArr[LEDMATRIX_NUMBER_OF_ROWS];
	LedMatrix_ChannelType                   LedMatrix_ColumnsChannelArr[LEDMATRIX_NUMBER_OF_COLUMNS];
	LedMatrix_CommonRowType_t               LedMatrix_CommonRowType;
}LedMatrix_ConfigType;


/************************************************************************
 *                      extern for Configuration Structure              *
 ************************************************************************/

extern LedMatrix_ConfigType gastr_LedMatrixConfigArr[];


/************************************************************************/

#endif /* LEDMATRIX_INC_LEDMATRIX_LCFG_H_ */
