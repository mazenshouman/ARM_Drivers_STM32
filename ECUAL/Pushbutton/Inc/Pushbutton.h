/*
 *  File 	   : Pushbutton.h
 *  Created on : April 9, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef PUSHBUTTON_INC_PUSHBUTTON_H_
#define PUSHBUTTON_INC_PUSHBUTTON_H_


/************************************************************************
 *                       Macros And Types                               *
 ************************************************************************/
typedef uint8 Pushbutton_IdType;
#define PUSHBUTTON_ID0                                     (Pushbutton_IdType)0
#define PUSHBUTTON_ID1                                     (Pushbutton_IdType)1
#define PUSHBUTTON_ID2                                     (Pushbutton_IdType)2
#define PUSHBUTTON_ID3                                     (Pushbutton_IdType)3
#define PUSHBUTTON_ID4                                     (Pushbutton_IdType)4
#define PUSHBUTTON_ID5                                     (Pushbutton_IdType)5
#define PUSHBUTTON_ID6                                     (Pushbutton_IdType)6
#define PUSHBUTTON_ID7                                     (Pushbutton_IdType)7
#define PUSHBUTTON_ID8                                     (Pushbutton_IdType)8
#define PUSHBUTTON_ID9                                     (Pushbutton_IdType)9
#define PUSHBUTTON_ID10                                    (Pushbutton_IdType)10
#define PUSHBUTTON_ID11                                    (Pushbutton_IdType)11
#define PUSHBUTTON_ID12                                    (Pushbutton_IdType)12
#define PUSHBUTTON_ID13                                    (Pushbutton_IdType)13
#define PUSHBUTTON_ID14                                    (Pushbutton_IdType)14
#define PUSHBUTTON_ID15                                    (Pushbutton_IdType)15
#define PUSHBUTTON_ID16                                    (Pushbutton_IdType)16
#define PUSHBUTTON_ID17                                    (Pushbutton_IdType)17
#define PUSHBUTTON_ID18                                    (Pushbutton_IdType)18
#define PUSHBUTTON_ID19                                    (Pushbutton_IdType)19
#define PUSHBUTTON_ID20                                    (Pushbutton_IdType)20
#define PUSHBUTTON_ID21                                    (Pushbutton_IdType)21
#define PUSHBUTTON_ID22                                    (Pushbutton_IdType)22
#define PUSHBUTTON_ID23                                    (Pushbutton_IdType)23
#define PUSHBUTTON_ID24                                    (Pushbutton_IdType)24
#define PUSHBUTTON_ID25                                    (Pushbutton_IdType)25
#define PUSHBUTTON_ID26                                    (Pushbutton_IdType)26
#define PUSHBUTTON_ID27                                    (Pushbutton_IdType)27
#define PUSHBUTTON_ID28                                    (Pushbutton_IdType)28
#define PUSHBUTTON_ID29                                    (Pushbutton_IdType)29
#define PUSHBUTTON_ID30                                    (Pushbutton_IdType)30
#define PUSHBUTTON_ID31                                    (Pushbutton_IdType)31
#define PUSHBUTTON_ID32                                    (Pushbutton_IdType)32
#define PUSHBUTTON_ID33                                    (Pushbutton_IdType)33
#define PUSHBUTTON_ID34                                    (Pushbutton_IdType)34
#define PUSHBUTTON_ID35                                    (Pushbutton_IdType)35
#define PUSHBUTTON_ID36                                    (Pushbutton_IdType)36
#define PUSHBUTTON_ID37                                    (Pushbutton_IdType)37
#define PUSHBUTTON_ID38                                    (Pushbutton_IdType)38
#define PUSHBUTTON_ID39                                    (Pushbutton_IdType)39
#define PUSHBUTTON_ID40                                    (Pushbutton_IdType)40

/*
 * Error state macros
 * */
