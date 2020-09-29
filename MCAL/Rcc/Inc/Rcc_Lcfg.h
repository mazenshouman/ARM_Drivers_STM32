/*
 *  File 	   : Rcc_Lcfg.h
 *  Created on : Aug 30, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef RCC_INC_RCC_LCFG_H_
#define RCC_INC_RCC_LCFG_H_



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
 *                      Configuration Structure                         *
 ************************************************************************/
/*you can reduce the excution time taken by shifting this bit in the initialization function by setting the
 * actual value in the macros so you can just or the values in the register*/
typedef struct{
	Rcc_HsiStatus_t                       Rcc_HsiStatus:1;
	Rcc_HsiTrimValue_t                    Rcc_HsiTrimValue:5;
	Rcc_HseStatus_t                       Rcc_HseStatus:1;
	Rcc_HseBypassEnable_t                 Rcc_HseBypassEnable:1;
	Rcc_CssStatus_t                       Rcc_CssStatus:1;
	Rcc_PllStatus_t                       Rcc_PllStatus:1;
	Rcc_PllSource_t                       Rcc_PllSource:1;
	Rcc_PllHseDividerSel_t                Rcc_PllHseDividerSel:1;
	Rcc_PllMulFactor_t                    Rcc_PllMulFactor:4;
	Rcc_SysClkSelect_t                    Rcc_SysClkSelect:2;
	Rcc_AhbPrescaler_t                    Rcc_AhbPrescaler:4;
	Rcc_Abp1Prescaler_t                   Rcc_Abp1Prescaler:3;
	Rcc_Abp2Prescaler_t                   Rcc_Abp2Prescaler:3;
	Rcc_AdcPrescaler_t                    Rcc_AdcPrescaler:2;
	Rcc_UsbPrescaler_t                    Rcc_UsbPrescaler:1;
	Rcc_McoStatus_t                       Rcc_McoStatus:3;
	Rcc_LsiStatus_t                       Rcc_LsiStatus:1;
	Rcc_LseStatus_t                       Rcc_LseStatus:1;
	Rcc_LseBypassEnable_t                 Rcc_LseBypassEnable:1;
}Rcc_ClockConfigStr_t;

/************************************************************************
 *              Externed configuration Structure instance               *
 ************************************************************************/

extern Rcc_ClockConfigStr_t gstr_RccClockConfig;
extern Rcc_PeripheralSel_t  ga_RccPeripheralConfig[RCC_NUMBER_OF_PERIPHERALS];

#endif /* RCC_INC_RCC_LCFG_H_ */
