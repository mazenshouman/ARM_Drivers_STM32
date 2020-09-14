/*
 *  File 	   : Afio.h
 *  Created on : Sep 14, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef AFIO_INC_AFIO_H_
#define AFIO_INC_AFIO_H_


/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/
/*there are two way to declare peripheral remap
 * 1- make an array in lcfg file for all peripherals wanted to be remapped and set the values exactly as wanted
 *  and or them together but this way will be used only in init function (for loop with or all array elements)
 * 2- we have to set macros for peripheral + value wanted to be set but the only problem each peripheral has
 *    different mask so we have to make switch statements
 *  */

/*************************
 *      Peripherals ID   *
 ************************/
typedef uint8 Afio_PeripheralId_t;
#define AFIO_SPI1                                                        (Afio_PeripheralId_t)0
#define AFIO_I2C1                                                        (Afio_PeripheralId_t)1
#define AFIO_USART1                                                      (Afio_PeripheralId_t)2
#define AFIO_TIM1                                                        (Afio_PeripheralId_t)6
#define AFIO_TIM2                                                        (Afio_PeripheralId_t)8
#define AFIO_TIM3                                                        (Afio_PeripheralId_t)10
#define AFIO_HSE_PD01                                                    (Afio_PeripheralId_t)15
#define AFIO_SWJ                                                         (Afio_PeripheralId_t)24


/*************************
 *       Remap Values    *
 ************************/
typedef uint8 Afio_RemapValue_t;
#define AFIO_SPI1_REMAP_A4_7_TO_A15_B3_5                                  (Afio_RemapValue_t)1
#define AFIO_I2C1_REMAP_B6_7_TO_B8_9                                      (Afio_RemapValue_t)1
#define AFIO_USART1_REMAP_A9_10_TO_B6_7                                   (Afio_RemapValue_t)1
#define AFIO_TIM1_REMAP_OPTION1                                           (Afio_RemapValue_t)1
#define AFIO_TIM1_REMAP_OPTION2                                           (Afio_RemapValue_t)2
#define AFIO_TIM1_REMAP_OPTION3                                           (Afio_RemapValue_t)3
#define AFIO_TIM2_REMAP_OPTION1                                           (Afio_RemapValue_t)1
#define AFIO_TIM2_REMAP_OPTION2                                           (Afio_RemapValue_t)2
#define AFIO_TIM2_REMAP_OPTION3                                           (Afio_RemapValue_t)3
#define AFIO_TIM3_REMAP_OPTION1                                           (Afio_RemapValue_t)1
#define AFIO_TIM3_REMAP_OPTION2                                           (Afio_RemapValue_t)2
#define AFIO_TIM3_REMAP_OPTION3                                           (Afio_RemapValue_t)3
#define AFIO_PD01_REMAP_OSC_TO_D0_1                                       (Afio_RemapValue_t)1
#define AFIO_SWJ_REMAP_FULL_SWJ                                           (Afio_RemapValue_t)0
#define AFIO_SWJ_REMAP_FULL_SWJ_WITHOUT_RESET                             (Afio_RemapValue_t)1
#define AFIO_SWJ_REMAP_SW_DP_ONLY                                         (Afio_RemapValue_t)2
#define AFIO_SWJ_REMAP_ALL_FREE                                           (Afio_RemapValue_t)4


/*************************
 *     Exti Lines ID     *
 ************************/
typedef uint8 Afio_ExtiLineId_t;

