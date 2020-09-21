/*
 *  File 	   : LedMatrix.h
 *  Created on : Sep 20, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef LEDMATRIX_INC_LEDMATRIX_H_
#define LEDMATRIX_INC_LEDMATRIX_H_

/************************************************************************
 *                       Macros And Types                               *
 ************************************************************************/

typedef uint8 LedMatrix_Id_t;
#define LEDMATRIX_ID0                                         (LedMatrix_Id_t)0
#define LEDMATRIX_ID1                                         (LedMatrix_Id_t)1
#define LEDMATRIX_ID2                                         (LedMatrix_Id_t)2
#define LEDMATRIX_ID3                                         (LedMatrix_Id_t)3
#define LEDMATRIX_ID4                                         (LedMatrix_Id_t)4
#define LEDMATRIX_ID5                                         (LedMatrix_Id_t)5
#define LEDMATRIX_ID6                                         (LedMatrix_Id_t)6
#define LEDMATRIX_ID7                                         (LedMatrix_Id_t)7
#define LEDMATRIX_ID8                                         (LedMatrix_Id_t)8
#define LEDMATRIX_ID9                                         (LedMatrix_Id_t)9
#define LEDMATRIX_ID10                                        (LedMatrix_Id_t)10


/*
 * Error state macros
 * */
typedef uint8 LedMatrix_ErrorState_t;
#define LEDMATRIX_E_OK                                        (LedMatrix_ErrorState_t)0
#define LEDMATRIX_E_NOT_OK                                    (LedMatrix_ErrorState_t)1
#define LEDMATRIX_ID_OUTOFRANGE                               (LedMatrix_ErrorState_t)2
#define LEDMATRIX_NULL_POINTER                                (LedMatrix_ErrorState_t)3


typedef uint8 LedMatrix_CurrentState_t;
#define LEDMATRIX_STATE_NOT_FINISHED                          (LedMatrix_CurrentState_t)0
#define LEDMATRIX_STATE_FINISHED                              (LedMatrix_CurrentState_t)1

/*need modification to add array of characters*/
typedef uint8 LedMatrix_dataIndex_t;

typedef uint32 LedMatrix_timeInMs_t;
/************************************************************************/

/************************************************************************
 *                    LedMatrix functions' prototype                    *
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
 *  Desc     : This function initialize initialize the timer if it was configured to be controlled using it if it was configured      *
 *             to be controlled using rtos then this function will has no effect                                                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void LedMatrix_Init(void);


/**************************************************************************************************************************************
 *  Function : LedMatrix_DisplayCharSynch                                                                                             *
 *  Param    : IN     : Name / LedMatrix_Id                                                                                           *
 *                      Type / LedMatrix_Id_t                                                                                         *
 *                      Desc / predefine macro for LedMatrix id                                                                       *
 *                                                                                                                                    *
 *                      Name / dataIndex                                                                                              *
 *                      Type / LedMatrix_data_t                                                                                       *
 *                      Desc / takes the character wanted to be dispalyed on led matrix from the predefined array                     *
 *                                                                                                                                    *
 *                      Name / TimeInMs                                                                                               *
 *                      Type / LedMatrix_data_t                                                                                       *
 *                      Desc / takes the time which the character will be displayed for                                               *
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

LedMatrix_ErrorState_t LedMatrix_DisplayCharSynch(LedMatrix_Id_t  LedMatrix_Id , LedMatrix_dataIndex_t dataIndex , LedMatrix_timeInMs_t TimeInMs);

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

LedMatrix_ErrorState_t LedMatrix_DisplayTextSynch(LedMatrix_Id_t  LedMatrix_Id , LedMatrix_dataIndex_t dataIndex , LedMatrix_timeInMs_t ShiftingTimeInMs);

/**************************************************************************************************************************************
 *  Function : LedMatrix_DisplayCharAsynch                                                                                            *
 *  Param    : IN     : Name / LedMatrix_Id                                                                                           *
 *                      Type / LedMatrix_Id_t                                                                                         *
 *                      Desc / predefine macro for LedMatrix id                                                                       *
 *                                                                                                                                    *
 *             Output : Name / data                                                                                                   *
 *                      Type / LedMatrix_data_t                                                                                       *
 *                      Desc / takes the character wanted to be dispalyed on led matrix                                               *
 *                                                                                                                                    *
 *  Return   : LedMatrix_CurrentState_t                                                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used to display character on the led matrix by displaying column by column using the                     *
 *             predefine rate in the cfg file by using state machine so that it won't block the system and user must sit it           *
 *             as call bakck funtion in the timer                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

LedMatrix_CurrentState_t LedMatrix_DisplayCharAsynch(LedMatrix_Id_t  LedMatrix_Id , LedMatrix_dataIndex_t data);


#endif /* LEDMATRIX_INC_LEDMATRIX_H_ */