typedef uint8 Pushbutton_ErrorStateType;
#define PUSHBUTTON_E_OK                                    (Pushbutton_ErrorStateType)0
#define PUSHBUTTON_E_NOT_OK                                (Pushbutton_ErrorStateType)1
#define PUSHBUTTON_ID_OUTOFRANGE                           (Pushbutton_ErrorStateType)2
#define PUSHBUTTON_ACTIVE_TYPE_IS_NOT_DEFINED              (Pushbutton_ErrorStateType)3
#define PUSHBUTTON_NULL_POINTER                            (Pushbutton_ErrorStateType)4
#define PUSHBUTTON_UNDEFINED_STATE                         (Pushbutton_ErrorStateType)5


#ifdef PUSHBUTTON_PERIODIC_UPDATE

/*
 * states used in case of real time usage or periodic check on the switch
 * */

typedef uint8 Pushbutton_StateType;
#define PUSHBUTTON_RELEASED_STATE                          (Pushbutton_StateType)0
#define PUSHBUTTON_PRE_PRESSED_STATE                       (Pushbutton_StateType)1
#define PUSHBUTTON_PRESSED_STATE                           (Pushbutton_StateType)2
#define PUSHBUTTON_PRE_RELEASED_STATE                      (Pushbutton_StateType)3

/*
 * pointer to function to execute function from upper layer when current state is reached
 * */

typedef void (*Pushbutton_PtrToFunctionType)(void);


#else

typedef uint8 Pushbutton_StateType;
#define PUSHBUTTON_RELEASED_STATE                          (Pushbutton_StateType)0
#define PUSHBUTTON_PRESSED_STATE                           (Pushbutton_StateType)2

#endif

/************************************************************************/

/************************************************************************
 *                    PushButton functions' prototype                   *
 ************************************************************************/

/*
 * uses configuration parameter to enable periodic check functions or use just the normal read state funciton
 * for super loop systems
 * */
#ifndef PUSHBUTTON_PERIODIC_UPDATE

/**************************************************************************************************************************************
 *  Function : Pushbutton_ReadButtonLevel                                                                                             *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for Pushbutton id                                                                      *
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

Pushbutton_ErrorStateType Pushbutton_ReadButtonState(Pushbutton_IdType Pushbutton_Id , Pushbutton_StateType* State);

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

void Pushbutton_Init(void);

/**************************************************************************************************************************************
 *  Function : Pushbutton_GetCurrentState                                                                                             *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for Pushbutton id                                                                      *
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

Pushbutton_ErrorStateType Pushbutton_GetCurrentState(Pushbutton_IdType Pushbutton_Id , Pushbutton_StateType* State);

/**************************************************************************************************************************************
 *  Function : Pushbutton_GetCurrentState                                                                                             *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for Pushbutton id                                                                      *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : PushButton_ErrorStateType                                                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used with periodic calls to update the state of certain switch                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Pushbutton_ErrorStateType Pushbutton_UpdateState(Pushbutton_IdType Pushbutton_Id);

/**************************************************************************************************************************************
 *  Function : PushButton_SetCallBackFunction                                                                                         *
 *  Param    : IN     : Name / Pushbutton_Id                                                                                          *
 *                      Type / Pushbutton_IdType                                                                                      *
 *                      Desc / predefine macro for Pushbutton id                                                                      *
 *                                                                                                                                    *
 *                      Name / PtrToFunction                                                                                          *
 *                      Type / Pushbutton_PtrToFunctionType                                                                           *
 *                      Desc / takes Pointer to function which wanted to be executed when certain state is reached                    *
 *                                                                                                                                    *
 *                      Name / State                                                                                                  *
 *                      Type / PushButton_StateType                                                                                   *
 *                      Desc / predefine macro for Pushbutton state                                                                   *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Pushbutton_ErrorStateType                                                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function used with periodic calls to set callback functions for Pushbutton for certain state                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Pushbutton_ErrorStateType Pushbutton_SetCallBackFunction(Pushbutton_IdType Pushbutton_Id , Pushbutton_PtrToFunctionType PtrToFunction  , Pushbutton_StateType  State);


#endif
/**************************************************************************************************************************************/


#endif /* PUSHBUTTON_INC_PUSHBUTTON_H_ */