#define AFIO_EXTI_LINE0                                                   (Afio_ExtiLineId_t)0
#define AFIO_EXTI_LINE1                                                   (Afio_ExtiLineId_t)4
#define AFIO_EXTI_LINE2                                                   (Afio_ExtiLineId_t)8
#define AFIO_EXTI_LINE3                                                   (Afio_ExtiLineId_t)12
#define AFIO_EXTI_LINE4                                                   (Afio_ExtiLineId_t)32
#define AFIO_EXTI_LINE5                                                   (Afio_ExtiLineId_t)36
#define AFIO_EXTI_LINE6                                                   (Afio_ExtiLineId_t)40
#define AFIO_EXTI_LINE7                                                   (Afio_ExtiLineId_t)44
#define AFIO_EXTI_LINE8                                                   (Afio_ExtiLineId_t)64
#define AFIO_EXTI_LINE9                                                   (Afio_ExtiLineId_t)68
#define AFIO_EXTI_LINE10                                                  (Afio_ExtiLineId_t)72
#define AFIO_EXTI_LINE11                                                  (Afio_ExtiLineId_t)76
#define AFIO_EXTI_LINE12                                                  (Afio_ExtiLineId_t)96
#define AFIO_EXTI_LINE13                                                  (Afio_ExtiLineId_t)100
#define AFIO_EXTI_LINE14                                                  (Afio_ExtiLineId_t)104
#define AFIO_EXTI_LINE15                                                  (Afio_ExtiLineId_t)108


/*************************
 *   Exti Remap Values   *
 ************************/
typedef uint8 Afio_ExtiRemapValue_t;

#define AFIO_EXTI_REMAP_PORT_A                                            (Afio_ExtiRemapValue_t)0
#define AFIO_EXTI_REMAP_PORT_B                                            (Afio_ExtiRemapValue_t)1
#define AFIO_EXTI_REMAP_PORT_C                                            (Afio_ExtiRemapValue_t)2
#define AFIO_EXTI_REMAP_PORT_D                                            (Afio_ExtiRemapValue_t)3
#define AFIO_EXTI_REMAP_PORT_E                                            (Afio_ExtiRemapValue_t)4
#define AFIO_EXTI_REMAP_PORT_F                                            (Afio_ExtiRemapValue_t)5
#define AFIO_EXTI_REMAP_PORT_G                                            (Afio_ExtiRemapValue_t)6


/************************************************************************
 *                           Error macros                               *
 ***********************************************************************/
typedef uint8 Afio_ErrorStatus_t;
#define AFIO_E_OK                                                         (Afio_ErrorStatus_t)0
#define AFIO_E_NOT_OK                                                     (Afio_ErrorStatus_t)1

/************************************************************************/

/*********************************************************************************************************/

/************************************************************************/

/************************************************************************
 *                    AFIO functions' prototypes                         *
 ************************************************************************/
/**************************************************************************************************************************************
 *  Function : Afio_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Afio_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to rempa peripheral and remap exti line to different lines          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Afio_ErrorStatus_t Afio_Init(void);

/**************************************************************************************************************************************
 *  Function : Afio_RemapPeripheral                                                                                                   *
 *  Param    : IN     : Name / PeripheralId                                                                                           *
 *                      Type / Afio_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                                                                                                                                    *
 *                      Name / RemapValue                                                                                             *
 *                      Type / Afio_RemapValue_t                                                                                      *
 *                      Desc / takes predefined macro remap value                                                                     *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Afio_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function remap specific peripheral to different pins                                                              *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Afio_ErrorStatus_t Afio_RemapPeripheral(Afio_PeripheralId_t PeripheralId , Afio_RemapValue_t RemapValue);

/**************************************************************************************************************************************
 *  Function : Afio_RemapExtiLine                                                                                                     *
 *  Param    : IN     : Name / LineId                                                                                                 *
 *                      Type / Afio_ExtiLineId_t                                                                                      *
 *                      Desc / takes predefined macro for Exti Line id                                                                *
 *                                                                                                                                    *
 *                      Name / RemapValue                                                                                             *
 *                      Type / Afio_ExtiRemapValue_t                                                                                  *
 *                      Desc / takes predefined macro for remap value                                                                 *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Afio_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function remap specific Exti Line to different Port                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Afio_ErrorStatus_t Afio_RemapExtiLine(Afio_ExtiLineId_t LineId , Afio_ExtiRemapValue_t RemapValue);


/************************************************************************/


#endif /* AFIO_INC_AFIO_H_ */
