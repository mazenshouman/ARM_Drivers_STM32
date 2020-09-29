/*
 *  File 	   : Rcc.c
 *  Created on : Aug 30, 2020
 *  Author	   : Mazen Shouman
 *  Version    : 1.0
 */

/************************************************************************
 *                              Includes                                *
 ************************************************************************/
#include "Std_Types.h"
#include "Bit_Math.h"
#include "Rcc_Cfg.h"
#include "Rcc.h"
#include "Rcc_Lcfg.h"

/************************************************************************
 *                              Private Includes                        *
 ************************************************************************/

#include "Rcc_MemMap.h"

/********************************************
 *            Pointer to function           *
 *******************************************/
/*this will be used for future enhancement when interrupt is added*/
typedef void (*PtrToFunction) (void);


/************************************************************************
 *                         Macros And Types                             *
 ************************************************************************/
#define RCC_PER_CLK_EN_REG(OFFSET) *((&(RCC_BASE_ADDRESS->AHBENR))+OFFSET)


#define RCC_HSI_TRIM_MASK             (Rcc_Reg_Size_t)0xFFFFFF07
#define RCC_CLOCK_NOT_READY           0
#define RCC_PLL_MUL_FACTOR_MASK       (Rcc_Reg_Size_t)0xFFC3FFFF
#define RCC_SYSCLK_SOURCE_MASK        (Rcc_Reg_Size_t)0xFFFFFFFC
#define RCC_AHB_PRESCALE_MASK         (Rcc_Reg_Size_t)0xFFFFFF0F
#define RCC_APB1_PRESCALE_MASK        (Rcc_Reg_Size_t)0xFFFFF8FF
#define RCC_APB2_PRESCALE_MASK        (Rcc_Reg_Size_t)0xFFFFC7FF
#define RCC_ADC_PRESCALE_MASK         (Rcc_Reg_Size_t)0xFFFF3FFF
#define RCC_MCO_SOURCE_MASK           (Rcc_Reg_Size_t)0xF8FFFFFF
#define RCC_REG_SIZE                  32
#define RCC_CR_REG_RESET_VALUE        (Rcc_Reg_Size_t)0x00000083
#define RCC_CFGR_REG_RESET_VALUE      (Rcc_Reg_Size_t)0
#define RCC_CIR_REG_RESET_VALUE       (Rcc_Reg_Size_t)0
#define RCC_AHBENR_REG_RESET_VALUE    (Rcc_Reg_Size_t)0x00000014
#define RCC_APB2ENR_REG_RESET_VALUE   (Rcc_Reg_Size_t)0
#define RCC_APB1ENR_REG_RESET_VALUE   (Rcc_Reg_Size_t)0
#define RCC_BDCR_REG_RESET_VALUE      (Rcc_Reg_Size_t)0
#define RCC_CSR_REG_RESET_VALUE       (Rcc_Reg_Size_t)0x0C000000

/************************************************************************/

/************************************************************************
 *                     Function's Implementation                        *
 ************************************************************************/
/*each function will use two methods to place the value in the registers
 * 1-normal read - write - modify instruction to set or clear bit in the registers
 * 2-bit-banding alias to use atomic instruction as possible (but the only problem is that for values more than one bit is not applicable in this way)
 * */
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
Rcc_ErrorStatus_t Rcc_InitClock(void)
{
	Rcc_ErrorStatus_t returnValue=RCC_E_OK;
#if 0
	uint8 local_HsiStatusFlag=RCC_HSI_DISABLED;
#endif

	/*to configure the clock correctly we have to make the HSI as system clock and disable the pll as if any clock source is being used we can't change their configuration
	 * note: startup code for example sets the HSE as clock source for pll and pll is configured as sysclk
	 * so we can't disable both hse and PLL
	 *here I will configure HSI as sysclk and disable both HSE and Pll to set the new configuration
	 * */
	Rcc_deInit();
	/*HSI configuration*/
	/*check if the HSI is enabled or not */
	if(gstr_RccClockConfig.Rcc_HsiStatus==RCC_HSI_ENABLED)
	{/*if the default value is selected then set the value*/
		SET_BIT(RCC_BASE_ADDRESS->CR ,RCC_CR_HSION);

		/*wait until it's On*/
		while(!GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSION));

		if(gstr_RccClockConfig.Rcc_HsiTrimValue!=RCC_HSI_TRIM_DEFALUT_VALUE)
		{
			SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CR , RCC_HSI_TRIM_MASK , RCC_CR_HSITRIM , gstr_RccClockConfig.Rcc_HsiTrimValue);
		}
