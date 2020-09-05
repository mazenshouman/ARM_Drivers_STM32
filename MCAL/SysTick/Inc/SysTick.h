/*
 *  File 	   : SysTick.h
 *  Created on : Sep 5, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef SYSTICK_INC_SYSTICK_H_
#define SYSTICK_INC_SYSTICK_H_

/************************************************************************
 *                              Includes                                *
 ***********************************************************************/


/************************************************************************
 *                           Error macros                               *
 ***********************************************************************/
typedef uint8 SysTick_ErrorStatus_t;
#define SYSTICK_E_OK                                     (SysTick_ErrorStatus_t)0
#define SYSTICK_E_NOT_OK                                 (SysTick_ErrorStatus_t)1

/*max 24 bit value*/
typedef uint32 SysTick_LoadValue_t;


typedef void (*SysTick_PtrToFunction_t)(void);
/************************************************************************/

/************************************************************************
 *                    SysTick functions' prototypes                     *
 ***********************************************************************/
/**************************************************************************************************************************************
 *  Function : SysTick_Init                                                                                                           *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function pre-compile configuration to set clock source                                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_Init(void);


/**************************************************************************************************************************************
 *  Function : SysTick_SetBusyWaitInTicks                                                                                             *
 *  Param    : IN     : Name / NumberOfTicks                                                                                          *
 *                      Type / SysTick_LoadValue_t                                                                                    *
 *                      Desc / value to be set to the load register max 24 bit                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function is a synchronous function used to make busy wait for specific time                                       *
 *             specified in number of ticks                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_SetBusyWaitInTicks(SysTick_LoadValue_t NumberOfTicks);

/**************************************************************************************************************************************
 *  Function : SysTick_SetIntervalSingleInTicks                                                                                             *
 *  Param    : IN     : Name / NumberOfTicks                                                                                          *
 *                      Type / SysTick_LoadValue_t                                                                                    *
 *                      Desc / value to be set to the load register max 24 bit                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function is a Asynchronous function used to make Single interval for specific time                                       *
 *             specified in number of ticks                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_SetIntervalSingleInTicks(SysTick_LoadValue_t NumberOfTicks);


/**************************************************************************************************************************************
 *  Function : SysTick_SetIntervalSingleInTicks                                                                                       *
 *  Param    : IN     : Name / NumberOfTicks                                                                                          *
 *                      Type / SysTick_LoadValue_t                                                                                    *
 *                      Desc / value to be set to the load register max 24 bit                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function is a Asynchronous function used to make periodic interval for specific time                              *
 *             specified in number of ticks                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_SetIntervalPeriodicInTicks(SysTick_LoadValue_t NumberOfTicks);


/**************************************************************************************************************************************
 *  Function : SysTick_StopInterval                                                                                                   *
 *  Param    : IN     : Name / NumberOfTicks                                                                                          *
 *                      Type / SysTick_LoadValue_t                                                                                    *
 *                      Desc / value to be set to the load register max 24 bit                                                        *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function stops the ongoing interval by disabling the peripheral                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

void SysTick_StopInterval(SysTick_LoadValue_t NumberOfTicks);

/**************************************************************************************************************************************
 *  Function : SytTick_GetElapsedTimeInTicks                                                                                          *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the time in tick since the timer started this interval                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

SysTick_LoadValue_t SytTick_GetElapsedTimeInTicks(void);

/**************************************************************************************************************************************
 *  Function : SytTick_GetRemainingTimeInTicks                                                                                        *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the remaining time in tick until the value register reach zero                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

SysTick_LoadValue_t SytTick_GetRemainingTimeInTicks(void);


/**************************************************************************************************************************************
 *  Function : SysTick_SetCallback                                                                                                    *
 *  Param    : IN     : Name / PtrToFunction                                                                                          *
 *                      Type / SysTick_PtrToFunction_t                                                                                *
 *                      Desc / takes the address of the function wanted to be callback                                                *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : SysTick_ErrorStatus_t                                                                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function set the callback function                                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

SysTick_ErrorStatus_t SysTick_SetCallback(SysTick_PtrToFunction_t PtrToFunction);

/**************************************************************************************************************************************
 *  Function : SysTick_DeInit                                                                                                           *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : void                                                                                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function pre-compile configuration to set clock source and initialize the module                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/
void SysTick_Deinit(void);

//void MSTK_voidSetIntervalSingleInTicks ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
//void MSTK_voidSetIntervalPeriodicInTicks( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
//void MSTK_voidStopInterval(void);
//u32  MSTK_u32GetElapsedTimeInTicks(void);
//u32  MSTK_u32GetRemainingTimeInTicks(void);




#endif /* SYSTICK_INC_SYSTICK_H_ */
