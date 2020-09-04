/*
 *  File 	   : Nvic.h
 *  Created on : Sep 4, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef NVIC_INC_NVIC_H_
#define NVIC_INC_NVIC_H_

/************************************************************************
 *                              Includes                                *
 ************************************************************************/

#include "Port_Cfg.h"

/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/


/****************************
 *       Peripheral ID      *
 ***************************/
typedef uint8 Nvic_PeripheralId_t;

#define NVIC_WWDG								   	 (Nvic_PeripheralId_t)0
#define NVIC_PVD                                     (Nvic_PeripheralId_t)1
#define NVIC_TAMPER                                  (Nvic_PeripheralId_t)2
#define NVIC_RTC                                     (Nvic_PeripheralId_t)3
#define NVIC_FLASH                                   (Nvic_PeripheralId_t)4
#define NVIC_RCC                                     (Nvic_PeripheralId_t)5
#define NVIC_EXTI0                                   (Nvic_PeripheralId_t)6
#define NVIC_EXTI1                                   (Nvic_PeripheralId_t)7
#define NVIC_EXTI2                                   (Nvic_PeripheralId_t)8
#define NVIC_EXTI3                                   (Nvic_PeripheralId_t)9
#define NVIC_EXTI4                                   (Nvic_PeripheralId_t)10
#define NVIC_DMA1_Channel1                           (Nvic_PeripheralId_t)11
#define NVIC_DMA1_Channel2                           (Nvic_PeripheralId_t)12
#define NVIC_DMA1_Channel3                           (Nvic_PeripheralId_t)13
#define NVIC_DMA1_Channel4                           (Nvic_PeripheralId_t)14
#define NVIC_DMA1_Channel5                           (Nvic_PeripheralId_t)15
#define NVIC_DMA1_Channel6                           (Nvic_PeripheralId_t)16
#define NVIC_DMA1_Channel7                           (Nvic_PeripheralId_t)17
#define NVIC_ADC1_2                                  (Nvic_PeripheralId_t)18
#define NVIC_USB_HP_CAN_TX                           (Nvic_PeripheralId_t)19
#define NVIC_USB_LP_CAN_RX0                          (Nvic_PeripheralId_t)20
#define NVIC_CAN_RX1                                 (Nvic_PeripheralId_t)21
#define NVIC_CAN_SCE                                 (Nvic_PeripheralId_t)22
#define NVIC_EXTI9_5                                 (Nvic_PeripheralId_t)23
#define NVIC_TIM1_BRK                                (Nvic_PeripheralId_t)24
#define NVIC_TIM1_UP                                 (Nvic_PeripheralId_t)25
#define NVIC_TIM1_TRG_COM                            (Nvic_PeripheralId_t)26
#define NVIC_TIM1_CC                                 (Nvic_PeripheralId_t)27
#define NVIC_TIM2                                    (Nvic_PeripheralId_t)28
#define NVIC_TIM3                                    (Nvic_PeripheralId_t)29
#define NVIC_TIM4                                    (Nvic_PeripheralId_t)30
#define NVIC_I2C1_EV                                 (Nvic_PeripheralId_t)31
#define NVIC_I2C1_ER                                 (Nvic_PeripheralId_t)32
#define NVIC_I2C2_EV                                 (Nvic_PeripheralId_t)33
#define NVIC_I2C2_ER                                 (Nvic_PeripheralId_t)34
#define NVIC_SPI1                                    (Nvic_PeripheralId_t)35
#define NVIC_SPI2                                    (Nvic_PeripheralId_t)36
#define NVIC_USART1                                  (Nvic_PeripheralId_t)37
#define NVIC_USART2                                  (Nvic_PeripheralId_t)38
#define NVIC_USART3                                  (Nvic_PeripheralId_t)39
#define NVIC_EXTI15_10                               (Nvic_PeripheralId_t)40
#define NVIC_RTCAlarm								 (Nvic_PeripheralId_t)41
#define NVIC_USBWakeup                               (Nvic_PeripheralId_t)42
#define NVIC_TIM8_BRK                                (Nvic_PeripheralId_t)43
#define NVIC_TIM8_UP                                 (Nvic_PeripheralId_t)44
#define NVIC_TIM8_TRG_COM                            (Nvic_PeripheralId_t)45
#define NVIC_TIM8_CC                                 (Nvic_PeripheralId_t)46
#define NVIC_ADC3                                    (Nvic_PeripheralId_t)47
#define NVIC_FSMC                                    (Nvic_PeripheralId_t)48
#define NVIC_SDIO                                    (Nvic_PeripheralId_t)49
#define NVIC_TIM5                                    (Nvic_PeripheralId_t)50
#define NVIC_SPI3                                    (Nvic_PeripheralId_t)51
#define NVIC_UART4                                   (Nvic_PeripheralId_t)52
#define NVIC_UART5                                   (Nvic_PeripheralId_t)53
#define NVIC_TIM6                                    (Nvic_PeripheralId_t)54
#define NVIC_TIM7                                    (Nvic_PeripheralId_t)55
#define NVIC_DMA2_Channel1                           (Nvic_PeripheralId_t)56
#define NVIC_DMA2_Channel2                           (Nvic_PeripheralId_t)57
#define NVIC_DMA2_Channel3                           (Nvic_PeripheralId_t)ö58
#define NVIC_DMA2_Channel4_5                         (Nvic_PeripheralId_t)59

