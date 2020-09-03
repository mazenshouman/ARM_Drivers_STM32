/*
 *  File 	   : Rcc_Lcfg.h
 *  Created on : Aug 30, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

#ifndef RCC_INC_RCC_LCFG_H_
#define RCC_INC_RCC_LCFG_H_

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
