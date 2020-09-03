/*
 *  File 	   : Rcc.h
 *  Created on : Aug 30, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef RCC_INC_RCC_H_
#define RCC_INC_RCC_H_

/************************************************************************
 *                           File Includes                               *
 ************************************************************************/
#include "Rcc_MemMap.h"
#include "Rcc_Cfg.h"
/************************************************************************
 *                           Error macros                               *
 ************************************************************************/
typedef uint8 Rcc_ErrorStatus_t;
#define RCC_E_NOT_OK                                        (Rcc_ErrorStatus_t)1
#define RCC_E_OK                                            (Rcc_ErrorStatus_t)0
/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/

/****************************************
 *           HSI Status Macro           *
 ***************************************/
typedef uint32 Rcc_HsiStatus_t;
#define RCC_HSI_DISABLED                     (Rcc_HsiStatus_t)0
#define RCC_HSI_ENABLED                      (Rcc_HsiStatus_t)1

/****************************************
 *           HSI TRIM Macro             *
 ***************************************/
/*Note:by adding or decreasing the default value by on the HSI clock trimmed by 40Khz*/
typedef uint32 Rcc_HsiTrimValue_t;
#define RCC_HSI_TRIM_DEFALUT_VALUE           (Rcc_HsiTrimValue_t)16

/****************************************
 *           HSE Status Macro           *
 ***************************************/
typedef uint32 Rcc_HseStatus_t;
#define RCC_HSE_DISABLED                     (Rcc_HseStatus_t)0
#define RCC_HSE_ENABLED                      (Rcc_HseStatus_t)1

/*************************************
 *           HSE Bypass Macro       *
 ************************************/
typedef uint32 Rcc_HseBypassEnable_t;
#define RCC_HSE_NO_BYPASS                      (Rcc_HseBypassEnable_t)0
#define RCC_HSE_BYPASS                         (Rcc_HseBypassEnable_t)1

/************************************
 *           CSS Status Macro       *
 ***********************************/
typedef uint32 Rcc_CssStatus_t;
#define RCC_CSS_DISABLED                       (Rcc_CssStatus_t)0
#define RCC_CSS_ENABLED                        (Rcc_CssStatus_t)1

/************************************
 *           PLL Status Macro       *
 ***********************************/
typedef uint32 Rcc_PllStatus_t;
#define RCC_PLL_DISABLED                       (Rcc_PllStatus_t)0
#define RCC_PLL_ENABLED                        (Rcc_PllStatus_t)1

/************************************
 *           PLL Source Macro       *
 ***********************************/
typedef uint32 Rcc_PllSource_t;
#define Rcc_PLL_SOURCE_HSI_DIVIDED_2           (Rcc_PllSource_t)0
#define Rcc_PLL_SOURCE_HSE                     (Rcc_PllSource_t)1

/************************************
 *      PLL HSE Divider Macro       *
 ***********************************/
/*if HSE is not enabled then choose the default option (0)*/
typedef uint32 Rcc_PllHseDividerSel_t;
#define Rcc_PLL_HSE_NOT_DIVIDED_2              (Rcc_PllHseDividerSel_t)0
#define Rcc_PLL_HSE_DIVIDED_2                  (Rcc_PllHseDividerSel_t)1

/************************************
 *      PLL Mul Factor Macro        *
 ***********************************/
/*caution:max freq out of pll is 72 MHZ*/
typedef uint32 Rcc_PllMulFactor_t;
#define RCC_PLL_MUL_FACTOR_2                   (Rcc_PllMulFactor_t)0
#define RCC_PLL_MUL_FACTOR_3                   (Rcc_PllMulFactor_t)1
#define RCC_PLL_MUL_FACTOR_4                   (Rcc_PllMulFactor_t)2
#define RCC_PLL_MUL_FACTOR_5                   (Rcc_PllMulFactor_t)3
#define RCC_PLL_MUL_FACTOR_6                   (Rcc_PllMulFactor_t)4
#define RCC_PLL_MUL_FACTOR_7                   (Rcc_PllMulFactor_t)5
#define RCC_PLL_MUL_FACTOR_8                   (Rcc_PllMulFactor_t)6
#define RCC_PLL_MUL_FACTOR_9                   (Rcc_PllMulFactor_t)7
#define RCC_PLL_MUL_FACTOR_10                  (Rcc_PllMulFactor_t)8
#define RCC_PLL_MUL_FACTOR_11                  (Rcc_PllMulFactor_t)9
#define RCC_PLL_MUL_FACTOR_12                  (Rcc_PllMulFactor_t)10
#define RCC_PLL_MUL_FACTOR_13                  (Rcc_PllMulFactor_t)11
#define RCC_PLL_MUL_FACTOR_14                  (Rcc_PllMulFactor_t)12
#define RCC_PLL_MUL_FACTOR_15                  (Rcc_PllMulFactor_t)13
#define RCC_PLL_MUL_FACTOR_16                  (Rcc_PllMulFactor_t)14