/**************************
 *         PRIORITY       *
 *************************/
typedef uint8 Nvic_PriorityValue_t;


/*Note:
 * depending on the value of the NVIC_PRIORITY_GROUPING_VALUE you have to set a value valid in that range
 * otherwise you will get an error
 * Ex:NVIC_PRIORITY_GROUPING_VALUE=SCB_PRIORITY_GROUPING_4GROUPS_4SUBGROUPS
 * 	  Max value for group is 3 and Max value for sub is 3 also
 * 	  Min value for both is 0 in all cases
 *
 * */

#define NVIC_PRIORITY_GROUP_0                         (Nvic_PriorityValue_t)0
#define NVIC_PRIORITY_GROUP_1                         (Nvic_PriorityValue_t)1
#define NVIC_PRIORITY_GROUP_2                         (Nvic_PriorityValue_t)2
#define NVIC_PRIORITY_GROUP_3                         (Nvic_PriorityValue_t)3
#define NVIC_PRIORITY_GROUP_4                         (Nvic_PriorityValue_t)4
#define NVIC_PRIORITY_GROUP_5                         (Nvic_PriorityValue_t)5
#define NVIC_PRIORITY_GROUP_6                         (Nvic_PriorityValue_t)6
#define NVIC_PRIORITY_GROUP_7                         (Nvic_PriorityValue_t)7
#define NVIC_PRIORITY_GROUP_8                         (Nvic_PriorityValue_t)8
#define NVIC_PRIORITY_GROUP_9                         (Nvic_PriorityValue_t)9
#define NVIC_PRIORITY_GROUP_10                        (Nvic_PriorityValue_t)10
#define NVIC_PRIORITY_GROUP_11                        (Nvic_PriorityValue_t)11
#define NVIC_PRIORITY_GROUP_12                        (Nvic_PriorityValue_t)12
#define NVIC_PRIORITY_GROUP_13                        (Nvic_PriorityValue_t)13
#define NVIC_PRIORITY_GROUP_14                        (Nvic_PriorityValue_t)14
#define NVIC_PRIORITY_GROUP_15                        (Nvic_PriorityValue_t)15

#define NVIC_PRIORITY_SUBGROUP_0                      (Nvic_PriorityValue_t)0
#define NVIC_PRIORITY_SUBGROUP_1                      (Nvic_PriorityValue_t)1
#define NVIC_PRIORITY_SUBGROUP_2                      (Nvic_PriorityValue_t)2
#define NVIC_PRIORITY_SUBGROUP_3                      (Nvic_PriorityValue_t)3
#define NVIC_PRIORITY_SUBGROUP_4                      (Nvic_PriorityValue_t)4
#define NVIC_PRIORITY_SUBGROUP_5                      (Nvic_PriorityValue_t)5
#define NVIC_PRIORITY_SUBGROUP_6                      (Nvic_PriorityValue_t)6
#define NVIC_PRIORITY_SUBGROUP_7                      (Nvic_PriorityValue_t)7
#define NVIC_PRIORITY_SUBGROUP_8                      (Nvic_PriorityValue_t)8
#define NVIC_PRIORITY_SUBGROUP_9                      (Nvic_PriorityValue_t)9
#define NVIC_PRIORITY_SUBGROUP_10                     (Nvic_PriorityValue_t)10
#define NVIC_PRIORITY_SUBGROUP_11                     (Nvic_PriorityValue_t)11
#define NVIC_PRIORITY_SUBGROUP_12                     (Nvic_PriorityValue_t)12
#define NVIC_PRIORITY_SUBGROUP_13                     (Nvic_PriorityValue_t)13
#define NVIC_PRIORITY_SUBGROUP_14                     (Nvic_PriorityValue_t)14
#define NVIC_PRIORITY_SUBGROUP_15                     (Nvic_PriorityValue_t)15



