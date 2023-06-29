/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Rcc_Private.h
 *		  Layer:  Mcal
 *       Module:  Rcc
 *		Version:  1.00
 *	
 *  Description:  Private macro definitions/functions to aid the implementation of the Rcc module
 *  
 *********************************************************************************************************************/
#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define MAX_NUMBER_OF_CLOCKS 5


/*** BIT DIFINITIONS ***/
/* RCC_CR */
#define RCC_CR_HSION 0
#define RCC_CR_HSIRDY 1
#define RCC_CR_HSEON 16
#define RCC_CR_HSERDY 17
#define RCC_CR_HSEBYP 18
#define RCC_CR_CSSON 19
#define RCC_CR_PLLON 24
#define RCC_CR_PLLRDY 25
#define RCC_CR_PLLI2SON 26
#define RCC_CR_PLLI2SRDY 27
#define RCC_CR_PLLSAION 28
#define RCC_CR_PLLSAIRDY 29

/* RCC_CFGR */
/*system clock switch*/
#define		RCC_CFGR_SW0                          0
#define		RCC_CFGR_SW1                          1
/*AHB Prescaler*/
#define		RCC_CFGR_HPRE_0                       4
#define		RCC_CFGR_HPRE_1                       5
#define		RCC_CFGR_HPRE_2                       6
#define		RCC_CFGR_HPRE_3                       7
/*APB Low-speed prescaler (APB1)*/
#define		RCC_CFGR_PPRE1_0                      10
#define		RCC_CFGR_PPRE1_1                      11
#define		RCC_CFGR_PPRE1_2                      12
/*APB High-speed prescaler (APB2)*/
#define		RCC_CFGR_PPRE2_0                      13
#define		RCC_CFGR_PPRE2_1                      14
#define		RCC_CFGR_PPRE2_2                      15

/* Bit definitions */
#define RCC_CFGR_MCO1_POS 21
#define RCC_CFGR_MCO1_MSK 0x00600000

#define RCC_CFGR_MCO1PRE_POS 24
#define RCC_CFGR_MCO1PRE_MSK 0x07000000

#define RCC_CFGR_MCO2_POS 30
#define RCC_CFGR_MCO2_MSK 0xc0000000

#define RCC_CFGR_MCO2PRE_POS 27
#define RCC_CFGR_MCO2PRE_MSK 0x38000000

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES 
 *********************************************************************************************************************/
static void RCC_InitPLL(Rcc_PllConfig_t *Copy_PllConfigPtr);

 
#endif  /* RCC_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Rcc_Private.h
 *********************************************************************************************************************/
