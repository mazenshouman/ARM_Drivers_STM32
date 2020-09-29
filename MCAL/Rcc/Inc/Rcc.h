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

/************************************************************************
 *                           Error macros                               *
 ************************************************************************/
typedef uint8 Rcc_ErrorStatus_t;
#define RCC_E_NOT_OK                                        (Rcc_ErrorStatus_t)1
#define RCC_E_OK                                            (Rcc_ErrorStatus_t)0
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
