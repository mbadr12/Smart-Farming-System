/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Gpio_Private.h
 *		  Layer:  Mcal
 *       Module:  Gpio
 *		Version:  1.00
 *	
 *  Description:  Private macro definitions/functions to aid the implementation of the Gpio module
 *  
 *********************************************************************************************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define NUMBER_OF_PINS_PER_PORT 16u
#define BAND_REGION_START 0x40000000
#define BAND_ALIAS_REGION_START 0x42000000
#define BIT_BANDING 1
#define GPIO_IDR_REG_OFFSET 4
#define MAX_PIN_ID 175
#define MAX_PIN_LEVEL 1 
#define MAX_PORT_LEVEL 0xffff 
#define MAX_PORT_ID 11

#define GPIO_MODE_MSK 0x3



#define MAX_PIN_MODE 3
/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define IS_PIN_ID(val) ((val >= 0 && val < 176U))
#define IS_PORT_ID(val) ((val >= 0 && val < 11U ))
#define IS_PIN_MODE(val) ((val >= 0 && val < 4U))
#define IS_PIN_OUTPUT_TYPE(val) ((val >= 0 && val < 2U))
#define IS_PIN_OUTPUT_SPEED(val) ((val >= 0 && val < 4U))
#define IS_PIN_INTERNAL_ATTACH(val) ((val >= 0 && val < 4U))
#define IS_PIN_LEVEL(val) ((val >= 0 && val < 2U))
#define IS_PORT_LEVEL(val) ((val >= 0 && val <= 0xffffU))
#define IS_BOOL(val) ((val == 0 || val == 1))
#define IS_PIN_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF15_EVENTOUT)  || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF5_SPI5)       || ((AF) == GPIO_AF5_SPI6)       || \
                          ((AF) == GPIO_AF8_UART7)      || ((AF) == GPIO_AF8_UART8)      || \
                          ((AF) == GPIO_AF12_FMC)       ||  ((AF) == GPIO_AF6_SAI1)      || \
                          ((AF) == GPIO_AF14_LTDC))



/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES 
 *********************************************************************************************************************/


 
#endif  /* GPIO_PRIVATE_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpio_Private.h
 *********************************************************************************************************************/
