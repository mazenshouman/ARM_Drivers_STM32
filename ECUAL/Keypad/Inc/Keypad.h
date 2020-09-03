/*
 *  File 	   : Keypad.h
 *  Created on : April 9, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef KEYPAD_INC_KEYPAD_H_
#define KEYPAD_INC_KEYPAD_H_

#include "keypad_Cfg.h"
/************************************************************************
 *                       Macros And Types                               *
 ************************************************************************/

typedef uint8 Keypad_IdType;
#define KEYPAD_ID0                                         (Keypad_IdType)0
#define KEYPAD_ID1                                         (Keypad_IdType)1
#define KEYPAD_ID2                                         (Keypad_IdType)2
#define KEYPAD_ID3                                         (Keypad_IdType)3
#define KEYPAD_ID4                                         (Keypad_IdType)4
#define KEYPAD_ID5                                         (Keypad_IdType)5
#define KEYPAD_ID6                                         (Keypad_IdType)6
#define KEYPAD_ID7                                         (Keypad_IdType)7
#define KEYPAD_ID8                                         (Keypad_IdType)8
#define KEYPAD_ID9                                         (Keypad_IdType)9
#define KEYPAD_ID10                                        (Keypad_IdType)10

/*
 * Error state macros
 * */
typedef uint8 Keypad_ErrorStateType;
#define KEYPAD_E_OK                                    (Keypad_ErrorStateType)0
#define KEYPAD_E_NOT_OK                                (Keypad_ErrorStateType)1
#define KEYPAD_ID_OUTOFRANGE                           (Keypad_ErrorStateType)2
#define KEYPAD_ACTIVE_TYPE_IS_NOT_DEFINED              (Keypad_ErrorStateType)3
#define KEYPAD_NULL_POINTER                            (Keypad_ErrorStateType)4
#define KEYPAD_UNDEFINED_STATE                         (Keypad_ErrorStateType)5


#ifdef KEYPAD_PERIODIC_UPDATE
/*
 * states used in case of real time usage or periodic check on the switch
 * */

typedef uint8 Keypad_StateType;
#define KEYPAD_RELEASED_STATE                          (Keypad_StateType)0
#define KEYPAD_PRE_PRESSED_STATE                       (Keypad_StateType)1
#define KEYPAD_PRESSED_STATE                           (Keypad_StateType)2
#define KEYPAD_PRE_RELEASED_STATE                      (Keypad_StateType)3



#endif

/************************************************************************/

/************************************************************************
 *                    Keypad functions' prototype                   *
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
 *             it will init the local array which holds the states of the keys                                                        *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void Keypad_Init(void);


#ifndef KEYPAD_PERIODIC_UPDATE
/*if i try to while on the key until it is released then the data won't send to the caller function
 * until the key is unpressed which lead to shortage in responsiveness of the action which depends
 * on upon this key
 * */

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

Keypad_ErrorStateType Keypad_GetKey(Keypad_IdType  Keypad_Id , keypad_OutputDataType* data);

/*
 * if you dont want to bather yourself with delay or handling the debouncing effect of the switch
 * use this function but take care that it will block the system until the switch is released
 * */

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

Keypad_ErrorStateType Keypad_GetKeyAfterRelease(Keypad_IdType  Keypad_Id , keypad_OutputDataType* data);

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

Keypad_ErrorStateType Keypad_CheckKeys(Keypad_IdType  Keypad_Id , keypad_OutputDataType* data);

#endif

#endif /* KEYPAD_INC_KEYPAD_H_ */
