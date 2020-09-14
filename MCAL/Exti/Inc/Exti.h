/*
 *  File 	   : Exti.h
 *  Created on : Sep 10, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef EXTI_EXTI_H_
#define EXTI_EXTI_H_

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/

/****************************
 *         Lines ID         *
 ***************************/

typedef uint8 Exti_LineId_t;

#define EXTI_LINE0                                          (Exti_LineId_t)0
#define EXTI_LINE1                                          (Exti_LineId_t)1
#define EXTI_LINE2                                          (Exti_LineId_t)2
#define EXTI_LINE3                                          (Exti_LineId_t)3
#define EXTI_LINE4                                          (Exti_LineId_t)4
#define EXTI_LINE5                                          (Exti_LineId_t)5
#define EXTI_LINE6                                          (Exti_LineId_t)6
#define EXTI_LINE7                                          (Exti_LineId_t)7
#define EXTI_LINE8                                          (Exti_LineId_t)8
#define EXTI_LINE9                                          (Exti_LineId_t)9
#define EXTI_LINE10                                         (Exti_LineId_t)10
#define EXTI_LINE11                                         (Exti_LineId_t)11
#define EXTI_LINE12                                         (Exti_LineId_t)12
#define EXTI_LINE13                                         (Exti_LineId_t)13
#define EXTI_LINE14                                         (Exti_LineId_t)14
#define EXTI_LINE15                                         (Exti_LineId_t)15
#define EXTI_LINE16_PVD                                     (Exti_LineId_t)16
#define EXTI_LINE17_RTC_ALARM                               (Exti_LineId_t)17
#define EXTI_LINE18_USB_WAKEUP                              (Exti_LineId_t)18
#define EXTI_LINE19_ETHERNET_WAKEUP                         (Exti_LineId_t)19


/***************************
 *           Mode          *
 **************************/
typedef uint8 Exti_Mode_t;

#define EXTI_MODE_INTERRUPT                                 (Exti_Mode_t)0
#define EXTI_MODE_EVENT                                     (Exti_Mode_t)1

/***************************
 *      Initial State      *
 **************************/
typedef uint8 Exti_InitialState_t;

#define EXTI_DISABLED                                       (Exti_InitialState_t)0
#define EXTI_ENABLED                                        (Exti_InitialState_t)1

/***************************
 *      Trigger Type       *
 **************************/
typedef uint8 Exti_Trigger_t;

#define EXTI_TRIGGER_RISING_EDGE                            (Exti_Trigger_t)1
#define EXTI_TRIGGER_FAllING_EDGE                           (Exti_Trigger_t)2
#define EXTI_TRIGGER_ON_CHANGE                              (Exti_Trigger_t)3

/***************************
 *      Pending Flag       *
 **************************/
typedef uint8 Exti_PendingFlagStatus_t;

#define EXTI_PENDING_FLAG_CLEARED                           (Exti_PendingFlagStatus_t)0
#define EXTI_PENDING_FLAG_SET                               (Exti_PendingFlagStatus_t)1

/***************************
 *   pointer to function   *
 ***************************/
typedef void (*Exti_PtrToFunction)(void);

/************************************************************************
 *                           Error macros                               *
 ***********************************************************************/
typedef uint8 Exti_ErrorStatus_t;

#define EXTI_E_OK                                           (Exti_ErrorStatus_t)0
#define EXTI_E_NOT_OK                                       (Exti_ErrorStatus_t)1

/************************************************************************/

/************************************************************************
 *                    Exit functions' prototypes                        *
 ***********************************************************************/
/**************************************************************************************************************************************
 *  Function : Exti_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to configure Lines define in                                        *
 *             Exti_LCFG and externed here to configure Lines                                                                         *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_Init(void);

/**************************************************************************************************************************************
 *  Function : Exti_EnableLine                                                                                                        *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / Mode                                                                                                   *
 *                      Type / Exti_Mode_t                                                                                            *
 *                      Desc / takes predefined macro for interrupt/event                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Enables interrupt/event for specific Line                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_EnableLine(Exti_LineId_t LineId , Exti_Mode_t Mode);

/**************************************************************************************************************************************
 *  Function : Exti_DisableLine                                                                                                       *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / Mode                                                                                                   *
 *                      Type / Exti_Mode_t                                                                                            *
 *                      Desc / takes predefined macro for interrupt/event                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Disables interrupt/event for specific Line                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_DisableLine(Exti_LineId_t LineId , Exti_Mode_t Mode);

/**************************************************************************************************************************************
 *  Function : Exti_SetTrigger                                                                                                        *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / Trigger                                                                                                *
 *                      Type / Exti_Trigger_t                                                                                         *
 *                      Desc / takes predefined macro for trigger type                                                                *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function select trigger for specific line                                                                         *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_SetTrigger(Exti_LineId_t LineId , Exti_Trigger_t Trigger);

/**************************************************************************************************************************************
 *  Function : Exti_GenerateSoftwareInterrupt                                                                                         *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function generate software interrupt/event on specific line                                                       *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_GenerateSoftwareInterrupt(Exti_LineId_t LineId);

/**************************************************************************************************************************************
 *  Function : Exti_ClearPendingFlag                                                                                                      *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Clear pending flag for specific Line                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_ClearPendingFlag(Exti_LineId_t LineId);

/**************************************************************************************************************************************
 *  Function : Exti_GetPendingFlag                                                                                                    *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_PendingFlagStatus_t                                                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function gets the pending flag status for specific line                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_PendingFlagStatus_t Exti_GetPendingFlag(Exti_LineId_t LineId);

/**************************************************************************************************************************************
 *  Function : Exti_SetCallback                                                                                                       *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Exti_LineId_t                                                                                          *
 *                      Desc / takes predefined macro for Line id                                                                     *
 *                                                                                                                                    *
 *                      Name / PtrToFunction                                                                                          *
 *                      Type / Exti_PtrToFunction                                                                                     *
 *                      Desc / takes the address of the call back function                                                            *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Exti_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function set callback function for the wanted line                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Exti_ErrorStatus_t Exti_SetCallback(Exti_LineId_t LineId , Exti_PtrToFunction PtrToFunction);


#endif /* EXTI_EXTI_H_ */