#if 0
		local_HsiStatusFlag=RCC_HSI_ENABLED;
#endif
	}

	/*HSE configuration*/
	if(gstr_RccClockConfig.Rcc_HseStatus==RCC_HSE_ENABLED)
	{
		/*check HSE bypass*/
		switch(gstr_RccClockConfig.Rcc_HseBypassEnable)
		{
			case RCC_HSE_NO_BYPASS:
				CLEAR_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSEBYP);
				break;
			case RCC_HSE_BYPASS:
				SET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSEBYP);
				break;
			default:
				returnValue=RCC_E_NOT_OK;
				break;
		}

		if(returnValue==RCC_E_OK)
		{
			/*then turn it on and check the HSE status flag*/
			SET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSEON);

			/*wait until the HSE become ready*/
			while(!GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSERDY));

			/*check the css bit*/
			switch(gstr_RccClockConfig.Rcc_CssStatus)
			{
				case RCC_CSS_DISABLED:
					CLEAR_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_CSSON);
					break;
				case RCC_CSS_ENABLED:
					SET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_CSSON);
					break;
				default:
					returnValue=RCC_E_NOT_OK;
					break;
			}
		}
		/*for this part i need confirmation that I can disable the HSi without changing the JTAG */
#if 0
		if(returnValue==RCC_E_OK)
		{
			/*if HSI is disabled then turn it off*/
			if(local_HsiStatusFlag==RCC_HSI_DISABLED)
			{
				CLEAR_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSION);

				/*wait until it's off*/
				while(GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSIRDY));
			}
		}