typedef uint8 Nvic_InterruptActiveStatus_t;
#define NVIC_INTERRUPT_NOT_ACTIVE                     (Nvic_InterruptActiveStatus_t)0
#define NVIC_INTERRUPT_ACTIVE                         (Nvic_InterruptActiveStatus_t)1



/************************************************************************
 *                           Error macros                               *
 ***********************************************************************/
typedef uint8 Nvic_ErrorStatus_t;
#define NVIC_E_OK                                     (Nvic_ErrorStatus_t)0
#define NVIC_E_NOT_OK                                 (Nvic_ErrorStatus_t)1

/************************************************************************/

/************************************************************************
 *                    NVIC functions' prototypes                        *
 ***********************************************************************/
/**************************************************************************************************************************************
 *  Function : Nvic_Init                                                                                                              *
 *  Param    : IN     : Name / None                                                                                                   *
 *                      Type / void                                                                                                   *
 *                      Desc / None                                                                                                   *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function uses linking configuration structure to configure Peripheral define in                                   *
 *             Nvic_LCFG and externed here to configure pins                                                                          *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_Init(void);

/**************************************************************************************************************************************
 *  Function : Nvic_EnableInterrupt                                                                                                   *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Enables interrupt for specific peripheral                                                                *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_EnableInterrupt(Nvic_PeripheralId_t PeripheralID);

/**************************************************************************************************************************************
 *  Function : Nvic_DisableInterrupt                                                                                                  *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Disables interrupt for specific peripheral                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_DisableInterrupt(Nvic_PeripheralId_t PeripheralID);

/**************************************************************************************************************************************
 *  Function : Nvic_SetPending                                                                                                        *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function set pending flag for specific peripheral                                                                 *
 *             Note: pending flag is automatically clearing at the start of the ISR                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_SetPending(Nvic_PeripheralId_t PeripheralID);

/**************************************************************************************************************************************
 *  Function : Nvic_ClearPending                                                                                                      *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function Clear pending flag for specific peripheral                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_ClearPending(Nvic_PeripheralId_t PeripheralID);

/**************************************************************************************************************************************
 *  Function : Nvic_ReadActiveFlag                                                                                                    *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_InterruptActiveStatus_t                                                                                           *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function return the state of active flag for specific peripheral                                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_InterruptActiveStatus_t Nvic_ReadActiveFlag(Nvic_PeripheralId_t PeripheralID);

/**************************************************************************************************************************************
 *  Function : Nvic_SetInterruptSoftwarePriority                                                                                      *
 *  Param    : IN     : Name / PeripheralID                                                                                           *
 *                      Type / Nvic_PeripheralId_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *                      Name / GroupNumber                                                                                            *
 *                      Type / Nvic_PriorityValue_t                                                                                   *
 *                      Desc / takes predefined macro for Group number                                                                *
 *                      Name / SubgroupNumber                                                                                         *
 *                      Type / Nvic_PriorityValue_t                                                                                   *
 *                      Desc / takes predefined macro for Subgroup number                                                             *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Nvic_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function sets software priority for specific peripheral choose the right value for group and                      *
 *             group so theat the fucntion doesn't detect error in the given values                                                   *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/

Nvic_ErrorStatus_t Nvic_SetInterruptSoftwarePriority(Nvic_PeripheralId_t PeripheralID , Nvic_PriorityValue_t GroupNumber , Nvic_PriorityValue_t SubgroupNumber);



#endif /* NVIC_INC_NVIC_H_ */
