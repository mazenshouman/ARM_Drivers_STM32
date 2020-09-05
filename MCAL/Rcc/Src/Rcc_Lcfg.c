/*
 *  File 	   : Rcc_Lcfg.c
 *  Created on : Aug 30, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */


/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_Types.h"
#include "Rcc.h"
#include "Rcc_Lcfg.h"


/************************************************************************
 *      creating instance and initializing configuration structure      *
 ************************************************************************/
Rcc_ClockConfigStr_t gstr_RccClockConfig=
{
		/*      HsiStatus                 HsiTrimValue                      HseStatus            HseBypassEnable             CssStatus 	               PllStatus                PllSource                     PllHseDividerSel                PllMulFactor             SysclkSelect           AhbPrescaler          Abp1Prescaler              Abp2Prescaler           AdcPrescaler             UsbPrescaler               McoStatus          LsiStatus            LseStatus          LseBypassEnable*/
		     RCC_HSI_ENABLED     ,    RCC_HSI_TRIM_DEFALUT_VALUE ,       RCC_HSE_ENABLED    ,   RCC_HSE_NO_BYPASS     ,    RCC_CSS_DISABLED   ,    RCC_PLL_DISABLED   ,    Rcc_PLL_SOURCE_HSE      ,      Rcc_PLL_HSE_NOT_DIVIDED_2    ,  RCC_PLL_MUL_FACTOR_9     ,   RCC_SYSCLK_HSE     ,   RCC_AHB_SYSCLK  ,      RCC_APB1_HCLK    ,        RCC_APB2_HCLK    ,  RCC_ADC_PCLK2_DIVIDED_2 , RCC_USB_PLL_DIVIDED_1_5  , RCC_MCO_DIABLED  , RCC_LSI_DISABLED  ,   RCC_LSE_DISABLED  ,  RCC_LSE_NO_BYPASS
};

Rcc_PeripheralSel_t  ga_RccPeripheralConfig[RCC_NUMBER_OF_PERIPHERALS]=
{
		RCC_IOPA,
		RCC_IOPB,
		RCC_IOPC,
};