#endif
	}
	else if(gstr_RccClockConfig.Rcc_HseStatus==RCC_HSE_DISABLED)
	{
		/*then turn it off and check the HSE status flag*/
		CLEAR_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSEON);

		/*wait until the HSE becomes off*/
		while(GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSERDY));
	}
	else
	{
		returnValue=RCC_E_NOT_OK;
	}
	if(returnValue==RCC_E_OK)
	{
		/*pll configuration*/

		/*check pll on or not*/
		if(gstr_RccClockConfig.Rcc_PllStatus==RCC_PLL_ENABLED)
		{
			/*set the mul factor*/
			SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_PLL_MUL_FACTOR_MASK , RCC_CFGR_PLLMUL ,gstr_RccClockConfig.Rcc_PllMulFactor);

			/*if it was enabled configure source */
			switch(gstr_RccClockConfig.Rcc_PllSource)
			{
				case Rcc_PLL_SOURCE_HSI_DIVIDED_2:
					if(GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSIRDY)==RCC_CLOCK_NOT_READY)
					{
						returnValue=RCC_E_NOT_OK;
					}
					else
					{
						CLEAR_BIT(RCC_BASE_ADDRESS->CFGR , RCC_CFGR_PLLSRC);
					}

					break;
				case Rcc_PLL_SOURCE_HSE:
					if(GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSERDY)==RCC_CLOCK_NOT_READY)
					{
						returnValue=RCC_E_NOT_OK;
					}
					else
					{
						/*check divider value*/
						if(gstr_RccClockConfig.Rcc_PllHseDividerSel==Rcc_PLL_HSE_DIVIDED_2)
						{
							SET_BIT(RCC_BASE_ADDRESS->CFGR ,RCC_CFGR_PLLXTPRE);
						}
						else
						{
							CLEAR_BIT(RCC_BASE_ADDRESS->CFGR ,RCC_CFGR_PLLXTPRE);
						}
						/*set source*/
						SET_BIT(RCC_BASE_ADDRESS->CFGR , RCC_CFGR_PLLSRC);
					}
					break;
				default:
					returnValue=RCC_E_NOT_OK;
					break;
			}
			if(returnValue==RCC_E_OK)
			{
				SET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_PLLON);
				/*wait until it's ready*/
				while(!GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_PLLRDY));
			}
		}
		else if(gstr_RccClockConfig.Rcc_PllStatus==RCC_PLL_DISABLED)
		{
			CLEAR_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_PLLON);
			/*wait until it's off*/
			while(GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_PLLRDY));
		}

		/*set Busses (AHB , APB1 , APB2) prescale*/
		if(returnValue==RCC_E_OK)
		{
			/*I won't check for macros in this part*/
			/*set Busses (AHB , APB1 , APB2) prescale*/

			/*AHB prescale*/
			SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_AHB_PRESCALE_MASK ,RCC_CFGR_HPRE , gstr_RccClockConfig.Rcc_AhbPrescaler);

			/*Apb2 prescale*/
			SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_APB2_PRESCALE_MASK ,RCC_CFGR_PPRE2 , gstr_RccClockConfig.Rcc_Abp2Prescaler);

			/*Apb1 prescale*/
			SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_APB1_PRESCALE_MASK ,RCC_CFGR_PPRE1 , gstr_RccClockConfig.Rcc_Abp1Prescaler);

			/*if prescale used for AHB then check flash configuration*/

			/*set USB prescale*/
			switch(gstr_RccClockConfig.Rcc_UsbPrescaler)
			{
				case RCC_USB_PLL_DIVIDED_1_5:
					CLEAR_BIT(RCC_BASE_ADDRESS->CFGR,RCC_CFGR_USBPRE);
					break;
				case RCC_USB_PLL:
					SET_BIT(RCC_BASE_ADDRESS->CFGR,RCC_CFGR_USBPRE);
					break;
				default:
					break;
			}

			/*set ADC prescale*/
			SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_ADC_PRESCALE_MASK ,RCC_CFGR_ADCPRE , gstr_RccClockConfig.Rcc_AdcPrescaler);
		}

		/*set system clock to the configured clock*/
		if(returnValue==RCC_E_OK)
		{
			/*set system clock to the configured clock*/
			SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_SYSCLK_SOURCE_MASK ,RCC_CFGR_SW , gstr_RccClockConfig.Rcc_SysClkSelect);

			/*check if the wanted sysclk is set*/
			if(GET_VALUE_REG(RCC_BASE_ADDRESS->CFGR,RCC_SYSCLK_SOURCE_MASK,RCC_CFGR_SW)!=gstr_RccClockConfig.Rcc_SysClkSelect)
			{
				returnValue=RCC_E_NOT_OK;
			}
		}

		/*check LSI*/
		switch(gstr_RccClockConfig.Rcc_LsiStatus)
		{
			case RCC_LSI_DISABLED:
				CLEAR_BIT(RCC_BASE_ADDRESS->CSR,RCC_CSR_LSION);

				/*wait until it's off*/
				while(GET_BIT(RCC_BASE_ADDRESS->CSR,RCC_CSR_LSIRDY));
				break;
			case RCC_LSI_ENABLED:
				SET_BIT(RCC_BASE_ADDRESS->CSR,RCC_CSR_LSION);

				/*wait until it's locked*/
				while(!GET_BIT(RCC_BASE_ADDRESS->CSR,RCC_CSR_LSIRDY));
				break;
			default:
				break;
		}

		/*check LSE and bypass value*/
		switch(gstr_RccClockConfig.Rcc_LseStatus)
		{
			case RCC_LSE_DISABLED:
				CLEAR_BIT(RCC_BASE_ADDRESS->BDCR,RCC_BDCR_LSEON);

				/*wait until it's off*/
				while(GET_BIT(RCC_BASE_ADDRESS->BDCR,RCC_BDCR_LSERDY));
				break;
			case RCC_LSE_ENABLED:
				/*check bypass value*/
				switch(gstr_RccClockConfig.Rcc_LseBypassEnable)
				{
					case RCC_LSE_NO_BYPASS:
						CLEAR_BIT(RCC_BASE_ADDRESS->BDCR,RCC_BDCR_LSEBYP);
						break;
					case RCC_LSE_BYPASS:
						SET_BIT(RCC_BASE_ADDRESS->BDCR,RCC_BDCR_LSEBYP);
						break;
					default:
						break;
				}
				SET_BIT(RCC_BASE_ADDRESS->BDCR,RCC_BDCR_LSEON);

				/*wait until it's locked*/
				while(!GET_BIT(RCC_BASE_ADDRESS->BDCR,RCC_BDCR_LSERDY));
				break;
			default:
				break;
		}

		/*configure MCO pin source*/
		SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_MCO_SOURCE_MASK ,RCC_CFGR_MCO , gstr_RccClockConfig.Rcc_McoStatus);
	}
	return returnValue;
}

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
Rcc_ErrorStatus_t Rcc_InitPeripheralsClock(void)
{
	Rcc_ErrorStatus_t returnValue=RCC_E_OK;
	uint8 local_loopCounter=0;
	uint8 local_bitOffset=0;
	uint8 local_regOffset=0;
	for(local_loopCounter=0 ; local_loopCounter<RCC_NUMBER_OF_PERIPHERALS;++local_loopCounter)
	{
		if(ga_RccPeripheralConfig[local_loopCounter]>RCC_DAC)
		{
			returnValue=RCC_E_NOT_OK;
			break;
		}
		/*get bit offset in register*/
		local_bitOffset=ga_RccPeripheralConfig[local_loopCounter]%RCC_REG_SIZE;
		/*get register offset*/
		local_regOffset=ga_RccPeripheralConfig[local_loopCounter]/RCC_REG_SIZE;


		/*enable the wanted peripheral*/
		SET_BIT(RCC_PER_CLK_EN_REG(local_regOffset) , local_bitOffset);
	}
	return returnValue;
}


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
Rcc_ErrorStatus_t Rcc_InitPeripheralClock(Rcc_PeripheralSel_t Per_Id)
{
	Rcc_ErrorStatus_t returnValue=RCC_E_OK;
	uint8 local_bitOffset=0;
	uint8 local_regOffset=0;
	if(Per_Id>RCC_DAC)
	{
		returnValue=RCC_E_NOT_OK;
	}
	else
	{
		/*get bit offset in register*/
		local_bitOffset=Per_Id%RCC_REG_SIZE;
		/*get register offset*/
		local_regOffset=Per_Id/RCC_REG_SIZE;


		/*enable the wanted peripheral*/
		SET_BIT(RCC_PER_CLK_EN_REG(local_regOffset) , local_bitOffset);
	}
	return returnValue;
}

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
Rcc_ErrorStatus_t Rcc_deInit(void)
{
	Rcc_ErrorStatus_t returnValue=RCC_E_OK;
	/*enable HSI*/
	SET_BIT(RCC_BASE_ADDRESS->CR ,RCC_CR_HSION);

	/*wait until it's On*/
	while(!GET_BIT(RCC_BASE_ADDRESS->CR , RCC_CR_HSION));

	/*set it as sysclk*/

	SET_VALUE_FOR_BITS_IN_REG(RCC_BASE_ADDRESS->CFGR , RCC_SYSCLK_SOURCE_MASK ,RCC_CFGR_SW , RCC_SYSCLK_HSI);


	/*check if the wanted sysclk is set*/
	if(GET_VALUE_REG(RCC_BASE_ADDRESS->CFGR,RCC_SYSCLK_SOURCE_MASK,RCC_CFGR_SW)!=RCC_SYSCLK_HSI)
	{
		returnValue=RCC_E_NOT_OK;
	}
	else
	{
		/*disable pll and hse and reset value for all peripherals*/
		RCC_BASE_ADDRESS->CR=RCC_CR_REG_RESET_VALUE;
		RCC_BASE_ADDRESS->CFGR=RCC_CFGR_REG_RESET_VALUE;
		RCC_BASE_ADDRESS->CIR=RCC_CIR_REG_RESET_VALUE;
		RCC_BASE_ADDRESS->AHBENR=RCC_AHBENR_REG_RESET_VALUE;
		RCC_BASE_ADDRESS->APB2ENR=RCC_APB2ENR_REG_RESET_VALUE;
		RCC_BASE_ADDRESS->APB1ENR=RCC_APB1ENR_REG_RESET_VALUE;
		RCC_BASE_ADDRESS->BDCR=RCC_BDCR_REG_RESET_VALUE;
		RCC_BASE_ADDRESS->CSR=RCC_CSR_REG_RESET_VALUE;
	}
	return returnValue;
}