/************************************
 *          MCO Status Macro        *
 ***********************************/
/*caution Max output freq is 50 MHZ*/
typedef uint32 Rcc_McoStatus_t;
#define RCC_MCO_DIABLED                        (Rcc_McoStatus_t)0
#define RCC_MCO_SYSCLK                         (Rcc_McoStatus_t)4
#define RCC_MCO_HSI                            (Rcc_McoStatus_t)5
#define RCC_MCO_HSE                            (Rcc_McoStatus_t)6
#define RCC_MCO_PLL_DIVIDED_2                  (Rcc_McoStatus_t)7

/************************************
 *         USB Prescaler Macro      *
 ***********************************/
/*usb need 48 MHZ from the pll so it must configure with this freq*/
/*put the defalut value if usb is not used (0)*/
typedef uint32 Rcc_UsbPrescaler_t;
#define RCC_USB_PLL_DIVIDED_1_5                (Rcc_UsbPrescaler_t)0
#define RCC_USB_PLL                            (Rcc_UsbPrescaler_t)1

/************************************
 *         ADC Prescaler Macro      *
 ***********************************/
typedef uint32 Rcc_AdcPrescaler_t;
#define RCC_ADC_PCLK2_DIVIDED_2                (Rcc_AdcPrescaler_t)0
#define RCC_ADC_PCLK2_DIVIDED_4                (Rcc_AdcPrescaler_t)1
#define RCC_ADC_PCLK2_DIVIDED_6                (Rcc_AdcPrescaler_t)2
#define RCC_ADC_PCLK2_DIVIDED_8                (Rcc_AdcPrescaler_t)3

/************************************
 *        APB2 Prescaler Macro      *
 ***********************************/
typedef uint32 Rcc_Abp2Prescaler_t;
#define RCC_APB2_HCLK                          (Rcc_Abp2Prescaler_t)0
#define RCC_APB2_HCLK_DIVIDED_2                (Rcc_Abp2Prescaler_t)4
#define RCC_APB2_HCLK_DIVIDED_4                (Rcc_Abp2Prescaler_t)5
#define RCC_APB2_HCLK_DIVIDED_8                (Rcc_Abp2Prescaler_t)6
#define RCC_APB2_HCLK_DIVIDED_16               (Rcc_Abp2Prescaler_t)7


/************************************
 *        APB1 Prescaler Macro      *
 ***********************************/
/*caution Max freq is 36MHZ*/
typedef uint32 Rcc_Abp1Prescaler_t;
#define RCC_APB1_HCLK                          (Rcc_Abp1Prescaler_t)0
#define RCC_APB1_HCLK_DIVIDED_2                (Rcc_Abp1Prescaler_t)4
#define RCC_APB1_HCLK_DIVIDED_4                (Rcc_Abp1Prescaler_t)5
#define RCC_APB1_HCLK_DIVIDED_8                (Rcc_Abp1Prescaler_t)6
#define RCC_APB1_HCLK_DIVIDED_16               (Rcc_Abp1Prescaler_t)7

/************************************
 *        AHB Prescaler Macro      *
 ***********************************/
