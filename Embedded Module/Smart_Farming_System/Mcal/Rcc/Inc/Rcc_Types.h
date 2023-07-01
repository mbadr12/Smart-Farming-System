/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Rcc_Types.h
 *		    Layer:  Mcal
 *       Module:  Rcc
 *		  Version:  1.00
 *	
 *  Description:  Rcc module API type definitions.    
 *  
 *********************************************************************************************************************/
#ifndef RCC_TYPES_H 
#define RCC_TYPES_H 

/**********************************************************************************************************************
 * INCLUDES 
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum {
  RCC_AHB1_GPIOA = 0,
  RCC_AHB1_GPIOB,
  RCC_AHB1_GPIOC,
  RCC_AHB1_GPIOD,
  RCC_AHB1_GPIOE,
  RCC_AHB1_GPIOF,
  RCC_AHB1_GPIOG,
  RCC_AHB1_GPIOH,
  RCC_AHB1_GPIOI,
  RCC_AHB1_GPIOJ,
  RCC_AHB1_GPIOK,
  RCC_AHB1_CRC = 12,
  RCC_AHB1_FLITF_LP = 15, // only available in low power
  RCC_AHB1_SRAM1_LP, // only available in low power
  RCC_AHB1_SRAM2_LP, // only available in low power
  RCC_AHB1_BKPSRAM, 
  RCC_AHB1_CCMDATARAM=20, // Not availabe in low power
  RCC_AHB1_DMA1,
  RCC_AHB1_DMA2,
  RCC_AHB1_ETHMAC = 25,
  RCC_AHB1_ETHMACTX,
  RCC_AHB1_ETHMACRX,
  RCC_AHB1_ETHMACPTP,
  RCC_AHB1_OTGHS,
  RCC_AHB1_OTGHSULPI,
  RCC_AHB2_DCMI = 32,
  RCC_AHB2_CRYP = 32+4,
  RCC_AHB2_HASH,
  RCC_AHB2_RNG,
  RCC_AHB2_OTGFS,
  RCC_AHB3_FMC = 64,
  RCC_APB1_TIM2 = 96,
  RCC_APB1_TIM3,
  RCC_APB1_TIM4,
  RCC_APB1_TIM5,
  RCC_APB1_TIM6,
  RCC_APB1_TIM7,
  RCC_APB1_TIM12,
  RCC_APB1_TIM13,
  RCC_APB1_TIM14,
  RCC_APB1_WWDG = 96+11,
  RCC_APB1_SPI2 = 96+14,
  RCC_APB1_SPI3,
  RCC_APB1_USART2 = 96+17,
  RCC_APB1_USART3,
  RCC_APB1_UART4,
  RCC_APB1_UART5,
  RCC_APB1_I2C1,
  RCC_APB1_I2C2,
  RCC_APB1_I2C3,
  RCC_APB1_CAN1 = 96 + 25,
  RCC_APB1_CAN2,
  RCC_APB1_PWR = 96 + 28,
  RCC_APB1_DAC,
  RCC_APB1_UART7,
  RCC_APB1_UART8,
  RCC_APB2_TIM1 = 128,
  RCC_APB2_TIM8,
  RCC_APB2_USART1 = 128 + 4,
  RCC_APB2_USART6,
  RCC_APB2_ADC1 = 128 + 8,
  RCC_APB2_ADC2,
  RCC_APB2_ADC3,
  RCC_APB2_SDIO,
  RCC_APB2_SPI1,
  RCC_APB2_SPI4,
  RCC_APB2_SYSCFG,
  RCC_APB2_TIM9 = 128 + 16,
  RCC_APB2_TIM10,
  RCC_APB2_TIM11,
  RCC_APB2_SPI15 = 128 + 20,
  RCC_APB2_SPI16,
  RCC_APB2_SAI1,
  RCC_APB2_LTDC = 128 + 26
}Rcc_PeripheralId_t;


typedef enum {
  RCC_HSE_CRYSTAL = 1,
  RCC_HSE_RC,
  RCC_HSI,
  RCC_PLL,
  RCC_PLLI2S,
  RCC_PLLSAI
}Rcc_ClkType_t;

/*** PLL CONFIGURATION TYPE DEFINITIONS ***/
typedef enum {
  RCC_PLL_MAIN,
  RCC_PLL_I2S,
  RCC_PLL_SAI
}Rcc_PllType_t;

typedef enum {
  RCC_PLL_SRC_HSI,
  RCC_PLL_SRC_HSE,
}Rcc_PllSrc_t;

typedef struct{
  /* Select which PLL you want to configure */
  Rcc_PllType_t PllType;
  /* Select the PLL source */
  Rcc_PllSrc_t PllSrc;
  /* M Division Factor */
  u8 MDF;
  /* P Division Factor */
  u8 PDF;
  /* Q Division Factor */
  u8 QDF;
  /* R Division Factor */
  u8 RDF;
  /* N Multiplication Factor */ 
  u8 NMF;
} Rcc_PllConfig_t;

typedef enum
{
  RCC_MCO_PS_1,
  RCC_MCO_PS_2 = 4,
  RCC_MCO_PS_3,
  RCC_MCO_PS_4,
  RCC_MCO_PS_5,
} Rcc_McoPrescaler_t;

typedef enum
{
  RCC_MCO1_HSI = 0,
  RCC_MCO1_LSE,
  RCC_MCO1_HSE,
  RCC_MCO1_PLL,
} Rcc_Mco1Src_t;

typedef enum
{
  RCC_MCO2_SYSCLK = 0,
  RCC_MCO2_PLLI2S,
  RCC_MCO2_HSE,
  RCC_MCO2_PLL,
} Rcc_Mco2Src_t;

#endif  /* RCC_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Rcc_Types.h
 *********************************************************************************************************************/