typedef uint32 Rcc_AhbPrescaler_t;
#define RCC_AHB_SYSCLK                          (Rcc_AhbPrescaler_t)0
#define RCC_AHB_SYSCLK_DIVIDED_2                (Rcc_AhbPrescaler_t)8
#define RCC_AHB_SYSCLK_DIVIDED_4                (Rcc_AhbPrescaler_t)9
#define RCC_AHB_SYSCLK_DIVIDED_8                (Rcc_AhbPrescaler_t)10
#define RCC_AHB_SYSCLK_DIVIDED_16               (Rcc_AhbPrescaler_t)11
#define RCC_AHB_SYSCLK_DIVIDED_64               (Rcc_AhbPrescaler_t)12
#define RCC_AHB_SYSCLK_DIVIDED_128              (Rcc_AhbPrescaler_t)13
#define RCC_AHB_SYSCLK_DIVIDED_256              (Rcc_AhbPrescaler_t)14
#define RCC_AHB_SYSCLK_DIVIDED_512              (Rcc_AhbPrescaler_t)15

/************************************
 *        SYSCLK Select Macro       *
 ***********************************/
typedef uint8 Rcc_SysClkSelect_t;
#define RCC_SYSCLK_HSI                          (Rcc_SysClkSelect_t)0
#define RCC_SYSCLK_HSE                          (Rcc_SysClkSelect_t)1
#define RCC_SYSCLK_PLL                          (Rcc_SysClkSelect_t)2

/***********************************************
 *        peripheral enable/reset Macros       *
 ***********************************************/
typedef uint8 Rcc_PeripheralSel_t;
/************************
 *       APB1 bits      *
 ***********************/
#define RCC_DAC                                  (Rcc_PeripheralSel_t)93
#define RCC_PWR                                  (Rcc_PeripheralSel_t)92
#define RCC_BKP                                  (Rcc_PeripheralSel_t)91
#define RCC_CAN                                  (Rcc_PeripheralSel_t)89
#define RCC_USB                                  (Rcc_PeripheralSel_t)87
#define RCC_I2C2                                 (Rcc_PeripheralSel_t)86
#define RCC_I2C1                                 (Rcc_PeripheralSel_t)85
#define RCC_UART5                                (Rcc_PeripheralSel_t)84
#define RCC_UART4                                (Rcc_PeripheralSel_t)83
#define RCC_USART3                               (Rcc_PeripheralSel_t)82
#define RCC_USART2                               (Rcc_PeripheralSel_t)81
#define RCC_SPI3                                 (Rcc_PeripheralSel_t)79
#define RCC_SPI2                                 (Rcc_PeripheralSel_t)78
#define RCC_WWDG                                 (Rcc_PeripheralSel_t)75
#define RCC_TIM14                                (Rcc_PeripheralSel_t)72
#define RCC_TIM13                                (Rcc_PeripheralSel_t)71
#define RCC_TIM12                                (Rcc_PeripheralSel_t)70
#define RCC_TIM7                                 (Rcc_PeripheralSel_t)69
#define RCC_TIM6                                 (Rcc_PeripheralSel_t)68
#define RCC_TIM5                                 (Rcc_PeripheralSel_t)67
#define RCC_TIM4                                 (Rcc_PeripheralSel_t)66
#define RCC_TIM3                                 (Rcc_PeripheralSel_t)65
#define RCC_TIM2                                 (Rcc_PeripheralSel_t)64

/************************
 *       APB2 bits      *
 ***********************/
#define RCC_TIM11                                (Rcc_PeripheralSel_t)53
#define RCC_TIM10                                (Rcc_PeripheralSel_t)52
#define RCC_TIM9                                 (Rcc_PeripheralSel_t)51
#define RCC_ADC3                                 (Rcc_PeripheralSel_t)47
#define RCC_USART1                               (Rcc_PeripheralSel_t)46
#define RCC_TIM8                                 (Rcc_PeripheralSel_t)45
#define RCC_SPI1                                 (Rcc_PeripheralSel_t)44
#define RCC_TIM1                                 (Rcc_PeripheralSel_t)43
#define RCC_ADC2                                 (Rcc_PeripheralSel_t)42
#define RCC_ADC1                                 (Rcc_PeripheralSel_t)41
#define RCC_IOPG                                 (Rcc_PeripheralSel_t)40
#define RCC_IOPF                                 (Rcc_PeripheralSel_t)39
#define RCC_IOPE                                 (Rcc_PeripheralSel_t)38
#define RCC_IOPD                                 (Rcc_PeripheralSel_t)37
#define RCC_IOPC                                 (Rcc_PeripheralSel_t)36
#define RCC_IOPB                                 (Rcc_PeripheralSel_t)35
#define RCC_IOPA                                 (Rcc_PeripheralSel_t)34
#define RCC_AFIO                                 (Rcc_PeripheralSel_t)32

/************************
 *       APB1 bits      *
 ***********************/
#define RCC_SDIOEN                               (Rcc_PeripheralSel_t)10
#define RCC_FSMCEN                               (Rcc_PeripheralSel_t)8
#define RCC_CRCEN                                (Rcc_PeripheralSel_t)6
#define RCC_FLITFEN                              (Rcc_PeripheralSel_t)4
#define RCC_SRAMEN                               (Rcc_PeripheralSel_t)2
#define RCC_DMA2EN                               (Rcc_PeripheralSel_t)1
#define RCC_DMA1EN                               (Rcc_PeripheralSel_t)0


/****************************************
 *           LSI Selection Macro        *
 ***************************************/
/*LSI is off by default*/
typedef uint32 Rcc_LsiStatus_t;
#define RCC_LSI_DISABLED                          (Rcc_LsiStatus_t)0
#define RCC_LSI_ENABLED                           (Rcc_LsiStatus_t)1

/****************************************
 *           LSE Selection Macro        *
 ***************************************/
/*LSI is off by default*/
typedef uint32 Rcc_LseStatus_t;
#define RCC_LSE_DISABLED                          (Rcc_LseStatus_t)0
#define RCC_LSE_ENABLED                           (Rcc_LseStatus_t)1

/*************************************
 *           LSE Bypass Macro        *
 ************************************/
typedef uint32 Rcc_LseBypassEnable_t;
#define RCC_LSE_NO_BYPASS                         (Rcc_LseBypassEnable_t)0
#define RCC_LSE_BYPASS                            (Rcc_LseBypassEnable_t)1
/***********************************************************************************/


/************************************************************************
 *                        functions' prototypes                         *
 ************************************************************************/

/**************************************************************************************************************************************
 *  Function : Rcc_InitClock                                                                                                          *
 *  Param    : IN     : None                                                                                                          *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   :  Rcc_ErrorStatus_t                                                                                                     *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This initialize all clock sources in the controller, set prescale for all buses , ADC and USB and                      *
 *             configure MCO pin Source                                                                                               *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/
Rcc_ErrorStatus_t Rcc_InitClock(void);

/**************************************************************************************************************************************
 *  Function : Rcc_InitPeripheralsClock                                                                                               *
 *  Param    : IN     : None                                                                                                          *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Rcc_ErrorStatus_t                                                                                                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function initialize clock for all specified peripheral in the configuration file                                  *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/
Rcc_ErrorStatus_t Rcc_InitPeripheralsClock(void);


/**************************************************************************************************************************************
 *  Function : Rcc_InitPeripheralsClock                                                                                               *
 *  Param    : IN     : Name / Per_Id                                                                                                 *
 *                      Type / Rcc_PeripheralSel_t                                                                                    *
 *                      Desc / takes predefined macro for peripheral id                                                               *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Rcc_ErrorStatus_t                                                                                                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function initialize clock for specific peripheral                                                                 *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/
Rcc_ErrorStatus_t Rcc_InitPeripheralClock(Rcc_PeripheralSel_t Per_Id);

/**************************************************************************************************************************************
 *  Function : Rcc_deInit                                                                                                             *
 *  Param    : IN     : None                                                                                                          *
 *                                                                                                                                    *
 *             Output : None                                                                                                          *
 *                                                                                                                                    *
 *  Return   : Rcc_ErrorStatus_t                                                                                                      *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *  Desc     : This function initialize HSI as system clock and disable all other configuration and set default factory               *
 *             values in the Rcc Registers                                                                                            *
 *                                                                                                                                    *
 *                                                                                                                                    *
 *************************************************************************************************************************************/
Rcc_ErrorStatus_t Rcc_deInit(void);
#endif /* RCC_INC_RCC_H_ */
